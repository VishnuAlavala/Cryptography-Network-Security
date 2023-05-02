import string
a=input("Enter Plain Text:")
b=int(input("Enter Key:"))
plain_text=a
shift=b
alphabet=string.ascii_lowercase
shifted=alphabet[shift:] + alphabet[:shift]
table=str.maketrans(alphabet,shifted)
encrypted=plain_text.translate(table)
print("Cipher Text:",encrypted)
c=encrypted
shift=-b
alphabet=string.ascii_lowercase
shifted=alphabet[shift:] + alphabet[:shift]
table=str.maketrans(alphabet,shifted)
encrypted=c.translate(table)
print("Plain Text:",encrypted)

