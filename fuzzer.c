#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Simple black-box fuzzer that generates random byte
// strings that are passed as an argument into a compiled file to check for crashes.
int main(int argc, char *argv[])
{
    srand(time(NULL));
    bool crash = false;
    time_t initialTime = time(NULL);
    int numTests = 0;

    while (crash == false)
    {
        char input[256] = "./target '";
        for (int i = 0; i < 3; i++)
        {
            unsigned char byte = rand() % 256;
            if (byte == 0x0 || byte == 0x0A || byte == 0x27)
            {
                i--;
            }
            else
            {
                char str[2] = {byte, '\0'};
                strcat(input, str);
            }
        }
        strcat(input, "'");
        int result = system(input);
        numTests++;
        if (result != 0)
        {
            crash = true;
            time_t finalTime = time(NULL);
            printf("Crash detected with input: %s\nNumber of tests: %d\nTotal Time: %fs\n",
                   input, numTests, difftime(finalTime, initialTime));
        }
    }
    return 0;
}