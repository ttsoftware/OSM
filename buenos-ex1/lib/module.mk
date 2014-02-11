# Makefile for the lib module

# Set the module name
MODULE := lib

FILES := libc.c xprintf.c rand.S bitmap.c debug.c dlist.c

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
