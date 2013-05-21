
#include <xdc/std.h>
#include <ti/sdo/utils/trace/gt.h>

void temp_trace_init()
{
GT_init();
GT_set("*" "=01234567");
}
