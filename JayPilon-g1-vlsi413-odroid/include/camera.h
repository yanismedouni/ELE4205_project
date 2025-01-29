#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include <chrono>
#include <tuple>

namespace Cam {
    /// @brief Initializes the camera with a specified resolution.
    /// 
    /// This function creates and configures a VideoCapture object with the specified
    /// width and height for capturing frames from the camera.
    /// 
    /// @param width The desired width of the camera resolution.
    /// @param height The desired height of the camera resolution.
    /// @return Returns the VideoCapture object configured to the specified resolution.
    ///         If the camera fails to open, returns an uninitialized VideoCapture object.
    cv::VideoCapture CreateCamera(int width, int height);
}
#endif // CAMERA_H
