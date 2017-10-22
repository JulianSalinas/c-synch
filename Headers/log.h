#ifndef C_SYNCHRONIZATION_LOG_H
#define C_SYNCHRONIZATION_LOG_H

#include "main.h"
#include <time.h>

#define PAGING 1
#define SEGMENTATION 2

#define ALLOCATION 1
#define DEALLOCATION 2
#define FAIL 0

void write_to_log(int type, int is_paging, int process_id, int cell_number);

char * read_log();

#endif //C_SYNCHRONIZATION_LOG_H
