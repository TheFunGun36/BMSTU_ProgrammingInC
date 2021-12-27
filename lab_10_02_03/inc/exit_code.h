#ifndef EXIT_CODE_H
#define EXIT_CODE_H

typedef enum exit_t
{
    exit_success,
    exit_invalid_cmd,
    exit_invalid_number,
    exit_empty_output,
    exit_no_memory
} exit_t;

#endif
