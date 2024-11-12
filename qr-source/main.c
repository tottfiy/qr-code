#include "qr.h"

void main() {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    EVP_PKEY *pkey = generateKey(2048);
    // Message to encrypt
    const char *message = input_handler();
    unsigned char *ciphertext = NULL;
    size_t ciphertext_len = encrypt(pkey, (unsigned char *)message, strlen(message), &ciphertext);
    printPrivateKey(pkey);

    char *encoded_data = base64_encode(ciphertext, ciphertext_len);
    printf("Ciphertext (hex): ");
    for (size_t i = 0; i < ciphertext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    unsigned char *plaintext = NULL;
    size_t plaintext_len = decrypt(pkey, (unsigned char *)ciphertext, ciphertext_len, &plaintext);
    printf("Decrypted text: ");
    for (size_t i = 0; i < plaintext_len; i++) {
        printf("%c", plaintext[i]);
    }
    printf("\n");

    generate_qr_code(encoded_data, "qr.jpg");  // Generate qr.jpg file

    OPENSSL_free(ciphertext);
    EVP_PKEY_free(pkey);
    ERR_free_strings();
}