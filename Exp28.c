#include <stdio.h>
#include <math.h>

// Function to calculate (base^exponent) % modulus efficiently
int modExp(int base, int exponent, int modulus) {
    int result = 1;
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

int main() {
    int q, a; // Public numbers
    int x, y; // Secret numbers
    int A, B; // Exchanged values
    int K1, K2; // Shared secret keys
    
    printf("Enter the prime number (q): ");
    scanf("%d", &q);
    
    printf("Enter the primitive root modulo (a): ");
    scanf("%d", &a);
    
    printf("Enter Alice's secret number (x): ");
    scanf("%d", &x);
    
    printf("Enter Bob's secret number (y): ");
    scanf("%d", &y);
    
    // Calculate A = (a^x) % q
    A = modExp(a, x, q);
    
    // Calculate B = (a^y) % q
    B = modExp(a, y, q);
    
    // Exchange A and B
    
    // Calculate shared secret key for Alice: K1 = (B^x) % q
    K1 = modExp(B, x, q);
    
    // Calculate shared secret key for Bob: K2 = (A^y) % q
    K2 = modExp(A, y, q);
    
    printf("Shared secret key for Alice: %d\n", K1);
    printf("Shared secret key for Bob: %d\n", K2);
    
    return 0;
}
