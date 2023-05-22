#include <stdio.h>

// Function to generate subkeys for CMAC
void generateSubkeys(const unsigned char *key, int keyLength, unsigned char *subkey1, unsigned char *subkey2) {
    // Calculate the first subkey
    unsigned char L[16] = { 0 };
    unsigned char K1[16];

    // Apply the block cipher to the block of all 0 bits
    // Replace this line with your block cipher encryption function or library call
    // encryptBlock(L, key);

    // Perform the left shift on the resulting string
    for (int i = 0; i < keyLength; i++) {
        K1[i] = (L[i] << 1) | (L[i + 1] >> 7);
    }

    // Conditionally XOR with the constant
    if ((L[0] & 0x80) == 0x80) {
        K1[keyLength - 1] ^= 0x87;
    }

    // Copy the first subkey to the output
    memcpy(subkey1, K1, keyLength);

    // Calculate the second subkey
    unsigned char K2[16];

    // Apply the block cipher to the first subkey
    // Replace this line with your block cipher encryption function or library call
    // encryptBlock(K1, key);

    // Perform the left shift on the resulting string
    for (int i = 0; i < keyLength; i++) {
        K2[i] = (K1[i] << 1) | (K1[i + 1] >> 7);
    }

    // Conditionally XOR with the constant
    if ((K1[0] & 0x80) == 0x80) {
        K2[keyLength - 1] ^= 0x87;
    }

    // Copy the second subkey to the output
    memcpy(subkey2, K2, keyLength);
}

int main() {
    unsigned char key64[8] = {
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xAB, 0xCD, 0xEF
    };

    unsigned char subkey1_64[8];
    unsigned char subkey2_64[8];

    generateSubkeys(key64, 8, subkey1_64, subkey2_64);

    printf("Subkey 1 (64-bit): ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", subkey1_64[i]);
    }
    printf("\n");

    printf("Subkey 2 (64-bit): ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", subkey2_64[i]);
    }
    printf("\n\n");

    unsigned char key128[16] = {
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98,
        0x76, 0x54, 0x32, 0x10
    };

    unsigned char subkey1_128[16];
    unsigned char subkey2_128[16];

    generateSubkeys(key128, 16, subkey1_128, subkey2_128);

    printf("Subkey 1 (128-bit): ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", subkey1_128[i]);
    }
    printf("\n");

    printf("Subkey 2 (128-bit): ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", subkey2_128[i]);
    }
    printf("\n");

    return 0;
}
