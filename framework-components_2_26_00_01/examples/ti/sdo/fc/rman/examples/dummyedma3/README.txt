Example demonstrates an algorithm that requests an edma3Chan resource. This
consists of an EDMA/QDMA channel linked to a series of contiguous PaRams. 

The resource handle received also includes actual addresses of PaRams being
returned and programmed Shadow PaRams that can be copied to the actual paRam
addresses. 

ESR masks to trigger the EDMA trasnfer and IPR bit masks to check
for completion are also provided in the resource handle. 
