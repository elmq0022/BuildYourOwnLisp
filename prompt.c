#include <stdio.h>

/* Declare a buffer for the user input of size 2048 */
static char input[2048];

int main(int argc, char** argv){

    /* Print Version and Exit Information */
    puts("Lispy Version 0.0.1");
    puts("Press Ctrl+C to Exit\n");

    /* In a never ending loop */
    while (1) {

        /* the prompt */
        fputs("lispy> ", stdout);

        /* read a line of user input of maximum size 2048 */
        fgets(input, 2048, stdin);

        /* echo input back to user */
        printf("No you're a %s", input);

    }

    return 0;
}
