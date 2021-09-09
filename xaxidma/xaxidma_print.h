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
#include "xaxidma_reg.h"
#include "xaxidma_bd.h"
#include "xaxidma_bdring.h"
#pragma once

// -------------------------------------------------------------------
void xaxidma_print_dma_cr(XAxiDma_DmaCr_Reg_t var);
void xaxidma_print_dma_sr(XAxiDma_DmaSr_Reg_t var);
void xaxidma_print_dma_mm2s_desc(XAxiDma_Reg_t var);
void xaxidma_print_dma_s2mm_desc(XAxiDma_Reg_t var);

// -------------------------------------------------------------------
void xaxidma_print_bd_ctrl(XAxiDma_Bd_Control_t var);
void xaxidma_print_bd_stat(XAxiDma_Bd_Status_t var);
void xaxidma_print_bd(XAxiDma_Bd_t var);

// -------------------------------------------------------------------
void xaxidma_print_bdring(XAxiDma_BdRing_t var);

// -------------------------------------------------------------------
void xaxidma_print_offset_dma(XAxiDma_Reg_t *var);
void xaxidma_print_offset_bd(XAxiDma_Bd_t *var);