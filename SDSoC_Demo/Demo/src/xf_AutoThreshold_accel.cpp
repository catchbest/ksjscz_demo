/***************************************************************************
Copyright (c) 2016, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
may be used to endorse or promote products derived from this software 
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/

#include "xf_AutoThreshold_config.h"

#pragma SDS data access_pattern("_src.data":SEQUENTIAL, "_dst.data":SEQUENTIAL)
#pragma SDS data copy("_src.data"[0:"_src.size"], "_dst.data"[0:"_dst.size"])
#pragma SDS data mem_attribute("_src.data":NON_CACHEABLE|PHYSICAL_CONTIGUOUS)
#pragma SDS data mem_attribute("_dst.data":NON_CACHEABLE|PHYSICAL_CONTIGUOUS)
#pragma SDS data data_mover("_src.data":AXIDMA_SIMPLE)
#pragma SDS data data_mover("_dst.data":AXIDMA_SIMPLE)
void threshold_accel(xf::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC8> &_src,xf::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC8> &_dst, unsigned char &Otsuval)
{
	xf::Threshold<XF_THRESHOLD_TYPE_BINARY,XF_8UC1,HEIGHT, WIDTH, XF_NPPC8>(_src,_dst,Otsuval,0,0);
}



#pragma SDS data access_pattern("_src.data":SEQUENTIAL)
#pragma SDS data copy("_src.data"[0:"_src.size"])
void otsuthreshold_accel(xf::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC8> &_src, unsigned char &Otsuval)
{
	xf::OtsuThreshold<XF_8UC1, HEIGHT, WIDTH, XF_NPPC8>(_src, Otsuval);
}

