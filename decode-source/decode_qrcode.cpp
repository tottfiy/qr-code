#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

int main() {
    // Corrected code
cv::Mat qrImage = cv::imread("qr.jpeg");
if (qrImage.empty()) {
    std::cerr << "Error: Could not load the image!" << std::endl;
    return -1;
}

// Create a QR code detector
cv::QRCodeDetector qrDecoder;

// Decode the QR code directly and capture the decoded text
cv::Mat bbox, rectifiedImage;
std::string decodedText = qrDecoder.detectAndDecode(qrImage, bbox, rectifiedImage);

if (decodedText.empty()) {
    std::cout << "No QR code detected or failed to decode." << std::endl;
} else {
    // Print the decoded string
    std::cout << "Decoded string: " << decodedText << std::endl;
}

// Optionally, display the image with the detected QR code
if (!bbox.empty()) {
    for (int i = 0; i < bbox.rows; i++) {
        cv::line(qrImage, bbox.at<cv::Point2f>(i), bbox.at<cv::Point2f>((i + 1) % bbox.rows), cv::Scalar(0, 255, 0), 2);
    }
    cv::imshow("QR Code", qrImage);
    cv::waitKey(0);
}

return 0;

}
