#include "qr.h"

// Base64 encode function
char *base64_encode(const unsigned char *input) {
    size_t length = strlen((const char *)input); // Calculate the length inside the function
    size_t encoded_length = 4 * ((length + 2) / 3); // Base64 encoding requires 4 chars for every 3 bytes
    char *encoded = (char *)malloc(encoded_length + 1); // +1 for the null terminator

    if (encoded == NULL) {
        perror("Base64 encoding failed");
        return NULL;
    }

    EVP_EncodeBlock((unsigned char *)encoded, input, length);
    return encoded;
}


unsigned char *base64_decode(const char *input) {
    size_t length = strlen(input); // Calculate the length inside the function
    size_t decoded_length = (length / 4) * 3;
    unsigned char *decoded = (unsigned char *)malloc(decoded_length + 1); // +1 for the null terminator

    if (decoded == NULL) {
        perror("Base64 decoding failed");
        return NULL;
    }

    // Decode the base64 string
    int result_len = EVP_DecodeBlock(decoded, (const unsigned char *)input, length);
    if (result_len < 0) {
        perror("Base64 decoding failed");
        free(decoded);
        return NULL;
    }

    return decoded;
}

// Function to handle OPENSSL Errors
void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

// Function to generate a new RSA key
EVP_PKEY *generateKey(int bits) {
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) handleErrors();

    if (EVP_PKEY_keygen_init(ctx) <= 0) handleErrors();
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits) <= 0) handleErrors();

    EVP_PKEY *pkey = NULL;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) handleErrors();

    EVP_PKEY_CTX_free(ctx);
    return pkey;
}

// Function to print the public key to stdout
void printPublicKey(EVP_PKEY *pkey) {
    PEM_write_PUBKEY(stdout, pkey);
}

// Function to print the private key to stdout
void printPrivateKey(EVP_PKEY *pkey) {
    PEM_write_PrivateKey(stdout, pkey, NULL, NULL, 0, NULL, NULL);
}

void savePrivateKey(EVP_PKEY *pkey) {
    FILE * file = fopen("private-key.pem", "wb");
    if (!file) {
        perror("Failed to open file for writing private key");
        handleErrors();
    }

    if (PEM_write_PrivateKey(file, pkey, NULL, NULL, 0, NULL, NULL) <= 0) {
        perror("Failed to write private key to file");
        handleErrors();
    }
    fclose(file);
}

// Function to encrypt the plaintext using the public key
int encrypt(EVP_PKEY *pkey, const unsigned char *plaintext, size_t plaintext_len, unsigned char **ciphertext) {
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (!ctx) handleErrors();

    if (EVP_PKEY_encrypt_init(ctx) <= 0) handleErrors();

    size_t ciphertext_len;
    if (EVP_PKEY_encrypt(ctx, NULL, &ciphertext_len, plaintext, plaintext_len) <= 0) handleErrors();

    *ciphertext = OPENSSL_malloc(ciphertext_len);
    if (*ciphertext == NULL) handleErrors();

    if (EVP_PKEY_encrypt(ctx, *ciphertext, &ciphertext_len, plaintext, plaintext_len) <= 0) handleErrors();

    EVP_PKEY_CTX_free(ctx);
    return ciphertext_len;
}

// Function to decrypt the ciphertext using the private key
int decrypt(EVP_PKEY *pkey, const unsigned char *ciphertext, size_t ciphertext_len, unsigned char **plaintext) {
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (!ctx) handleErrors();

    if (EVP_PKEY_decrypt_init(ctx) <= 0) handleErrors();

    size_t plaintext_len;
    if (EVP_PKEY_decrypt(ctx, NULL, &plaintext_len, ciphertext, ciphertext_len) <= 0) handleErrors();

    *plaintext = OPENSSL_malloc(plaintext_len);
    if (*plaintext == NULL) handleErrors();

    if (EVP_PKEY_decrypt(ctx, *plaintext, &plaintext_len, ciphertext, ciphertext_len) <= 0) handleErrors();

    EVP_PKEY_CTX_free(ctx);
    return plaintext_len;
}

