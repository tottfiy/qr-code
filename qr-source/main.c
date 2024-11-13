#include "qr.h"

void main() {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    EVP_PKEY *pkey = generateKey(2048);
    // Message to encrypt
    const char *message = input_handler();
    unsigned char *ciphertext = NULL;
    size_t ciphertext_len = encrypt(pkey, (unsigned char *)message, strlen(message), &ciphertext);
    savePrivateKey(pkey);
    printf("Private key was saved to private-key.pem\n");

    char *encoded_data = base64_encode(ciphertext);

    // printf("Ciphertext (hex): ");
    // for (size_t i = 0; i < ciphertext_len; i++) {
    //     printf("%02x", ciphertext[i]);
    // }
    // printf("\n");
    

    generate_qr_code(encoded_data, "../app/qr.jpg");  // Generate qr.jpg file

    // char* decoded_text = decoder("qr.jpg");
    // unsigned char *decoded_ciphertext = base64_decode(decoded_text, enclen);
    // unsigned char *plaintext = NULL;
    // size_t plaintext_len = decrypt(pkey, decoded_ciphertext, enclen, &plaintext);

    // unsigned char *plaintext = NULL;

    // size_t plaintext_len = decrypt(pkey, (char *)decoded_text, enclen, &plaintext);
    // printf("Decrypted text: ");
    // for (size_t i = 0; i < plaintext_len; i++) {
    //     printf("%c", plaintext[i]);
    // }
    // printf("\n");

    OPENSSL_free(ciphertext);
    EVP_PKEY_free(pkey);
    ERR_free_strings();
}
