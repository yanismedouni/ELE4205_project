#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector> 

namespace
{
    /// @brief Represents the "ready" state of the server.
    const char READY{ 'R' };

    /// @brief Represents the state where no light is detected.
    const char NO_LIGHT{ 'N' };

    /// @brief Represents the state where the button has been pushed.
    const char BUTTON_PUSHED{ 'B' };

    /// @brief List of supported resolutions for the camera.
    /// Each resolution is represented as a pair of integers: (width, height).
    const std::vector<std::pair<int, int>> RESOLUTIONS{
        {432, 240},
        {800, 600},
        {960, 720},
        {1280, 720}
    };
}

#endif // CONSTANTS_H
