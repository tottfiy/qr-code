
# **Source Files**
##### **QR generator**
- **qr.h**: Contains function declarations for all source files except `main()`.
- **input.c**: Handles user input and validation, prompting for re-entry on invalid data.
- **encryption.c**: Generates public and private keys, encrypts user data.
- **qrgen.c**: Generates and saves the QR code, sends it to the user along with the private key.
- **main.c**: Coordinates the execution of functions.
- **test.c**: Tests input validation and encryption/decryption processes.
##### **QR decryptor**
- **WIP**


# **Requirements**
- OpenSSL
- qrencode
- computer


# **Compilation**
##### To compile the programs, use:

- QR generator:

```bash
gcc main.c input.c encryption.c qrgen.c -o qrgen -lcrypto -lqrencode
````
- QR decryptor:
```bash
WIP.
