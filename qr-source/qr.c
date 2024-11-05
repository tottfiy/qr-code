#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "qr.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



void printQr(const uint8_t qrcode[]) {
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
	fputs("\n", stdout);
    
}


void genQR(const char *text, const char *filename, int quality) {
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    
    // Generate the QR code
    bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode,
                                    qrcodegen_Ecc_LOW, qrcodegen_VERSION_MIN,
                                    qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
                                    
    if (ok) {
        int size = qrcodegen_getSize(qrcode);
        int width = size;
        int height = size;
        int channels = 3; // RGB
        
        // Allocate memory for image data
        uint8_t *data = (uint8_t *)malloc(width * height * channels);
        if (!data) {
            printf("Failed to allocate memory for image.\n");
            return;
        }

        // Populate the RGB buffer from the QR code matrix
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                int pixel = qrcodegen_getModule(qrcode, x, y) ? 0 : 255; // Black or white
                int place = ((y * width + x) * channels);
                data[place + 0] = pixel;  // Red
                data[place + 1] = pixel;  // Green
                data[place + 2] = pixel;  // Blue
            }
        }
            if (!stbi_write_jpg(filename, width, height, channels, data, quality)) {
            printf("Failed to write JPEG file.\n");
        }
        free(data);
        printf("Your QR code is in qr-code.jpg file.\n");
        }   else {
                printf("ERROR GENERATING QR");
        }


        
    }






