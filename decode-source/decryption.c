#include "decode.hpp"

// Function to handle OPENSSL Errors
void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
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
