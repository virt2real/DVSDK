# 
#  Copyright (c) 2010, Texas Instruments Incorporated
#  All rights reserved.
# 
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
# 
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
# 
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
# 
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
#

# location of the configured CE app partially linked object
CONFIGURED_CE_SUBSYSTEM_OBJ = ../configured_CE_subsystem/configured_CE_subsystem.o

# [EDIT THIS] path to the MVArm compiler 
CC=/db/toolsrc/library/vendors2005/mvl/arm/mvl5.0/montavista/pro/devkit/arm/v5t_le/armv5tl-montavista-linux-gnueabi/bin/gcc \
    -g -Wall -Os

# standard compile rule
%.o : %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<


# link our end-user application object files with the partially linked CE obj
app.out: app.o $(CONFIGURED_CE_SUBSYSTEM_OBJ)
	$(CC) -g -o $@ app.o $(CONFIGURED_CE_SUBSYSTEM_OBJ) -lpthread 

all: app.out

clean:
	rm -rf app.out *.o 

#
#  @(#) ti.sdo.ce.examples.apps.video_copy; 1, 0, 0,77; 12-2-2010 21:21:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

#

