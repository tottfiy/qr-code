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

    // Check if input was too long
    if (str[strlen(str) - 1] != '\n') {
        printf("Input too long. Please enter less than 500 characters.\n");
        return;
    }

    // Remove the newline character, if present
    str[strcspn(str, "\n")] = '\0';

    // Print the valid input
    printf("You entered: %s\n", str);
}