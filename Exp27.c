#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate (base^exponent) % modulus efficiently
unsigned long long modExp(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    unsigned long long result = 1;
    base = base % modulus;
    
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    
    return result;
}

// Function to encrypt the message
void encrypt(unsigned long long *message, unsigned long long *encrypted, unsigned long long length, unsigned long long e, unsigned long long n) {
    for (unsigned long long i = 0; i < length; i++) {
        encrypted[i] = modExp(message[i], e, n);
    }
}

// Function to decrypt the encrypted message
void decrypt(unsigned long long *encrypted, unsigned long long *decrypted, unsigned long long length, unsigned long long d, unsigned long long n) {
    for (unsigned long long i = 0; i < length; i++) {
        decrypted[i] = modExp(encrypted[i], d, n);
    }
}

int main() {
    unsigned long long n, e, d; // RSA parameters
    unsigned long long message[100], encrypted[100], decrypted[100]; // Arrays for message, encrypted message, and decrypted message
    unsigned long long length; // Length of the message
    
    printf("Enter the modulus (n): ");
    scanf("%llu", &n);
    
    printf("Enter the public exponent (e): ");
    scanf("%llu", &e);
    
    printf("Enter the private exponent (d): ");
    scanf("%llu", &d);
    
    printf("Enter the length of the message: ");
    scanf("%llu", &length);
    
    printf("Enter the message (0 to 25 for each character):\n");
    for (unsigned long long i = 0; i < length; i++) {
        scanf("%llu", &message[i]);
    }
    
    // Encrypt the message
    encrypt(message, encrypted, length, e, n);
    
    printf("Encrypted message: ");
    for (unsigned long long i = 0; i < length; i++) {
        printf("%llu ", encrypted[i]);
    }
    printf("\n");
    
    // Decrypt the encrypted message
    decrypt(encrypted, decrypted, length, d, n);
    
    printf("Decrypted message: ");
    for (unsigned long long i = 0; i < length; i++) {
        printf("%llu ", decrypted[i]);
    }
    printf("\n");
    
    return 0;
}
