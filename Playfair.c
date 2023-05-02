#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5
char matrix[SIZE][SIZE];
const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
void generate_matrix(char *key) {
    char temp[strlen(key) + sizeof(alphabet)];
    strcpy(temp, key);
    strcat(temp, alphabet);
    int i, j, k = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            matrix[i][j] = temp[k++];
        }
    }
}
void find_positions(char c1, char c2, int *x1, int *y1, int *x2, int *y2) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == c1) {
                *x1 = i;
                *y1 = j;
            }
            if (matrix[i][j] == c2) {
                *x2 = i;
                *y2 = j;
            }
        }
    }
}
void playfair_cipher(char *plaintext, char *key, char *ciphertext) {
    generate_matrix(key);
    char temp[strlen(plaintext) + 1];
    int i, j = 0;
    for (i = 0; i < strlen(plaintext); i++) {
        if (plaintext[i] != ' ') {
            temp[j++] = plaintext[i];
        }
    }
    if (j % 2 != 0) {
        temp[j++] = 'x';
    }
    temp[j] = '\0';
    for (i = 0; i < j; i += 2) {
        int x1, y1, x2, y2;
        find_positions(temp[i], temp[i+1], &x1, &y1, &x2, &y2);
        if (x1 == x2) {
            ciphertext[i] = matrix[x1][(y1 + 1) % SIZE];
            ciphertext[i+1] = matrix[x2][(y2 + 1) % SIZE];
        } else if (y1 == y2) {
            ciphertext[i] = matrix[(x1 + 1) % SIZE][y1];
            ciphertext[i+1] = matrix[(x2 + 1) % SIZE][y2];
        } else {
            ciphertext[i] = matrix[x1][y2];
            ciphertext[i+1] = matrix[x2][y1];
        }
    }
    ciphertext[j] = '\0';
}
int main() {
    char plaintext[100], key[100], ciphertext[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    playfair_cipher(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Plaintext:%s",plaintext);
    return 0;
}
