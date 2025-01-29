#ifndef QRREADER_H
#define QRREADER_H

#include <opencv2/opencv.hpp> // Pour le type cv::Mat

namespace QR {
    /// @brief Detects and decodes a QR code from an image.
    /// @param image The input image to process.
    /// @param decodedText The decoded QR code text, if any.
    /// @return true if a QR code is detected and decoded, false otherwise. 
    bool DetectAndDecodeQRCode(const cv::Mat &image, std::string &decodedText, std::vector<cv::Point> &boundingBox);

    /// @brief Draws a bounding box around the QR code in the image. 
    /// @param image The image to draw the box on.
    /// @param boundingBox The coordinates of the QR code.
    void DrawBoundingBox(cv::Mat &image, const std::vector<cv::Point> &boundingBox);

    /// @brief 
    /// @param data 
    /// @return 
    std::string FilterQRCodeData(const std::string &data);

}
#endif // QRREADER_H