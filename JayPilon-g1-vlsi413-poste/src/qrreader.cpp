#include "qrreader.h"      // Includes header for QR code detection and decoding
#include <zbar.h>          // Includes ZBar library for QR code scanning and decoding



// Function to detect and decode a QR code from an image
bool QR::DetectAndDecodeQRCode(const cv::Mat &image, std::string &decodedText, std::vector<cv::Point> &boundingBox) {
    cv::Mat gray;                                                   // Create a matrix to store the grayscale image
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);                  // Convert the input image to grayscale (required by ZBar)

    zbar::ImageScanner scanner;                                     // Create an instance of ZBar's ImageScanner
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);  // Configure the scanner to detect QR codes

    zbar::Image zbarImage(gray.cols, gray.rows, "Y800", gray.data, gray.cols * gray.rows); // Wrap the grayscale image in a ZBar-compatible format

    if (scanner.scan(zbarImage) > 0) {                                // Scan the image for QR codes (returns > 0 if detected)
        for (auto symbol = zbarImage.symbol_begin();                  // Iterate through all detected QR codes
             symbol != zbarImage.symbol_end(); ++symbol) {
            decodedText = symbol->get_data();                         // Extract the decoded text from the QR code
            boundingBox.clear();                                      // Clear the bounding box vector to store new points
            for (auto i = 0; i < symbol->get_location_size(); ++i) {  // Iterate through the QR code's corner points
                boundingBox.emplace_back(cv::Point(                   // Add each corner point to the bounding box
                    symbol->get_location_x(i), symbol->get_location_y(i)));
            }
            return true;                                            // Return true if at least one QR code is detected
        }
    }
    return false;                                                   // Return false if no QR code is detected
}

// Function to draw a bounding box around the detected QR code on the image
void QR::DrawBoundingBox(cv::Mat &image, const std::vector<cv::Point> &boundingBox) {
    if (boundingBox.size() == 4) {                                  // Ensure the bounding box has exactly 4 points
        cv::polylines(image, boundingBox, true,                     // Draw a closed polygon (bounding box)
                      cv::Scalar(0, 0, 255), 2);                    // Use red color and thickness of 2
    } else {                                                        // If the bounding box does not have 4 points
        std::cerr << "Error: Bounding box does not contain 4 points." << std::endl;  // Print an error message
    }
}

///////////////////////////////////////// LIVRABLE 6 /////////////////////////////////////////

// Function to filter and process the QR code data
std::string QR::FilterQRCodeData(const std::string &data) {
    std::string filtered;
    for (char c : data) {
        if (std::isalnum(c) || std::isspace(c)) {  // Keep only letters, digits, and spaces
            if (std::isupper(c)) {                // Convert uppercase letters to lowercase
                filtered += std::tolower(c);
            } else {
                filtered += c;                    // Add the character as-is
            }
        }
    }
    std::cout<< filtered<< std::endl;             // to check if the filtering is functionnal
    return filtered;                              // Return the filtered string
}


