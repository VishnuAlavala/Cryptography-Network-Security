#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generate_cipher(char *keyword, char *cipher) {
    int i, j, k;
    int keyword_len = strlen(keyword);
    char remaining_letters[ALPHABET_SIZE];
    int remaining_letters_len = 0;
    int used[ALPHABET_SIZE] = {0};

    strcpy(cipher, keyword);

    for (i = 0; i < keyword_len; i++) {
        used[toupper(keyword[i]) - 'A'] = 1;
    }

    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (!used[i]) {
            remaining_letters[remaining_letters_len++] = 'A' + i;
        }
    }

    strcat(cipher, remaining_letters);
}

void encrypt(char *plaintext, char *keyword, char *ciphertext) {
    char cipher[ALPHABET_SIZE + 1];
    generate_cipher(keyword, cipher);

    int i;
    int plaintext_len = strlen(plaintext);

    for (i = 0; i < plaintext_len; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(cipher[plaintext[i] - 'a']);
            } else {
                ciphertext[i] = cipher[plaintext[i] - 'A'];
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0';
}

int main() {
    char plaintext[100];
    char keyword[100];
    char ciphertext[100];

    printf("Enter the plaintext message: ");
    fgets(plaintext, 100, stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter the keyword: ");
    fgets(keyword, 100, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    encrypt(plaintext, keyword, ciphertext);

    printf("The encrypted message is: %s\n", ciphertext);

    return 0;
}
