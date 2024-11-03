#include <stdio.h>
#include <stdlib.h>
#define MAX_LIMIT 500

void input_handler() {
    printf("Write your text (< 500 characters): \n");
    char str[MAX_LIMIT];
    if (fgets(str, MAX_LIMIT, stdin) == NULL) {
        printf("Error occurred\n");
        return;
    }
    printf("%s", str);
}


int main() {
    input_handler();
    return 0;
}