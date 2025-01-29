#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <constants.h>

/// @class Button
/// @brief Represents a physical button connected via GPIO, with functionality to track its state.
class Button {
public:
    /// @brief Constructs a Button object with the given GPIO file path.
    /// @param gpioPath The file path to the GPIO pin associated with the button.
    explicit Button(const std::string& gpioPath);

    /// @brief Updates the current state of the button.
    /// 
    /// Tracks the button's state based on whether it is pressed or released.
    void UpdateState();

    /// @brief Retrieves the current state of the button.
    /// @return The current button state:
    ///         - `0`: Not pressed
    ///         - `1`: Just pressed
    ///         - `2`: Held
    int ReturnState();

private:
    /// @brief The file path to the GPIO pin associated with the button.
    std::string gpioPath;

    /// @brief Checks if the button is currently pressed.
    /// @return `true` if the button is pressed, `false` otherwise.
    bool IsPressed();

    /// @brief Tracks the previous state of the button.
    /// 
    /// Used to detect transitions such as from "not pressed" to "just pressed."
    int state;
};

#endif // BUTTON_H
