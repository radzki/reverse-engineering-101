#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MSA \m/_

int sum = 867;
int debug = 0;

int password_check(char *password) {

    int count = 0;
    for (int i = 0; i < strlen(password); i++) {
        count += password[i];
        if (debug) {
            printf("%d\n", count);
        }
    }
    return count == sum;
}

int main() {
    while (1) {
        char *input = malloc(100);
        printf("Enter your password: ");
        scanf("%s", input);
        if (password_check(input)) {
            printf("Your are now a hacker!\n");
            return 0;
        }
        else {
            printf("Wrong password! Lammer!\n");
        }
        free(input);
    }

}


