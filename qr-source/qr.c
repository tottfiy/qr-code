#include "qr.h"

void generate_qr_code(const char *data, const char *filename) {
    // Generate QR code with larger size (increase module size to 10 for better readability)
    int module_size = 10;  // Larger module size for better readability
    QRcode *qrcode = QRcode_encodeString(data, 0, QR_ECLEVEL_L, QR_MODE_8, module_size);
    if (!qrcode) {
        fprintf(stderr, "Failed to generate QR code\n");
        return;
    }

    // Create JPEG structure
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // Set up JPEG error handling
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    // Open the output file
    FILE *outfile = fopen(filename, "wb");
    if (!outfile) {
        fprintf(stderr, "Failed to open file for writing\n");
        QRcode_free(qrcode);
        return;
    }

    // Set the compression destination to the file
    jpeg_stdio_dest(&cinfo, outfile);

    // Set the image parameters
    cinfo.image_width = qrcode->width * module_size;
    cinfo.image_height = qrcode->width * module_size;
    cinfo.input_components = 3; // RGB
    cinfo.in_color_space = JCS_RGB;

    // Set up JPEG compression
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, TRUE);

    // Start compression
    jpeg_start_compress(&cinfo, TRUE);

    // Convert the QR code to RGB and write to the JPG file
    unsigned char *row = (unsigned char *)malloc(qrcode->width * module_size * 3);
    int x, y, i, j;
    for (y = 0; y < qrcode->width; y++) {
        for (i = 0; i < module_size; i++) { // Repeat for each module row
            for (x = 0; x < qrcode->width; x++) {
                int color = qrcode->data[y * qrcode->width + x] & 1 ? 0 : 255;  // Black or white
                for (j = 0; j < module_size; j++) { // Repeat for each module column
                    row[(x * module_size + j) * 3 + 0] = color;  // Red
                    row[(x * module_size + j) * 3 + 1] = color;  // Green
                    row[(x * module_size + j) * 3 + 2] = color;  // Blue
                }
            }
            jpeg_write_scanlines(&cinfo, &row, 1);
        }
    }

    // Finish compression
    jpeg_finish_compress(&cinfo);
    fclose(outfile);

    // Clean up
    free(row);
    QRcode_free(qrcode);
    jpeg_destroy_compress(&cinfo);

    printf("QR code saved to %s\n", filename);
}
