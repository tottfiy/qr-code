#include "../qr-source/qr.h"

int main() {
    // Load the private key from a PEM file
    FILE *key_file = fopen("private-key.pem", "r");
    if (!key_file) {
        perror("Error opening private key file");
        return 1;
    }

    EVP_PKEY *pkey = PEM_read_PrivateKey(key_file, NULL, NULL, NULL);
    fclose(key_file);

    if (!pkey) {
        fprintf(stderr, "Error reading private key from PEM file\n");
        ERR_print_errors_fp(stderr);
        return 1;
    }

    // Decode the QR code and base64 decode it
    char* decoded_text = decoder("qr.jpg");
    unsigned char *decoded_ciphertext = base64_decode(decoded_text);

    if (!decoded_ciphertext) {
        fprintf(stderr, "Base64 decoding failed\n");
        EVP_PKEY_free(pkey);
        return 1;
    }

    size_t len_dec = strlen((char *)decoded_ciphertext);
    unsigned char *plaintext = NULL;
    size_t plaintext_len = decrypt(pkey, decoded_ciphertext, len_dec, &plaintext);

    if (plaintext_len > 0) {
        printf("Decrypted text: %.*s\n", (int)plaintext_len, plaintext);
        OPENSSL_free(plaintext);
    } else {
        fprintf(stderr, "Decryption failed\n");
        ERR_print_errors_fp(stderr);
    }

    OPENSSL_free(decoded_ciphertext);
    EVP_PKEY_free(pkey);
    return 0;
}