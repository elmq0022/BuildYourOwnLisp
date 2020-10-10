#include <stdio.h>
#include <stdlib.h>

/* if compile on windows compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* fake readline function */
char* readline(char* prompt){
    fputs(prompt, stdio);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}

/* fake history function */
void add_history(char* unused) {}

/* otherwise use the readline headers */
#else
#include <readline/readline.h>
#include <readline/history.h>
#endif

int main(int argc, char** argv){

    puts("Lispy Version 0.0.1");
    puts("Press Ctrl+C to Exit\n");

    while (1) {

        /* the prompt */
        char* input = readline("lispy> ");
        add_history(input);

        printf("No you're a %s\n", input);
        free(input);

    }

    return 0;
}
