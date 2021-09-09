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

#include "xaxidma_print.h"

void xaxidma_print_dma_cr(XAxiDma_DmaCr_Reg_t var)
{
    printf("\n----- DMA CR REG -----\n");
    printf("RS: %i\n", var.RS);
    printf("Reset: %i\n", var.Reset);
    printf("Keyhole: %i\n", var.Keyhole);
    printf("CycBdEnbl: %i\n", var.CycBdEnbl);
    printf("IOC_IrqEn: %i\n", var.IOC_IrqEn);
    printf("Dly_IrqEn: %i\n", var.Dly_IrqEn);
    printf("Err_IrqEn: %i\n", var.Err_IrqEn);
    printf("IRQThreshold: %i\n", var.IRQThreshold);
    printf("IRQDelay: %i\n", var.IRQDelay);
    printf("\n");
}

void xaxidma_print_dma_sr(XAxiDma_DmaSr_Reg_t var)
{
    printf("\n----- DMA SR REG -----\n");
    printf("Halted: %i\n", var.Halted);
    printf("Idle: %i\n", var.Idle);
    printf("SGIncld: %i\n", var.SGIncld);
    printf("DMAIntErr: %i\n", var.DMAIntErr);
    printf("DMASlvErr: %i\n", var.DMASlvErr);
    printf("DMADecErr: %i\n", var.DMADecErr);
    printf("SGIntErr: %i\n", var.SGIntErr);
    printf("SGSlvErr: %i\n", var.SGSlvErr);
    printf("SGDecErr: %i\n", var.SGDecErr);
    printf("IOC_Irq: %i\n", var.IOC_Irq);
    printf("Dly_Irq: %i\n", var.Dly_Irq);
    printf("Err_Irq: %i\n", var.Err_Irq);
    printf("IRQThresholdSts: %i\n", var.IRQThresholdSts);
    printf("IRQDelaySts: %i\n", var.IRQDelaySts);
    printf("\n");
}

void xaxidma_print_dma_mm2s_desc(XAxiDma_Reg_t var)
{
    printf("----- DMA mm2s desc -----\n");
    printf("curdesc:      0x%08x \n", var.mm2s_curdesc);
    printf("curdesc msb:  0x%08x \n", var.mm2s_curdesc_msb);
    printf("taildesc:     0x%08x \n", var.mm2s_taildesc);
    printf("taildesc msb: 0x%08x \n", var.mm2s_taildesc_msb);
    printf("\n");
}

void xaxidma_print_dma_s2mm_desc(XAxiDma_Reg_t var)
{
    printf("----- DMA s2mm desc -----\n");
    printf("curdesc:      0x%08x \n", var.s2mm_curdesc);
    printf("curdesc msb:  0x%08x \n", var.s2mm_curdesc_msb);
    printf("taildesc:     0x%08x \n", var.s2mm_taildesc);
    printf("taildesc msb: 0x%08x \n", var.s2mm_taildesc_msb);
    printf("\n");
}

// -------------------------------------------------------------------

void xaxidma_print_bd_ctrl(XAxiDma_Bd_Control_t var)
{
    printf("----- DMA BD CTRL -----\n");
    printf("BuffLen: %i \n", var.BuffLen);
    printf("TXRX_EOF: %i \n", var.TXRX_EOF);
    printf("TXRX_SOF: %i \n", var.TXRX_SOF);
}

void xaxidma_print_bd_stat(XAxiDma_Bd_Status_t var)
{
    printf("----- DMA BD STAT -----\n");
    printf("TranBytes: %i \n", var.TranBytes);
    printf("_EOF_: %i \n", var._EOF_);
    printf("_SOF_: %i \n", var._SOF_);
    printf("DMAIntErr: %i \n", var.DMAIntErr);
    printf("DMASlvErr: %i \n", var.DMASlvErr);
    printf("DMADecErr: %i \n", var.DMADecErr);
    printf("Cmplt: %i \n", var.Cmplt);
}

void xaxidma_print_bd(XAxiDma_Bd_t var)
{
    printf("\n----- Buffer Descriptor -----\n");
    printf("NxtDesc:      0x%08x \n", var.nxt_desc);
    printf("NxtDesc MSB:  %p \n", var.nxt_desc_msb);
    printf("BuffAddr:     0x%08x \n", var.buff_addr);
    printf("BuffAddr MSB: %p \n", var.buff_addr_msb);
    printf("mcctl:        0x%08x \n", var.mcctl);
    printf("stride:       0x%08x \n", var.stride);
    for (int i = 0; i < 5; i++)
        printf("app[%i]: 0x%08x \n", i, var.app[i]);
    printf("id:       0x%08x \n", var.id);
    printf("stscntrl: 0x%08x \n", var.stscntrl);
    printf("dre:      0x%08x \n", var.dre);
    xaxidma_print_bd_ctrl(var.ctrl);
    xaxidma_print_bd_stat(var.stat);
    printf("\n");
}

// -------------------------------------------------------------------
void xaxidma_print_bdring(XAxiDma_BdRing_t var)
{
    printf("\n----- BD Ring -----\n");
    printf("max_buff_byte: %i \n", var.max_buff_byte);
    printf("virt_head:     0x%08x \n", var.virt_head);
    printf("virt_tail:     0x%08x \n", var.virt_tail);
    printf("phys_head:     0x%08x \n", var.phys_head);
    printf("phys_tail:     0x%08x \n", var.phys_tail);
    printf("max_bd_count:  %i \n", var.max_bd_count);
    printf("free_bd_count: %i \n", var.free_bd_count);
    printf("cur_bd_id:     %i \n", var.cur_bd_id);
    printf("num_bd:        %i \n", var.num_bd);
}

// -------------------------------------------------------------------

void xaxidma_print_dma_offset(XAxiDma_Reg_t *var)
{
    printf("mm2s_cr: %p \n", &var->mm2s_cr);
    printf("mm2s_sr: %p \n", &var->mm2s_sr);
    printf("mm2s_curdesc: %p \n", &var->mm2s_curdesc);
    printf("mm2s_curdesc_msb: %p \n", &var->mm2s_curdesc_msb);
    printf("mm2s_taildesc: %p \n", &var->mm2s_taildesc);
    printf("mm2s_taildesc_msb: %p \n", &var->mm2s_taildesc_msb);
    printf("mm2s_sa: %p \n", &var->mm2s_sa);
    printf("mm2s_sa_msb: %p \n", &var->mm2s_sa_msb);
    printf("mm2s_length: %p \n", &var->mm2s_length);
    printf("sg_ctl: %p \n", &var->sg_ctl);
    printf("s2mm_cr: %p \n", &var->s2mm_cr);
    printf("s2mm_sr: %p \n", &var->s2mm_sr);
    printf("s2mm_curdesc: %p \n", &var->s2mm_curdesc);
    printf("s2mm_curdesc_msb: %p \n", &var->s2mm_curdesc_msb);
    printf("s2mm_taildesc: %p \n", &var->s2mm_taildesc);
    printf("s2mm_taildesc_msb: %p \n", &var->s2mm_taildesc_msb);
    printf("s2mm_da: %p \n", &var->s2mm_da);
    printf("s2mm_da_msb: %p \n", &var->s2mm_da_msb);
    printf("s2mm_length: %p \n", &var->s2mm_length);
}

void xaxidma_print_bd_offset(XAxiDma_Bd_t *var)
{
    printf("nxt_desc: %p \n", &var->nxt_desc);
    printf("nxt_desc_msb: %p \n", &var->nxt_desc_msb);
    printf("buff_addr: %p \n", &var->buff_addr);
    printf("buff_addr_msb: %p \n", &var->buff_addr_msb);
    printf("mcctl: %p \n", &var->mcctl);
    printf("stride: %p \n", &var->stride);
    printf("ctrl: %p \n", &var->ctrl);
    printf("stat: %p \n", &var->stat);
    printf("app: %p \n", &var->app);
    printf("id: %i \n", &var->id);
    printf("stscntrl: %p \n", &var->stscntrl);
    printf("dre: %p \n", &var->dre);
}