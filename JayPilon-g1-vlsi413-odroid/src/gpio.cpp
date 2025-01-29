#include "gpio.h"

// Function to read the light sensor
bool GPIO::IsLightDetected() {
    std::ifstream lightSensor("/sys/class/saradc/ch0");
    int value;
    lightSensor >> value;
    lightSensor.close();
    return value < 1000;  // Threshold can be adjusted
}

char GPIO::GetServerState(Button& button) {
    button.UpdateState();
    if (!GPIO::IsLightDetected()) return NO_LIGHT;
    else if (button.ReturnState() == 1) return BUTTON_PUSHED;
    else return READY;
}