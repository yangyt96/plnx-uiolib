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
#include <fcntl.h>  // open
#include <unistd.h> // close
#include <sys/mman.h>
#include "xaxidma_reg.h"
#include "xaxidma_bd.h"
#include "xaxidma_bdring.h"
#include "xaxidma_print.h"
#pragma once

#define DMA_BASE_ADDR (0x40400000)
#define DDR_BASE_ADDR (0x00000000)
#define MEM_BASE_ADDR (DDR_BASE_ADDR + 0x01000000)

#define TX_BD_BASE (MEM_BASE_ADDR + 0x00000000)
#define TX_BD_HIGH (MEM_BASE_ADDR + 0x0000FFFF)
#define RX_BD_BASE (MEM_BASE_ADDR + 0x00010000)
#define RX_BD_HIGH (MEM_BASE_ADDR + 0x0001FFFF)

#define TX_BUFF_BASE (MEM_BASE_ADDR + 0x00100000)
#define TX_BUFF_HIGH (MEM_BASE_ADDR + 0x002fffff)
#define RX_BUFF_BASE (MEM_BASE_ADDR + 0x00300000)
#define RX_BUFF_HIGH (MEM_BASE_ADDR + 0x004fffff)

#define MIN_BD_PKT_BYTE (sizeof(uint32_t))
#define MAX_BD_PKT_BYTE (MIN_BD_PKT_BYTE * 66) // (MIN_BD_PKT_BYTE * (NOCPE_PE_NUM + 1))

typedef struct
{
    void **virt_addr;
    void **phys_addr;
    uint32_t *dbytes;
    uint32_t num_bd;
} Sg_Packets_t;

/**
 * Variables
 **/
inline volatile XAxiDma_Reg_t *virt_dma;
inline volatile void *virt_tx_bd;
inline volatile void *virt_rx_bd;
inline volatile void *virt_tx_buff;
inline volatile void *virt_rx_buff;

inline volatile XAxiDma_BdRing_t TxBdRing; // max count
inline volatile XAxiDma_BdRing_t RxBdRing; // max count
inline volatile uint32_t Error;
inline volatile uint32_t TxDone;  // HW indicator
inline volatile uint32_t RxDone;  // HW indicator
inline volatile uint32_t TxWrite; // SW indicator
inline volatile uint32_t RxRead;  // SW indicator

/**
 * Functions
 **/

// Hardware
int32_t xaxidma_sg_tran(XAxiDma_Reg_t *self, XAxiDma_BdRing_t *tx_bdring);
int32_t xaxidma_sg_recv(XAxiDma_Reg_t *self, XAxiDma_BdRing_t *rx_bdring);
void xaxidma_sg_tx_setup();
void xaxidma_sg_rx_setup();

// Software
void sg_start();
void sg_stop();
void sg_restart_tx();
void sg_restart_rx();
int32_t sg_sync_tx();
int32_t sg_sync_rx(); // called after sg_sync_tx
int32_t sg_tran_packets(Sg_Packets_t *packets);
int32_t sg_recv_packets(Sg_Packets_t *packets);
