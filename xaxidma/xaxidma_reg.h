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

#include <stdint.h>
#include <unistd.h>
#pragma once

/**
 * Naming Convention
 *
 * 1.) CAPS_UNDER: Constants, enum Constans
 * 2.) CamelCase_t: type, union, struct, enum tag
 * 3.) CamelCase: Global var
 * 4.) small_under: function, vars
 *
 * */

// MM2S Control and Status Register
#define XAXIDMA_MM2S_DMACR_OFFSET 0x00
#define XAXIDMA_MM2S_DMASR_OFFSET 0x04

// MM2S SG Mode
#define XAXIDMA_MM2S_CURDESC_OFFSET 0x08
#define XAXIDMA_MM2S_CURDESC_MSB_OFFSET 0x0c
#define XAXIDMA_MM2S_TAILDESC_OFFSET 0x10
#define XAXIDMA_MM2S_TAIL_DESC_MSB_OFFSET 0x14

// MM2S Direct Register Mode
#define XAXIDMA_MM2S_SA_OFFSET 0x18
#define XAXIDMA_MM2S_SA_MSB_OFFSET 0x1c
#define XAXIDMA_MM2S_LENGTH_OFFSET 0x28

// Scatter/Gather User and Cache
#define XAXIDMA_SG_CTL_OFFSET 0x2c

// S2MM Control and Status Register
#define XAXIDMA_S2MM_DMACR_OFFSET 0x30
#define XAXIDMA_S2MM_DMASR_OFFSET 0x34

// S2MM SG Mode
#define XAXIDMA_S2MM_CURDESC_OFFSET 0x38
#define XAXIDMA_S2MM_CURDESC_MSB_OFFSET 0x3c
#define XAXIDMA_S2MM_TAILDESC_OFFSET 0x40
#define XAXIDMA_S2MM_TAIL_DESC_MSB_OFFSET 0x44

// S2MM Direct Register Mode
#define XAXIDMA_S2MM_DA_OFFSET 0x48
#define XAXIDMA_S2MM_DA_MSB_OFFSET 0x4c
#define XAXIDMA_S2MM_LENGTH_OFFSET 0x58

// (MM2S/S2MM DMA Control Register – Offset 00h/30h)
typedef struct __attribute__((__packed__))
{
    uint8_t RS : 1;        // 0: RW - Run(1)/Stop(0)
    uint8_t pad0 : 1;      // 1: RO
    uint8_t Reset : 1;     // 2: RW
    uint8_t Keyhole : 1;   // 3: RW
    uint8_t CycBdEnbl : 1; // 4: RW
    uint8_t pad1 : 7;      // 11-5: RO
    uint8_t IOC_IrqEn : 1; // 12: RW
    uint8_t Dly_IrqEn : 1; // 13: RW
    uint8_t Err_IrqEn : 1; // 14: RW
    uint8_t pad2 : 1;      // 15: RO
    uint8_t IRQThreshold;  // 23-16: RW
    uint8_t IRQDelay;      // 31-24: RW
} XAxiDma_DmaCr_Reg_t;

// (MM2S/S2MM DMA Status Register – Offset 04h/34h)
typedef struct __attribute__((__packed__))
{
    uint8_t Halted : 1;      // 0: RO
    uint8_t Idle : 1;        // 1: RO
    uint8_t pad0 : 1;        // 2: RO
    uint8_t SGIncld : 1;     // 3: RO - 1=Enbl, 0=Disbl
    uint8_t DMAIntErr : 1;   // 4: RO
    uint8_t DMASlvErr : 1;   // 5: RO
    uint8_t DMADecErr : 1;   // 6: RO
    uint8_t pad1 : 1;        // 7: RO
    uint8_t SGIntErr : 1;    // 8: RO
    uint8_t SGSlvErr : 1;    // 9: RO
    uint8_t SGDecErr : 1;    // 10: RO
    uint8_t pad2 : 1;        // 11: RO
    uint8_t IOC_Irq : 1;     // 12: R/WC
    uint8_t Dly_Irq : 1;     // 13: R/WC
    uint8_t Err_Irq : 1;     // 14: R/WC
    uint8_t pad3 : 1;        // 15: RO
    uint8_t IRQThresholdSts; // 23-16: RO
    uint8_t IRQDelaySts;     // 31-24: RO
} XAxiDma_DmaSr_Reg_t;

// (MM2S/S2MM DMA Current Descriptor Pointer Register - Offset 08h/38h)
typedef uint32_t XAxiDma_CurDesc_Reg_t; // ! LSB 6-bit always zero, Alignment of 0x40

// (MM2S/S2MM DMA Current Descriptor Pointer Register - Offset 0Ch/3Ch)
typedef uint32_t XAxiDma_CurDesc_Msb_Reg_t;

// (MM2S/S2MM DMA Tail Descriptor Pointer Register - Offset 10h/40h)
typedef uint32_t XAxiDma_TailDesc_Reg_t; // ! LSB 6-bit always zero, Alignment of 0x40

// (MM2S/S2MM DMA Tail Descriptor Pointer Register – Offset 14h/44h)
typedef uint32_t XAxiDma_TailDesc_Msb_Reg_t;

// (MM2S DMA Source Address Register – Offset 18h)
typedef uint32_t XAxiDma_Sa_Reg_t;

// (MM2S DMA Source Address Register – Offset 1Ch)
typedef uint32_t XAxiDma_Sa_Msb_Reg_t;

// (S2MM DMA Destination Address Register – Offset 48h)
typedef uint32_t XAxiDma_Da_Reg_t;

// (S2MM DMA Destination Address Register – Offset 4Ch)
typedef uint32_t XAxiDma_Da_Msb_Reg_t;

// (MM2S/S2MM DMA Transfer Length Register — Offset 28h/58h)
typedef struct __attribute__((__packed__))
{
    uint32_t Length : 26; // 25-0
    uint8_t pad0 : 6;     // 31-26
} XAxiDma_Length_Reg_t;

// SG_CTL (Scatter/Gather User and Cache Control Register—Offset 2Ch)
typedef struct __attribute__((__packed__))
{
    uint8_t SG_CACHE : 4; // 3-0: (Default: 0b0011)
    uint8_t pad0 : 4;     // 7-4
    uint8_t SG_USER : 4;  // 11-8
    uint32_t pad1 : 20;   // 31-12
} XAxiDma_Sg_Ctl_Reg_t;

/***********************************************************************
 * AXI DMA Register
 ***********************************************************************/
typedef struct __attribute__((__packed__))
{
    XAxiDma_DmaCr_Reg_t mm2s_cr;                  // 0x00
    XAxiDma_DmaSr_Reg_t mm2s_sr;                  // 0x04
    XAxiDma_CurDesc_Reg_t mm2s_curdesc;           // 0x08: W(DMACR.RS=0 & DMASR.Halted=1)
    XAxiDma_CurDesc_Msb_Reg_t mm2s_curdesc_msb;   // 0x0c
    XAxiDma_TailDesc_Reg_t mm2s_taildesc;         // 0x10: W(DMACR.RS=1 & DMASR.Halted=0)
    XAxiDma_TailDesc_Msb_Reg_t mm2s_taildesc_msb; // 0x14
    XAxiDma_Sa_Reg_t mm2s_sa;                     // 0x18
    XAxiDma_Sa_Msb_Reg_t mm2s_sa_msb;             // 0x1c
    uint64_t pad0;                                // 0x20
    XAxiDma_Length_Reg_t mm2s_length;             // 0x28
    XAxiDma_Sg_Ctl_Reg_t sg_ctl;                  // 0x2c
    XAxiDma_DmaCr_Reg_t s2mm_cr;                  // 0x30
    XAxiDma_DmaSr_Reg_t s2mm_sr;                  // 0x34
    XAxiDma_CurDesc_Reg_t s2mm_curdesc;           // 0x38: W(DMACR.RS=0 & DMASR.Halted=1)
    XAxiDma_CurDesc_Msb_Reg_t s2mm_curdesc_msb;   // 0x3c
    XAxiDma_TailDesc_Reg_t s2mm_taildesc;         // 0x40: W(DMACR.RS=1 & DMASR.Halted=0)
    XAxiDma_TailDesc_Msb_Reg_t s2mm_taildesc_msb; // 0x44
    XAxiDma_Da_Reg_t s2mm_da;                     // 0x48
    XAxiDma_Da_Msb_Reg_t s2mm_da_msb;             // 0x4c
    uint64_t pad1;                                // 0x50
    XAxiDma_Length_Reg_t s2mm_length;             // 0x58
} XAxiDma_Reg_t;

void xaxidma_reset(XAxiDma_Reg_t *dma);
void xaxidma_disable_mm2s_interrupt(XAxiDma_Reg_t *dma);
void xaxidma_disable_s2mm_interrupt(XAxiDma_Reg_t *dma);