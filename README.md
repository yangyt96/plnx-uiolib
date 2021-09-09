# PetaLinux Userspace IO Library
Xilinx only provides the baremetal API which cannot be used in PetaLinux. If one would like to use the FPGA driver of Linux, one must learn the linux kernel to use the implemented hardware which is very complicated.For effecient way of embedded software development, the userspace I/O (https://www.kernel.org/doc/html/v4.12/driver-api/uio-howto.html) is introduced. However, the corresponding API which is similar to https://github.com/Xilinx/embeddedsw/tree/master/XilinxProcessorIPLib/drivers/axidma is not provided. So, the user is required to implement your own API.

Currently, it only provides the API of AMBA AXI4 DMA Scatter Gather mode and DMA Simple mode, which follows the user manual of xilinx:
https://www.xilinx.com/support/documentation/ip_documentation/axi_dma/v7_1/pg021_axi_dma.pdf

