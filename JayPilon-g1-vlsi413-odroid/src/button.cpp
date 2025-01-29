#include "button.h"
#include <fstream>
#include <iostream>

Button::Button(const std::string& gpioPath) 
    : gpioPath(gpioPath), state(0) {} // Initialize the GPIO path and state

bool Button::IsPressed() {
    std::ifstream buttonStateFile(gpioPath);
    if (!buttonStateFile.is_open()) {
        std::cerr << "Error: Could not open GPIO file at " << gpioPath << std::endl;
        return false;
    }

    int value;
    buttonStateFile >> value;                  // Read the current state from the file
    buttonStateFile.close();
    return (value == 0);                      // Return true only on the down front
}

int Button::ReturnState() {
    return state;
}

void Button::UpdateState() {
    auto pressed = IsPressed();

    if (state == 0 && pressed) state = 1;
    else if (state==1 && pressed) state = 2;
    else if (!pressed) state = 0;        // Update the previous state based on the current value
}
