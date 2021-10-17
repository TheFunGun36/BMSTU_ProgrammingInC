#ifndef EXIT_CODE_H
#define EXIT_CODE_H

typedef enum exit_t
{
    exit_success,
    exit_no_memory,
    exit_eof,
    exit_invalid_input,
    exit_output_failure,
    exit_internal_error
} exit_t;

#endif
