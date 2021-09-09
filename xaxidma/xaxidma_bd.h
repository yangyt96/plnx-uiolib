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
#pragma once

// Address Offset
#define XAXIDMA_BD_NXTDESC_OFFSET 0x00
#define XAXIDMA_BD_NXTDESC_MSB_OFFSET 0x04
#define XAXIDMA_BD_BUFFER_ADDRESS_OFFSET 0x08
#define XAXIDMA_BD_BUFFER_ADDRESS_MSB_OFFSET 0x0c
#define XAXIDMA_BD_CONTROL_OFFSET 0x18
#define XAXIDMA_BD_STATUS_OFFSET 0x1c
#define XAXIDMA_BD_APP0_OFFSET 0x20
#define XAXIDMA_BD_APP1_OFFSET 0x24
#define XAXIDMA_BD_APP2_OFFSET 0x28
#define XAXIDMA_BD_APP3_OFFSET 0x2c
#define XAXIDMA_BD_APP4_OFFSET 0x30

// (MM2S/S2MM Next Descriptor Pointer)
typedef uint32_t XAxiDma_Bd_NxtDesc_t;
typedef uint32_t XAxiDma_Bd_NxtDesc_Msb_t;

// (MM2S/S2MM Buffer Address)
typedef uint32_t XAxiDma_Bd_Buffer_Address_t;
typedef uint32_t XAxiDma_Bd_Buffer_Address_Msb_t;

// (MM2S/S2MM Control)
typedef struct __attribute__((__packed__))
{
    uint32_t BuffLen : 26; // 25-0
    uint8_t TXRX_EOF : 1;  // 26
    uint8_t TXRX_SOF : 1;  // 27
    uint8_t pad0 : 4;      // 31-28
} XAxiDma_Bd_Control_t;

// (MM2S/S2MM Status)
typedef struct __attribute__((__packed__))
{
    uint32_t TranBytes : 26; // 0-25
    uint8_t _EOF_ : 1;       // 26 (only for S2MM)
    uint8_t _SOF_ : 1;       // 27 (only for S2MM)
    uint8_t DMAIntErr : 1;   // 28
    uint8_t DMASlvErr : 1;   // 29
    uint8_t DMADecErr : 1;   // 30
    uint8_t Cmplt : 1;       // 31
} XAxiDma_Bd_Status_t;

// (MM2S/S2MM User Application Fields 0 to 4)
typedef uint32_t XAxiDma_Bd_App_t;

/***********************************************************************
 * MM2S/S2MM Buffer Descriptor
 ***********************************************************************/
typedef struct __attribute__((__packed__))
{
    XAxiDma_Bd_NxtDesc_t nxt_desc;                 // 0x00
    XAxiDma_Bd_NxtDesc_Msb_t nxt_desc_msb;         // 0x04
    XAxiDma_Bd_Buffer_Address_t buff_addr;         // 0x08
    XAxiDma_Bd_Buffer_Address_Msb_t buff_addr_msb; // 0x0c
    uint32_t mcctl;                                // 0x10
    uint32_t stride;                               // 0x14
    XAxiDma_Bd_Control_t ctrl;                     // 0x18
    XAxiDma_Bd_Status_t stat;                      // 0x1c
    XAxiDma_Bd_App_t app[5];                       // 0x20 - 0x30
    uint32_t id;                                   // 0x34: SW
    uint32_t stscntrl;                             // 0x38
    uint32_t dre;                                  // 0x3c
} XAxiDma_Bd_t;
