
#ifndef QR_H
#define QR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <opencv2/opencv.hpp>
#include <zbar.h>
#include "../qr-source/qr.h"


// Function to decode QR image
int decoder(const char * filename);

#endif // QR_H
