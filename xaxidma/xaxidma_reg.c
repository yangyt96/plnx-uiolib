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

#include "xaxidma_reg.h"

void xaxidma_reset(XAxiDma_Reg_t *dma)
{
    XAxiDma_DmaCr_Reg_t mm2s_cr = dma->mm2s_cr;
    XAxiDma_DmaCr_Reg_t s2mm_cr = dma->s2mm_cr;

    mm2s_cr.Reset = 1;
    s2mm_cr.Reset = 1;

    dma->mm2s_cr = mm2s_cr;
    dma->s2mm_cr = s2mm_cr;

    usleep(10);
}

void xaxidma_disable_mm2s_interrupt(XAxiDma_Reg_t *dma)
{
    XAxiDma_DmaCr_Reg_t cr = dma->mm2s_cr;

    cr.Dly_IrqEn = 0;
    cr.Err_IrqEn = 0;
    cr.IOC_IrqEn = 0;

    dma->mm2s_cr = cr;
}

void xaxidma_disable_s2mm_interrupt(XAxiDma_Reg_t *dma)
{
    XAxiDma_DmaCr_Reg_t cr = dma->s2mm_cr;

    cr.Dly_IrqEn = 0;
    cr.Err_IrqEn = 0;
    cr.IOC_IrqEn = 0;

    dma->s2mm_cr = cr;
}