// #include <opencv2/opencv_modules.hpp>

#include "qr.hpp"

int decoder(const char * filename) {
    // Load the image using OpenCV
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);  // Read the image in color mode

    // Check if the image was loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    // Convert to grayscale (ZBar works better with grayscale images for barcode detection)
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Access the raw data from the image (grayscale)
    uchar* rawData = gray.data;

    // Set up the ZBar image
    zbar::Image zbarImage(image.cols, image.rows, "Y800", rawData, image.cols * image.rows);

    // Create a scanner object
    zbar::ImageScanner scanner;

    // Enable the scanner to recognize barcodes (QR, Code128, etc.)
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

    // Scan the image for barcodes
    int n = scanner.scan(zbarImage);

    // If barcodes are found, print them
    if (n > 0) {
        std::cout << "Barcode(s) found!" << std::endl;
        for (zbar::Image::SymbolIterator symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol) {
            std::cout << "Type: " << symbol->get_type_name() << std::endl;
            std::cout << "Data: " << symbol->get_data() << std::endl;
        }
    } else {
        std::cout << "No barcodes found." << std::endl;
    }

    return 0;
}
