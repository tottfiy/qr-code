# Encryption and QR generation

## Compilation
To compile the program, use the following command:
```bash
gcc main.c input.c encryption.c qr.c -o ../app/qrgen -lcrypto -lqrencode -ljpeg
```

## Running the Program
Run the compiled program with:
```bash
./qrgen
```

## Source Files
- `encryption.c`: Contains functions for key generation, encryption, and decryption.
- `input.c`: Handles user input for the plaintext message.
- `main.c`: Initializes OpenSSL, manages encryption and decryption processes.
- `qr.c`: Generation of QR code.
- `qr.h`: Header file defining function prototypes and includes necessary libraries.

```

