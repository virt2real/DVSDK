#include <ti/sdo/ce/osal/Global.h>

static Global_ArmDspLinkConfigMemTableEntry memTable_all_x674[] = {
    {"SDRAM", 0xC2C00000, 0xC2C00000, 0x00300000, 1, 0},
    {"DSPLINKMEM", 0xC2F01000, 0xC2F01000, 0x000FF000, 1, 0},
    {"RESET_VECTOR", 0xC2F00000, 0xC2F00000, 0x00001000, 1, 0},
    {"DDRALGHEAP", 0xC3000000, 0xC3000000, 0x01000000, 0, 0},
    {NULL, 0, 0, 0, 0, 0}
};
