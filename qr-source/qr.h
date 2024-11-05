
#ifndef QR_H
#define QR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include "qrcodegen.h"
#include "stb_image.h"
#define MAX_LIMIT 500

// Error handling function
void handleErrors();

// Function to generate a new RSA key
EVP_PKEY *generateKey(int bits);

// Function to print the public key to stdout
void printPublicKey(EVP_PKEY *pkey);

// Function to print the private key to stdout
void printPrivateKey(EVP_PKEY *pkey);

// Function to encrypt the plaintext using the public key
int encrypt(EVP_PKEY *pkey, const unsigned char *plaintext, size_t plaintext_len, unsigned char **ciphertext);

// Function to decrypt the ciphertext using the private key
int decrypt(EVP_PKEY *pkey, const unsigned char *ciphertext, size_t ciphertext_len, unsigned char **plaintext);

// Function to handle user input
char * input_handler();

// Function to encode text into QR format
void genQR(const char *text, const char *filename, int quality);

// Function to print QR code
// void printQr(const uint8_t qrcode[]);

#endif // QR_H
