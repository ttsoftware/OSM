/*
* OSM shell.
*/

#include "tests/lib.h"

#define BUFFER_SIZE 100
#define PATH_LENGTH 256

typedef int (*cmd_fun_t)(int, char**);

typedef struct {
    char* name;
    cmd_fun_t func;
    char *desc;
} cmd_t;

int cmd_echo(int, char**);
int cmd_show(int, char**);
int cmd_read(int, char**);
int cmd_rm(int, char**);
int cmd_cp(int, char**);
int cmd_cmp(int, char**);
int cmd_ls(int, char**);
int cmd_exit();
int cmd_help();

cmd_t commands[] = { 
    {"echo", cmd_echo, "print the arguments to the screen"},
    {"show", cmd_show, "print the contents of the given file to the screen"},
    {"read", cmd_read, "read a line from standard in and write it to a new file"},
    {"rm", cmd_rm, "deletes a file if it exists."},
    {"cp", cmd_cp, "copies a file."},
    {"cmp", cmd_cmp, "compares the contents of two file."},
    {"ls", cmd_ls, "list directory contents."},
    {"exit", cmd_exit, "exit the buenos shell."},
    {"help", cmd_help, "show this help message"}
};

#define N_COMMANDS sizeof(commands) / sizeof(cmd_t)

void print_prompt(int last_retval) {
    printf("%d> ", last_retval);
}

/* Note that tokenize(cmdline, argv) modifies cmdline by inserting NUL
characters. */
int tokenize(char* cmdline, char** argv) {
    int argc = 0;
    int inword=0;
    char *s, *p;
    for (s = cmdline, p = cmdline; *s; s++) {
        if (*s == ' ' && inword) {
            inword=0;
            argv[argc++]=p;
            *s = '\0';
        } else if (*s != ' ' && !inword) {
            inword=1;
            p=s;
        }
    }
    if (inword) {
        argv[argc++]=p;
    }
    return argc;
}

int run_program(char* prog) {
    return syscall_join(syscall_exec(prog));
}

int run_command(char* cmdline) {
    char* argv[BUFFER_SIZE];
    int argc = tokenize(cmdline, argv);
    unsigned int i;
    if (argc == 0) {
        return 0;
    }
    for (i = 0; i < N_COMMANDS; i++) {
        if (strcmp(argv[0], commands[i].name) == 0) {
            return commands[i].func(argc, argv);
        }
    }
    return run_program(cmdline);
}

void help() {
    printf("Welcome to the Buenos Shell!\n");
    printf("The following commands are available:\n");
    unsigned int i;
    for (i = 0; i < N_COMMANDS; i++) {
        printf("  %s: %s\n", commands[i].name, commands[i].desc);
    }
}

int main(void) {
    char cmdline[BUFFER_SIZE];
    int ret = 0;
    help();
    while (1) {
        print_prompt(ret);
        readline(cmdline, BUFFER_SIZE);
        run_command(cmdline);
    }
    syscall_halt();
    return 0;
}

int cmd_echo(int argc, char** argv) {
    int i;
    for (i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    puts("\n");
    return 0;
}

int cmd_show(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: show <file>\n");
        return 1;
    }

    int fd;
    if ((fd=syscall_open(argv[1])) < 0) {
        printf("Could not open %s.  Reason: %d\n", argv[1], fd);
        return 1;
    }

    int rd;
    char buffer[BUFFER_SIZE];
    while ((rd = syscall_read(fd, buffer, BUFFER_SIZE))) {
        int wr=0, thiswr;
        while (wr < rd) {
            if ((thiswr = syscall_write(1, buffer+wr, rd-wr)) <= 0) {
                printf("\nCall to syscall_write() failed.  Reason: %d.\n", wr);
                syscall_close(fd);
                return 1;
            }
            wr += thiswr;
        }
    }
    if (rd < 0) {
        printf("\nCall to syscall_read() failed.  Reason: %d.\n", rd);
        syscall_close(fd);
        return 1;
    } else {
        syscall_close(fd);
        return 0;
    }
}

int cmd_read(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: read <file>\n");
        return 1;
    }

    char text[BUFFER_SIZE];
    int count, ret, fd, wr;
    count = readline(text, BUFFER_SIZE - 1) + 1;
    text[count - 1] = '\n';
    text[count] = '\0';
    
    if ((ret=syscall_create(argv[1], count)) < 0) {
        printf("Could not create %s with initial size %d.  Reason: %d\n", argv[1], count, ret);
        return 1;
    }
    
    if ((fd=syscall_open(argv[1])) < 0) {
        printf("Could not open %s.  Reason: %d\n", argv[1], fd);
        return 1;
    }

    if ((wr=syscall_write(fd, text, count)) <= 0) {
        printf("\nCall to syscall_write() failed.  Reason: %d.\n", wr);
        syscall_close(fd);
        return 1;
    }

    syscall_close(fd);
    return 0;
}

int cmd_ls(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: ls <directory>\n");
        return 1;
    }

    char const* volumename = argv[1];
    
    int filecount = syscall_filecount(volumename);

    printf("%d\n", filecount);

    char temp_filename[VFS_NAME_LENGTH];

    int i = 0;
    int files = 0;
    while (files < filecount) {

        int code = syscall_file(volumename, i, temp_filename);

        printf("%d\n", code);
        if (code == 0) {
            printf("%s\n", temp_filename);
            files++;
        }
        i++;
    }

    return 0;
}

/**
 *  Display the first byte where the files differ.
 */
int cmd_cmp(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: cmp <file1> <file2>\n");
        return 1;
    }

    char file1_buffer[1];
    char file2_buffer[1];

    int file1_handle = syscall_open(argv[1]);
    int file2_handle = syscall_open(argv[2]);

    int position = 1;
    int line = 1;
    int diff = 0;
    while (syscall_read(file1_handle, &file1_buffer, 1) > 0) {
        int read = syscall_read(file2_handle, &file2_buffer, 1);
        // we check if file2 is EOF
        if (read == 0) {
            diff++;
            break;
        }
        // we check bytes are equal
        if (file1_buffer[0] != file2_buffer[0]) {
            diff++;
            break;
        }
        // check for newline, which coincidentally is ascii number 10
        if (file1_buffer[0] == 10) {
            line++;
        }

        position++;
    }
    if (diff > 0) {
        printf(
            "Files differ at position %d, line %d\n", 
            position, 
            line
        );   
    }
    return 0;
}

/**
 * We read through the file to find its length.
 * We then read it into the buffer, create a new file,
 * and write the buffer to the new file.
 */
int cmd_cp(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: cp <file>\n");
        return 1;
    }

    char temp_buffer[1];
    int handle = syscall_open(argv[1]);

    int length = 0;
    while (syscall_read(handle, &temp_buffer, 1) > 0) {
        length++;
    }

    char buffer[length];
    syscall_seek(handle, 0);
    syscall_read(handle, &buffer, length); 

    handle = syscall_open(argv[2]);
    if (handle == -1) {
        syscall_create(argv[2], length);
        handle = syscall_open(argv[2]);
    }
    syscall_write(handle, &buffer, length);

    return 0;
}

int cmd_rm(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: rm <file>\n");
        return 1;
    }
    syscall_delete(argv[1]);
    return 0;
}

int cmd_help() {
    help();
    return 0;
}   

int cmd_exit() {
    syscall_exit(0);
    return 0;
}