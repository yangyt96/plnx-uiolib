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

#include "xaxidma_sg.h"

// Hardware ----------------------------------------------------------------------------------

int32_t xaxidma_sg_tran(XAxiDma_Reg_t *self, XAxiDma_BdRing_t *tx_bdring)
{
    XAxiDma_DmaCr_Reg_t cr = self->mm2s_cr;
    XAxiDma_DmaSr_Reg_t sr = self->mm2s_sr;

    if (sr.SGIncld != 1)
    {
        printf("Error: Hardware doesn't support SG mode. \n");
        return EXIT_FAILURE;
    }

    cr.RS = 0;
    do
    {
        self->mm2s_cr = cr;
        sr = self->mm2s_sr;
    } while (sr.Halted != 1);

    self->mm2s_curdesc = (uintptr_t)tx_bdring->phys_head;

    cr.RS = 1;
    do
    {
        self->mm2s_cr = cr;
        sr = self->mm2s_sr;
    } while (sr.Halted != 0);

    self->mm2s_taildesc = (uintptr_t)tx_bdring->phys_tail;

    return EXIT_SUCCESS;
}

int32_t xaxidma_sg_recv(XAxiDma_Reg_t *self, XAxiDma_BdRing_t *rx_bdring)
{
    XAxiDma_DmaCr_Reg_t cr = self->s2mm_cr;
    XAxiDma_DmaSr_Reg_t sr = self->s2mm_sr;

    if (sr.SGIncld != 1)
    {
        printf("Error: Hardware doesn't support SG mode. \n");
        return EXIT_FAILURE;
    }

    cr.RS = 0;
    do
    {
        self->s2mm_cr = cr;
        sr = self->s2mm_sr;
    } while (sr.Halted != 1);

    self->s2mm_curdesc = (uintptr_t)rx_bdring->phys_head;

    cr.RS = 1;
    do
    {
        self->s2mm_cr = cr;
        sr = self->s2mm_sr;
    } while (sr.Halted != 0);

    self->s2mm_taildesc = (uintptr_t)rx_bdring->phys_tail;

    return EXIT_SUCCESS;
}

void xaxidma_sg_tx_setup()
{
    XAxiDma_BdRing_t bdring = xaxidma_bdring_init((void *)virt_tx_bd, (void *)TX_BD_BASE, (void *)TX_BD_HIGH, MAX_BD_PKT_BYTE);
    TxBdRing = bdring;
}

void xaxidma_sg_rx_setup()
{
    RxBdRing = xaxidma_bdring_init((void *)virt_rx_bd, (void *)RX_BD_BASE, (void *)RX_BD_HIGH, MAX_BD_PKT_BYTE);
    XAxiDma_BdRing_t bdring;

    xaxidma_bdring_allocate(&RxBdRing, RxBdRing.max_bd_count, &bdring);

    // Setup buffer address for each BD
    XAxiDma_Bd_t *bd_ptr = bdring.virt_head;
    uint32_t *rx_buff = (uint32_t *)RX_BUFF_BASE;
    for (int i = 0; i < bdring.num_bd; i++)
    {
        bd_ptr[i].ctrl.BuffLen = MAX_BD_PKT_BYTE;
        bd_ptr[i].buff_addr = (uintptr_t)&rx_buff[i * MAX_BD_PKT_BYTE / MIN_BD_PKT_BYTE];
        bd_ptr[i].stat.Cmplt = 0;
    }

    xaxidma_sg_recv(virt_dma, &bdring);
}

// Software ----------------------------------------------------------------------------------

void sg_start()
{
    printf("\n********** Start SG DMA **********\n");

    int dev_mem = open("/dev/mem", O_RDWR | O_SYNC);

    virt_dma = (XAxiDma_Reg_t *)mmap(NULL, sizeof(XAxiDma_Reg_t), PROT_READ | PROT_WRITE, MAP_SHARED, dev_mem, DMA_BASE_ADDR);
    virt_tx_bd = mmap(NULL, (TX_BD_HIGH - TX_BD_BASE + 1), PROT_READ | PROT_WRITE, MAP_SHARED, dev_mem, TX_BD_BASE);
    virt_rx_bd = mmap(NULL, (RX_BD_HIGH - RX_BD_BASE + 1), PROT_READ | PROT_WRITE, MAP_SHARED, dev_mem, RX_BD_BASE);
    virt_tx_buff = mmap(NULL, (TX_BUFF_HIGH - TX_BUFF_BASE + 1), PROT_READ | PROT_WRITE, MAP_SHARED, dev_mem, TX_BUFF_BASE);
    virt_rx_buff = mmap(NULL, (RX_BUFF_HIGH - RX_BUFF_BASE + 1), PROT_READ | PROT_WRITE, MAP_SHARED, dev_mem, RX_BUFF_BASE);

    close(dev_mem);

    xaxidma_reset(virt_dma);
    xaxidma_disable_mm2s_interrupt(virt_dma);
    xaxidma_disable_s2mm_interrupt(virt_dma);

    xaxidma_sg_tx_setup();
    xaxidma_sg_rx_setup();

    // XAxiDma_Reg_t dma = *virt_dma;
    // dma.mm2s_cr.IRQDelay = 100;
    // dma.s2mm_cr.IRQDelay = 100;
    // *virt_dma = dma;

    TxWrite = 0;
    TxDone = 0;
    RxDone = 0;
    RxRead = 0;
    Error = 0;
}

void sg_stop()
{
    xaxidma_reset(virt_dma);

    munmap(virt_dma, sizeof(XAxiDma_Reg_t));
    munmap(virt_tx_bd, TX_BD_HIGH - TX_BD_BASE + 1);
    munmap(virt_rx_bd, RX_BD_HIGH - RX_BD_BASE + 1);
    munmap(virt_tx_buff, TX_BUFF_HIGH - TX_BUFF_BASE + 1);
    munmap(virt_rx_buff, RX_BUFF_HIGH - RX_BUFF_BASE + 1);

    printf("\n********** Stop SG DMA **********\n");
}

void sg_restart_tx()
{
    xaxidma_sg_tx_setup();
    TxWrite = 0;
    TxDone = 0;
}

void sg_restart_rx()
{
    xaxidma_sg_rx_setup();
    RxDone = 0;
    RxRead = 0;
}

int32_t sg_sync_tx()
{
    // Wait until dma is halted
    XAxiDma_DmaSr_Reg_t sr;
    do
        sr = virt_dma->mm2s_sr;
    while (sr.Idle != 1);

    // Check error
    sr = virt_dma->mm2s_sr;
    Error += (sr.DMADecErr + sr.DMAIntErr + sr.DMASlvErr);
    if (Error > 0)
    {
        uintptr_t cur_phys_addr = virt_dma->mm2s_curdesc;
        uint32_t idx = (cur_phys_addr - TX_BD_BASE) / sizeof(XAxiDma_Bd_t);
        XAxiDma_Bd_t bd = TxBdRing.virt_head[idx];
        printf("Error: sg_sync_tx \n");
        xaxidma_print_dma_sr(virt_dma->mm2s_sr);
        xaxidma_print_bd(bd);
        return Error;
    }

    // check the bd is completed
    while (TxBdRing.virt_head[TxDone].stat.Cmplt != 0 && TxDone < TxBdRing.max_bd_count)
        TxDone++;

    if (TxDone != TxWrite)
    {
        printf("Error: sg_sync_tx - TxDone=%i TxWrite=%i \n", TxDone, TxWrite);
        uintptr_t cur_phys_addr = virt_dma->mm2s_curdesc;
        uint32_t idx = (cur_phys_addr - TX_BD_BASE) / sizeof(XAxiDma_Bd_t);
        XAxiDma_Bd_t bd = TxBdRing.virt_head[idx];
        printf("cur_phys_addr: 0x%08x \n", virt_dma->mm2s_curdesc);
        printf("idx: %i \n", idx);
        xaxidma_print_dma_sr(virt_dma->mm2s_sr);
        xaxidma_print_bd(bd);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int32_t sg_sync_rx()
{
    XAxiDma_DmaSr_Reg_t sr;
    do
        sr = virt_dma->s2mm_sr;
    while (sr.Halted != 0);

    // Check error
    sr = virt_dma->s2mm_sr;
    Error += (sr.DMADecErr + sr.DMAIntErr + sr.DMASlvErr);

    uintptr_t cur_phys_addr = virt_dma->s2mm_curdesc;
    uint32_t idx = (cur_phys_addr - RX_BD_BASE) / sizeof(XAxiDma_Bd_t);
    XAxiDma_Bd_t bd = RxBdRing.virt_head[idx];

    if (Error > 0)
    {

        printf("Error: sg_sync_tx \n");
        xaxidma_print_dma_sr(virt_dma->mm2s_sr);
        xaxidma_print_bd(bd);
        return Error;
    }

    while (RxBdRing.virt_head[RxDone].stat.Cmplt != 0 && RxDone < RxBdRing.max_bd_count)
        RxDone++;

    return EXIT_SUCCESS;
}

int32_t sg_tran_packets(Sg_Packets_t *packets)
{
    int status;

    XAxiDma_BdRing_t tx_bdring;
    status = xaxidma_bdring_allocate(&TxBdRing, packets->num_bd, &tx_bdring);
    if (status != EXIT_SUCCESS)
    {
        printf("Error: sg_send_packets - xaxidma_bdring_allocate \n");
        return status;
    }

    for (int i = 0; i < packets->num_bd; i++)
    {
        XAxiDma_Bd_t bd = tx_bdring.virt_head[i];
        bd.buff_addr = packets->phys_addr[i];
        bd.ctrl.BuffLen = packets->dbytes[i];
        bd.ctrl.TXRX_EOF = 1;
        bd.ctrl.TXRX_SOF = 1;
        bd.stat.Cmplt = 0;
        tx_bdring.virt_head[i] = bd;
    }

    status = xaxidma_sg_tran(virt_dma, &tx_bdring);
    if (status != EXIT_SUCCESS)
    {
        printf("Error: sg_send_packets - xaxidma_sg_tran \n");
        return status;
    }

    TxWrite += packets->num_bd;

    return EXIT_SUCCESS;
}

int32_t sg_recv_packets(Sg_Packets_t *packets)
{
    if (packets->phys_addr == NULL || packets->virt_addr == NULL || packets->dbytes == 0)
    {
        printf("Error: sg_recv_packets - packets->phys_addr=%p packets->virt_addr=%p \n", packets->phys_addr, packets->virt_addr);
        return EXIT_FAILURE;
    }

    if ((RxDone - RxRead) < packets->num_bd)
    {
        printf("Error: sg_recv_packets - packets->num_bd=%i is more than accepted value \n", packets->num_bd);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < packets->num_bd; i++)
    {
        packets->dbytes[i] = RxBdRing.virt_head[i + RxRead].stat.TranBytes;
        packets->phys_addr[i] = RxBdRing.virt_head[i + RxRead].buff_addr;
        packets->virt_addr[i] = (uintptr_t)packets->phys_addr[i] - RX_BUFF_BASE + (uintptr_t)virt_rx_buff;
    }

    RxRead += packets->num_bd;

    return EXIT_SUCCESS;
}