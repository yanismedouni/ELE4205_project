#ifndef GPIO_H
#define GPIO_H
#include <string>
#include <iostream>
#include <fstream>
#include "constants.h"
#include "button.h"

namespace GPIO {
    /// @brief Checks if sufficient light is detected.
    ///         - `true` if light is detected.
    ///         - `false` if light is not detected.
    bool IsLightDetected();

    /// @brief Determines the current state of the server based on sensor inputs.
    /// @param Button object which contains the state of the button.
    /// @return A character representing the server's state:
    ///         - `'B'`: Button is pressed.
    ///         - `'R'`: Light is detected and server is ready.
    ///         - `'N'`: No light detected.
    char GetServerState(Button& button);
}
#endif // GPIO_H