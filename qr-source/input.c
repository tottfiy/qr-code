#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "qr.h" 

// Function to handle input from user
char * input_handler() {
    printf("Write your text (< 500 characters): \n");
    char str[MAX_LIMIT];

    if (fgets(str, MAX_LIMIT, stdin) == NULL) {
        printf("Error occurred\n");
        return NULL; // Return NULL on error
    }

    if (str[strlen(str) - 1] != '\n') {
        printf("Input too long. Please enter less than 500 characters.\n");
        return NULL; // Return NULL for too long input
    }

    // Remove the newline character
    str[strcspn(str, "\n")] = '\0';

    // Allocate memory for the return value
    char *point = malloc(strlen(str) + 1); // +1 for the null terminator
    if (point == NULL) {
        printf("Memory allocation failed\n");
        return NULL; // Return NULL if malloc fails
    }

    strcpy(point, str); // Copy the string to the allocated memory
    printf("You entered: %s\n", point);
    return point; // Return the pointer to the newly allocated string
}

