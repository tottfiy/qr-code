#include "qr.h"

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

