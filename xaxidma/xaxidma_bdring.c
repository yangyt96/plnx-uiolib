/*
Copyright (c) 2021 Yee Yang Tan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "xaxidma_bdring.h"

XAxiDma_BdRing_t xaxidma_bdring_init(void *virt_base_addr, void *phys_base_addr,
                                     void *phys_high_addr, uint32_t max_buff_byte)
{
    XAxiDma_BdRing_t bdring;
    memset(&bdring, 0, sizeof(XAxiDma_BdRing_t));

    // ! check address validity
    if (((uintptr_t)phys_base_addr & (0x40 - 1)) != 0)
    {
        printf("Error: Invalid phys_base_addr=0x%08x \n", phys_base_addr);
        return bdring;
    }

    bdring.max_buff_byte = max_buff_byte;
    bdring.max_bd_count = ((uintptr_t)phys_high_addr - (uintptr_t)phys_base_addr + 1) / sizeof(XAxiDma_Bd_t);
    bdring.free_bd_count = bdring.max_bd_count;
    bdring.cur_bd_id = 0;
    uint32_t num_bd = 0;

    // init all to zero
    memset(virt_base_addr, 0, bdring.max_bd_count * sizeof(XAxiDma_Bd_t));

    XAxiDma_Bd_t bd;
    memset(&bd, 0, sizeof(XAxiDma_Bd_t));

    XAxiDma_Bd_t *phys_ptr = (XAxiDma_Bd_t *)phys_base_addr;
    XAxiDma_Bd_t *virt_ptr = (XAxiDma_Bd_t *)virt_base_addr;
    for (int i = 0; i < bdring.max_bd_count; i++)
    {
        bd.nxt_desc = (uintptr_t)&phys_ptr[i + 1]; // ? msb: link to next bd
        bd.id = i;
        virt_ptr[i] = bd;
    }
    // link the last one to first
    virt_ptr[bdring.max_bd_count - 1].nxt_desc = (uintptr_t)&phys_ptr[0];

    bdring.phys_head = &phys_ptr[0];
    bdring.phys_tail = &phys_ptr[bdring.max_bd_count - 1];

    bdring.virt_head = &virt_ptr[0];
    bdring.virt_tail = &virt_ptr[bdring.max_bd_count - 1];

    return bdring;
}

int32_t xaxidma_bdring_allocate(XAxiDma_BdRing_t *self, uint32_t num_bd,
                                XAxiDma_BdRing_t *allocate)
{
    XAxiDma_BdRing_t bdring;
    memset(&bdring, 0, sizeof(bdring));

    if (num_bd > self->free_bd_count || num_bd == 0)
    {
        printf(
            "Error: Invalid value of num_bd, self->free_bd_count=%i num_bd=%i \n",
            self->free_bd_count, num_bd);
        return EXIT_FAILURE;
    }

    // Allocate for new bdring
    bdring.max_buff_byte = self->max_buff_byte;
    bdring.num_bd = num_bd;
    bdring.phys_head = &self->phys_head[self->cur_bd_id];
    bdring.phys_tail = &self->phys_head[self->cur_bd_id + num_bd - 1];
    bdring.virt_head = &self->virt_head[self->cur_bd_id];
    bdring.virt_tail = &self->virt_head[self->cur_bd_id + num_bd - 1];

    bdring.virt_tail->nxt_desc = (uintptr_t)&bdring.phys_head[0]; // ? msb

    self->free_bd_count -= num_bd;
    self->cur_bd_id += num_bd;

    // to allocate
    *allocate = bdring;
    return EXIT_SUCCESS;
}
