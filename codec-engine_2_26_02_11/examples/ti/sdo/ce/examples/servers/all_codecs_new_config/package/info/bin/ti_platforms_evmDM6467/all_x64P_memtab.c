#include <ti/sdo/ce/osal/Global.h>

static Global_ArmDspLinkConfigMemTableEntry memTable_all_x64P[] = {
    {"DDR2", 0x8FA00000, 0x8FA00000, 0x00400000, 1, 0},
    {"DSPLINKMEM", 0x8FE00000, 0x8FE00000, 0x00100000, 1, 0},
    {"RESET_VECTOR", 0x8FF00000, 0x8FF00000, 0x00000080, 1, 0},
    {"DDRALGHEAP", 0x88000000, 0x88000000, 0x07A00000, 0, 0},
    {NULL, 0, 0, 0, 0, 0}
};
