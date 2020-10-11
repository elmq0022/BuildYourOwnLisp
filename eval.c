#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

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

long eval_op(long x, char* op, long y) {
    if (strcmp(op, "+") == 0) {return x + y;}
    if (strcmp(op, "-") == 0) {return x - y;}
    if (strcmp(op, "*") == 0) {return x * y;}
    if (strcmp(op, "/") == 0) {return x / y;}
    if (strcmp(op, "%") == 0) {return x % y;}
    if (strcmp(op, "^") == 0) {return powl(x, y);}
    if (strcmp(op, "min") == 0) {return (x < y) ? x : y;}
    if (strcmp(op, "max") == 0) {return (x > y) ? x : y;}
    return 0;
}

long eval(mpc_ast_t* t) {
    if (strstr(t->tag, "number")){
        return atoi(t->contents);
    }
    
    char* op = t->children[1]->contents;

    long x = eval(t->children[2]);

    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }
    return x;
}



int main(int argc, char** argv){

    /* create some parsers */
    mpc_parser_t* Number    = mpc_new("number");
    mpc_parser_t* Operator  = mpc_new("operator");
    mpc_parser_t* Expr      = mpc_new("expr");
    mpc_parser_t* Lispy     = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
            "                                                                                   \
            number      : /-?[0-9]+/ ;                                                          \
            operator    : '+' | '-' | '*' | '/' | '%' | '^' | /min/ | /max/ ;                   \
            expr        : <number> | '(' <operator> <expr>+ ')' ;                               \
            lispy       : /^/ <operator> <expr>+ /$/ ;                                          \
            ",                                                                                  \
            Number, Operator, Expr, Lispy);


    puts("Lispy Version 0.0.1");
    puts("Press Ctrl+C to Exit\n");

    while (1) {

        /* the prompt */
        char* input = readline("lispy> ");
        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            /* on success print the AST */
            long result = eval(r.output);
            printf("%li\n", result);
            mpc_ast_delete(r.output);

        } else {
            /* otherwise print the error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);

    }

    mpc_cleanup(4, Number, Operator, Expr, Lispy);
    return 0;
}
