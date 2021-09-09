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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "xaxidma_reg.h"
#pragma once

int32_t xaxidma_simple_tran(XAxiDma_Reg_t *self, void *phys_tx_buff, uint32_t num_byte)
{
    XAxiDma_DmaCr_Reg_t cr = self->mm2s_cr;
    XAxiDma_DmaSr_Reg_t sr = self->mm2s_sr;

    if (sr.SGIncld == 1)
    {
        printf("Error: Simple DMA mode does not support SG. \n");
        return EXIT_FAILURE;
    }

    cr.RS = 1;
    do
    {
        self->mm2s_cr = cr;
        sr = self->mm2s_sr;
    } while (sr.Halted != 0);

    self->mm2s_sa = (uintptr_t)phys_tx_buff;
    self->mm2s_length.Length = num_byte;

    return EXIT_SUCCESS;
}

int32_t xaxidma_simple_recv(XAxiDma_Reg_t *self, void *phys_rx_buff, uint32_t num_byte)
{
    XAxiDma_DmaCr_Reg_t cr = self->s2mm_cr;
    XAxiDma_DmaSr_Reg_t sr = self->s2mm_sr;

    if (sr.SGIncld == 1)
    {
        printf("Error: Simple DMA mode does not support SG. \n");
        return EXIT_FAILURE;
    }

    cr.RS = 1;
    do
    {
        self->mm2s_cr = cr;
        sr = self->s2mm_sr;
    } while (sr.Halted != 0);

    self->s2mm_da = (uintptr_t)phys_rx_buff;
    self->s2mm_length.Length = num_byte;

    return EXIT_SUCCESS;
}