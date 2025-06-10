#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pwd = "everybodylovesmsa";

int main() {
    while (1) {
        char *input = malloc(100);
        printf("Enter your password: ");
        scanf("%s", input);
        if (strcmp(input, pwd) == 0) {
            printf("Your are now a hacker!\n");
            return 0;
        }
        else {
            printf("Wrong password! Lammer!\n");
        }
        free(input);
    }
    return 0;
}