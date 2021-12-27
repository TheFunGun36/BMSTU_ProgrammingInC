#include "dynamic_array.h"
#include <string.h>

int int_darr_add(int_darr_t *darr, int val)
{
    int exit_code = darr ? ARR_OK : ARR_INVALID_PTR;

    if (exit_code == ARR_OK)
    {
        if (!darr->data)
        {
            darr->size = 1;
            darr->allocated = DARR_MEMORY_INC;
            darr->data = malloc(DARR_MEMORY_INC * sizeof(int));

            if (darr->data)
                *darr->data = val;
            else
                exit_code = ARR_NO_MEMORY;
        }
        else
        {
            if (darr->size >= darr->allocated)
            {
                int *old_ptr = darr->data;
                darr->data = realloc(darr->data, (darr->allocated + DARR_MEMORY_INC) * sizeof(int));
                
                if (!darr->data)
                {
                    darr->data = old_ptr;
                    exit_code = ARR_NO_MEMORY;
                }
                else
                {
                    darr->allocated += DARR_MEMORY_INC;
                    darr->data[darr->size++] = val;
                }
            }
            else
            {
                darr->data[darr->size++] = val;
            }
        }
    }

    return exit_code;
}

void int_darr_free(int_darr_t *darr)
{
    free(darr->data);
    memset(darr, 0, sizeof(int_darr_t));
}
