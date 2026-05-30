#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Simple black-box fuzzer that generates random byte
// strings that are passed as an argument into a compiled file to check for crashes
int main(int argc, char *argv[])
{
    srand(time(NULL));
    bool crash = false;
    time_t initial_Time = time(NULL);
    int num_Tests = 0;

    // Loop until illegal argument is found
    while (crash == false)
    {
        char input[256] = "./target '";
        char valid_char[63] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        // Fill input with 3 random byte characters using grammer based fuzzing
        for (int i = 0; i < 3; i++)
        {
            char byte = valid_char[rand() % 62];
            char str[4] = {byte, '\0'};
            strcat(input, str);
        }
        strcat(input, "'");
        int result = system(input);
        num_Tests++;
        // Check if the input causes an error
        if (result != 0)
        {
            crash = true;
            time_t finalTime = time(NULL);
            printf("Crash detected with input: %s\nNumber of tests: %d\nTotal Time: %fs\n",
                   input, num_Tests, difftime(finalTime, initial_Time));
        }
    }
    return 0;
}