def hill_encrypt(message, key):
    # Remove spaces and convert message to lowercase
    message = message.replace(" ", "").lower()
    
    # Pad the message with 'x' if its length is not divisible by 2
    if len(message) % 2 != 0:
        message += 'x'
    
    # Split the message into pairs of two characters
    pairs = [message[i:i+2] for i in range(0, len(message), 2)]
    
    # Convert characters to their corresponding numerical values (a=0, b=1, ..., z=25)
    numerical_values = [ord(ch) - ord('a') for pair in pairs for ch in pair]
    
    # Perform Hill cipher encryption
    encrypted_values = []
    for i in range(0, len(numerical_values), 2):
        x = numerical_values[i]
        y = numerical_values[i+1]
        encrypted_x = (key[0][0] * x + key[0][1] * y) % 26
        encrypted_y = (key[1][0] * x + key[1][1] * y) % 26
        encrypted_values.extend([encrypted_x, encrypted_y])
    
    # Convert numerical values back to characters
    encrypted_message = ''.join(chr(value + ord('a')) for value in encrypted_values)
    
    return encrypted_message


# Define the key matrix
key = [[9, 4], [5, 7]]

# Define the message
message = "meet me at the usual place at ten rather than eight oclock"

# Encrypt the message using the Hill cipher
encrypted_message = hill_encrypt(message, key)

# Print the encrypted message
print("Encrypted message:", encrypted_message)
