
import string
plaintext_alphabet = string.ascii_lowercase
ciphertext_alphabet = 'qwertyuiopasdfghjklzxcvbnm'
def substitution_cipher(plaintext):
    ciphertext = ''
    for char in plaintext:
        if char in plaintext_alphabet:
            index = plaintext_alphabet.index(char)
            ciphertext += ciphertext_alphabet[index]
        else:
            ciphertext += char
    return ciphertext
plaintext = input("Enter the Plaintext: ")
ciphertext = substitution_cipher(plaintext)
print("Cipher Text:", ciphertext)
print("Plain Text:",plaintext)
