#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

int main() {
    // Load the QR code image
    cv::Mat image = cv::imread("qrcode.jpg");

    if (image.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return -1;
    }

    // Create a QRCodeDetector object
    cv::QRCodeDetector qrDecoder;

    // Variables to hold the decoded data and points
    std::string decodedText;
    std::vector<cv::Point> points;

    // Decode the QR code in the image
    bool found = qrDecoder.detectAndDecode(image, decodedText, points);

    if (found) {
        // If QR code is detected, print the decoded text
        std::cout << "QR Code detected: " << decodedText << std::endl;

        // Optionally: Draw the polygon around the detected QR code
        cv::polylines(image, points, true, cv::Scalar(0, 255, 0), 2);

        // Display the result
        cv::imshow("QR Code Detection", image);
        cv::waitKey(0);
    } else {
        std::cout << "QR Code not detected!" << std::endl;
    }

    return 0;
}

// g++ -std=c++11 -o decode_qrcode decode_qrcode.cpp -ID:/OpenCV/opencv/build/include -LD:/OpenCV/opencv/build/x64/vc16/lib -lopencv_world490
