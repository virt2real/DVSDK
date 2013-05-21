Example demonstrates two algorithms that request edma3Chan resources. These
consist of an EDMA/QDMA channel linked to a series of contiguous
PaRams, alongwith TCCs

The resource handles received also includes actual addresses of PaRams being
returned and programmed Shadow PaRams that can be copied to the actual paRam
addresses. 

ESR masks to trigger the EDMA trasnfer and IPR bit masks to check
for completion are also provided in the resource handle. 

A system call to the Low level Resource Manager directly is made and resources
are requested.
Any resource that might be held by either/both of the algorithms is not
granted to teh system. The free resources are granted persistenly to the
system.  
