# Decryption and QR decoding

## Compilation
To compile the program, use the following command:
```bash
g++  decode.cpp main.c decryption.c -o ../app/decode -I/usr/include/opencv4 -lcrypt -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lssl -lcrypto -lzbar
```

## Running the Program
Run the compiled program with:
```bash
./decode
```

## Source Files
- `decode.cpp`: OpenCV reading and raw data extraction, ZBar scanning for QR code and getting Base64 encoded data.
- `decryption.c`: Handles decoding into binary and decryption of text.
- `main.c`: Initializes processes.
- `decode.hpp`: Header file defining function prototypes and includes necessary libraries.

```

