#include <stdio.h>
#include <stdlib.h>
#include "cmem.h"

#define BUF_SIZE	(720*576*2)
#define NUM_BUFFERS	4

struct buf_info {
	void *user_addr;
	unsigned long phy_addr;
};

struct buf_info buffers[NUM_BUFFERS];

main()
{
	void *pool;
	int i;

	CMEM_AllocParams  alloc_params;

	printf("calling cmem utilities\n");
	CMEM_init();

	alloc_params.type = CMEM_POOL;
	alloc_params.flags = CMEM_NONCACHED;
	alloc_params.alignment = 32;
	pool = CMEM_allocPool(0, &alloc_params);

	if (NULL == pool) {
		printf("Failed to allocate cmem pool\n");
		exit(1);
	}

	
	for (i=0; i < NUM_BUFFERS; i++) {
		buffers[i].user_addr = CMEM_alloc(BUF_SIZE, &alloc_params);
		if (buffers[i].user_addr) {
			buffers[i].phy_addr = CMEM_getPhys(buffers[i].user_addr);
			if (0 == buffers[i].phy_addr) {
				printf("Failed to get phy cmem buffer address\n");
				exit(1);
			}
		} else {
			printf("Failed to allocate cmem buffer\n");
			exit(1);
		}
		printf("Got %p from CMEM, phy = %p\n", buffers[i].user_addr,
			(void *)buffers[i].phy_addr);
	}
	printf("exiting \n");
}

