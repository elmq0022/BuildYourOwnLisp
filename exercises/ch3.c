#include <stdio.h>

void hello_n_times(int n){
    for (int i=0; i<n; i++){
        puts("Hello from FUNCTION");
    }
}


int main(int argc, char** argv) {
    for (int i = 0; i < 5; i++){
        puts("Hello world from FOR loop");
    }

    int i = 5;
    while (i > 0){
        puts("Hello world from WHILE loop");
        --i;
    }

    hello_n_times(5);

    return 0;
}



