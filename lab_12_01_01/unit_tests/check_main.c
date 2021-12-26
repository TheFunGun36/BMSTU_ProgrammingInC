#include "check_arrayworks.h"

int main()
{
    int exit_code = 0;
    exit_code += check_key();
    exit_code += check_mysort();
    return exit_code;
}
