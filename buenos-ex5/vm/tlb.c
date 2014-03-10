/*
 * TLB handling
 *
 * Copyright (C) 2003 Juha Aatrokoski, Timo Lilja,
 *   Leena Salmela, Teemu Takanen, Aleksi Virtanen.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: tlb.c,v 1.6 2004/04/16 10:54:29 ttakanen Exp $
 *
 */

#include "kernel/panic.h"
#include "kernel/assert.h"
#include "kernel/thread.h"
#include "vm/tlb.h"
#include "vm/pagetable.h"

tlb_entry_t* vpn_lookup(unsigned int vpn2, pagetable_t* pagetable) {
    for (unsigned int i = 0; i < pagetable->valid_count; i++) {
        if (pagetable->entries[i].VPN2 == vpn2) {
            return &(pagetable->entries[i]);
        }
    }
    return NULL;
}

void tlb_modified_exception(void)
{
    KERNEL_PANIC("Dirty bit was 0.");
}

void tlb_load_exception(void)
{
    tlb_store_exception();
}

void tlb_store_exception(void)
{
    tlb_exception_state_t tes;
    _tlb_get_exception_state(&tes);

    thread_table_t* current_thread = thread_get_current_thread_entry();
    pagetable_t* pagetable = current_thread->pagetable;

    tlb_entry_t* entry = vpn_lookup(tes.badvpn2, pagetable);
  
    if (entry == NULL) {
        kprintf("TLB exception. Details:\n"
           "Failed Virtual Address: 0x%8.8x\n"
           "Virtual Page Number:    0x%8.8x\n"
           "ASID (Thread number):   %d\n",
           tes.badvaddr, tes.badvpn2, tes.asid);
        KERNEL_PANIC("Segmentation fault.");
    }

    _tlb_write_random(entry);
}