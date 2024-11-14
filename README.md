
# **Source Files**
##### **QR generator**
- **qr.h**: Contains function declarations for all source files except `main()`.
- **input.c**: Handles user input and validation, prompting for re-entry on invalid data.
- **encryption.c**: Generates public and private keys, encrypts user data.
- **qrgen.c**: Generates and saves the QR code, sends it to the user along with the private key.
- **main.c**: Coordinates the execution of functions.

##### **QR decryptor**
- **decode.hpp**: Contains function declarations for all source files except `main()`.
- **decode.cpp**: Extracts data from QR code.
- **decryption.c**: Decodes and decrypts data from QR code.
- **main.c**: Coordinates the execution of functions.


# **Requirements**
- OpenSSL
- qrencode
- libjpeg
- zbar
- opencv

```bash
sudo apt-get install libjpeg-dev libqrencode-dev libopencv-dev zbar-tools libssl-dev libzbar-dev

```
# **Compilation**
##### To compile the programs, use:

- QR generator:

```bash
gcc main.c input.c encryption.c qr.c -o ../app/qrgen -lcrypto -lqrencode -ljpeg

```
- QR decryptor:
```bash
g++  decode.cpp main.c decryption.c -o ../app/decode -I/usr/include/opencv4 -lcrypt -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lssl -lcrypto -lzbar
