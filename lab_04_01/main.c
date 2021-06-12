#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "string_process.h"

#define TEST_PASSED 0
#define TEST_FAILED 1

int main()
{
    int exit_code = TEST_PASSED;

    if (exit_code == TEST_PASSED)
    {
        char *input_string = "Here's my phone number: 8 (800) 555-35-35";
        char *input_blacklist = "1234567890";
        int expected_result = 24;

        int result = my_strcspn(input_string, input_blacklist);
        exit_code = (expected_result == result) ? TEST_PASSED : TEST_FAILED;
    }

    if (exit_code == TEST_PASSED)
    {
        char *input_string = "abcdef";
        char *input_blacklist = "1234567890";
        int expected_result = 6;

        int result = my_strcspn(input_string, input_blacklist);
        exit_code = (expected_result == result) ? TEST_PASSED : TEST_FAILED;
    }

    if (exit_code == TEST_PASSED)
    {
        char *input_string = "abcdef0";
        char *input_blacklist = "1234567890";
        int expected_result = 6;

        int result = my_strcspn(input_string, input_blacklist);
        exit_code = (expected_result == result) ? TEST_PASSED : TEST_FAILED;
    }

    if (exit_code == TEST_PASSED)
    {
        char *input_string = "0abcdef";
        char *input_blacklist = "1234567890";
        int expected_result = 0;

        int result = my_strcspn(input_string, input_blacklist);
        exit_code = (expected_result == result) ? TEST_PASSED : TEST_FAILED;
    }

    if (exit_code == TEST_PASSED)
    {
        char *input_string = "abcdef0";
        char *input_blacklist = "qwertyuiopasdfghjklzxcvbnm";
        int expected_result = 0;

        int result = my_strcspn(input_string, input_blacklist);
        exit_code = (expected_result == result) ? TEST_PASSED : TEST_FAILED;
    }

    if (exit_code == TEST_PASSED)
    {
        char *input_string = "";
        char *input_blacklist = "qwertyuiopasdfghjklzxcvbnm";
        int expected_result = 0;

        int result = my_strcspn(input_string, input_blacklist);
        exit_code = (expected_result == result) ? TEST_PASSED : TEST_FAILED;
    }

    if (exit_code == TEST_PASSED)
    {
        char *input_string = "nice";
        char *input_blacklist = "";
        int expected_result = 4;

        int result = my_strcspn(input_string, input_blacklist);
        exit_code = (expected_result == result) ? TEST_PASSED : TEST_FAILED;
    }

    if (exit_code == TEST_PASSED)
    {
        char *input_string = "Testing level: \\b\\";
        char *input_blacklist = "b";
        int expected_result = 16;

        int result = my_strcspn(input_string, input_blacklist);
        exit_code = (expected_result == result) ? TEST_PASSED : TEST_FAILED;
    }

    return exit_code;
}
