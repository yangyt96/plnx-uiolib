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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "xaxidma_bd.h"
#pragma once

typedef struct
{
    uint32_t max_buff_byte;
    XAxiDma_Bd_t *virt_head;
    XAxiDma_Bd_t *virt_tail;
    XAxiDma_Bd_t *phys_head;
    XAxiDma_Bd_t *phys_tail;
    uint32_t max_bd_count;
    uint32_t free_bd_count;
    uint32_t cur_bd_id; // starting id
    uint32_t num_bd;    // allocated num bd
} XAxiDma_BdRing_t;

XAxiDma_BdRing_t xaxidma_bdring_init(void *virt_base_addr, void *phys_base_addr, void *phys_high_addr, uint32_t max_buff_byte);
int32_t xaxidma_bdring_allocate(XAxiDma_BdRing_t *self, uint32_t num_bd, XAxiDma_BdRing_t *allocate);