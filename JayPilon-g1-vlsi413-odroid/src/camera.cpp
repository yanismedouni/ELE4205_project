#include "camera.h"

// The CreateCamera function initializes and returns a VideoCapture object with specified resolution settings.
cv::VideoCapture Cam::CreateCamera(int width, int height) {
    cv::VideoCapture capture(0); // Opens the default camera.
    
    // Check if the camera was successfully opened.
    if (!capture.isOpened()) {
        std::cout << "Failed to connect to the camera." << std::endl;
        std::terminate();
    }
    
    // Set the desired resolution for the camera.
    capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);
    return capture;
}
