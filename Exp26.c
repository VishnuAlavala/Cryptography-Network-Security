#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1)
        return 0;
    if (num <= 3)
        return 1;
    if (num % 2 == 0 || num % 3 == 0)
        return 0;
    
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    }
    
    return 1;
}

// Function to find the modular inverse of a number
int modInverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;
    
    if (m == 1)
        return 0;
    
    while (a > 1) {
        int q = a / m;
        int t = m;
        
        m = a % m;
        a = t;
        t = y;
        
        y = x - q * y;
        x = t;
    }
    
    if (x < 0)
        x += m0;
    
    return x;
}

// Function to generate a random prime number
int generatePrime() {
    int num;
    do {
        num = rand() % 100 + 10; // Generate a random number between 10 and 109
    } while (!isPrime(num));
    
    return num;
}

// Function to generate a new public and private key pair
void generateKeyPair(int *e, int *d, int *n) {
    srand(time(NULL)); // Initialize random seed
    
    int p = generatePrime(); // Generate first prime number
    int q = generatePrime(); // Generate second prime number
    
    *n = p * q; // Calculate modulus
    
    int phi = (*p - 1) * (*q - 1); // Calculate Euler's totient function
    
    do {
        *e = rand() % (phi - 2) + 2; // Generate a random public exponent (2 <= e < phi)
    } while (gcd(*e, phi) != 1); // Ensure e and phi are coprime
    
    *d = modInverse(*e, phi); // Calculate the modular inverse of e (private exponent d)
}

// Function to encrypt a message
void encrypt(int *message, int length, int e, int n, int *encrypted) {
    for (int i = 0; i < length; i++) {
        encrypted[i] = modExp(message[i], e, n);
    }
}

// Function to decrypt an encrypted message
void decrypt(int *encrypted, int length, int d, int n, int *decrypted) {
    for (int i = 0; i < length; i++) {
        decrypted[i] = modExp(encrypted[i], d, n);
    }
}

int main() {
    int e, d, n; // RSA parameters
    int message[100], encrypted[100], decrypted[100]; // Arrays for message, encrypted message, and decrypted message
    int length; // Length of the message
    
    printf("Enter the length of the message: ");
    scanf("%d", &length);
    
    printf("Enter the message (0 to 25 for each character):\n");
    for (int i = 0; i < length; i++) {
        scanf("%d", &message[i]);
    }
    
    generateKeyPair(&e, &d, &n); // Generate new public and private key pair
    
    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);
    
    encrypt(message, length, e, n, encrypted); // Encrypt the message
    
    printf("Encrypted message: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", encrypted[i]);
    }
    printf("\n");
    
    decrypt(encrypted, length, d, n, decrypted); // Decrypt the encrypted message
    
    printf("Decrypted message: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", decrypted[i]);
    }
    printf("\n");
    
    return 0;
}
