# RSA Encryption Program

## Compilation
To compile the program, use the following command:
```bash
gcc main.c input.c encryption.c -o encrypt -lcrypto
```

## Running the Program
Run the compiled program with:
```bash
./encrypt
```

## Source Files
- `encryption.c`: Contains functions for key generation, encryption, and decryption.
- `input.c`: Handles user input for the plaintext message.
- `main.c`: Initializes OpenSSL, manages encryption and decryption processes.
- `qr.h`: Header file defining function prototypes and includes necessary libraries.

```
Feel free to adjust any part as necessary!
