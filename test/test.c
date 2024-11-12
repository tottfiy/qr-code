#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string.h>
#include "qrcodegen.h"
#include <jpeglib.h>

// Function to encrypt data using RSA public key
int encrypt_data(const char *data, unsigned char *encrypted, RSA *public_key) {
    int data_len = strlen(data);
    int rsa_len = RSA_size(public_key);
    
    // Encrypt the data
    int result = RSA_public_encrypt(data_len, (unsigned char*)data, encrypted, public_key, RSA_PKCS1_OAEP_PADDING);
    if(result == -1) {
        fprintf(stderr, "Encryption failed: %s\n", ERR_error_string(ERR_get_error(), NULL));
        return -1;
    }
    return result;
}

// Function to save QR code as JPEG
void save_qr_to_jpeg(const char *filename, const uint8_t *qr_data, int size) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *outfile;
    JSAMPROW row_pointer[1];
    int width = size;
    int height = size;
    int row_stride = width * 3;

    // Open output file
    outfile = fopen(filename, "wb");
    if (!outfile) {
        fprintf(stderr, "Error opening output file %s\n", filename);
        return;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    // Set compression parameters
    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;  // RGB
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_start_compress(&cinfo, TRUE);

    // Compress image (convert QR data to RGB for JPEG)
    while (cinfo.next_scanline < height) {
        row_pointer[0] = (JSAMPROW) &qr_data[cinfo.next_scanline * width];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    // Finish and close the file
    jpeg_finish_compress(&cinfo);
    fclose(outfile);
}

// Function to generate QR code
void generate_qr_code(const char *text, const char *filename) {
    uint8_t *qr_data;
    int size = qrcodegen_BUFFER_LEN;

    qrcodegen_Segment seg = qrcodegen_makeSegments(text);
    qr_data = qrcodegen_generate(seg, size);
    
    save_qr_to_jpeg(filename, qr_data, size);
    printf("QR Code saved as %s\n", filename);
}

int main() {
    // Load RSA public key
    FILE *public_key_file = fopen("public_key.pem", "rb");
    if (!public_key_file) {
        fprintf(stderr, "Unable to open public key file\n");
        return -1;
    }

    RSA *public_key = PEM_read_RSA_PUBKEY(public_key_file, NULL, NULL, NULL);
    if (!public_key) {
        fprintf(stderr, "Unable to load public key\n");
        return -1;
    }
    fclose(public_key_file);

    // Get text input from the user
    char input_text[1024];
    printf("Enter text to encrypt: ");
    fgets(input_text, sizeof(input_text), stdin);

    // Encrypt the text
    unsigned char encrypted[256];
    int encrypted_len = encrypt_data(input_text, encrypted, public_key);
    if (encrypted_len == -1) {
        return -1;
    }

    // Generate and save QR code with encrypted text
    char encrypted_text[256];
    memcpy(encrypted_text, encrypted, encrypted_len);
    encrypted_text[encrypted_len] = '\0'; // Null-terminate the string

    generate_qr_code((const char*)encrypted_text, "encrypted_qr_code.jpg");

    // Clean up
    RSA_free(public_key);
    return 0;
}
