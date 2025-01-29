#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <map>

namespace
{
    /// @brief Represents the ready state of the server.
    const char READY{ 'R' };

    /// @brief Represents the state where no light is detected.
    const char NO_LIGHT{ 'N' };

    /// @brief Represents the state where the button is pressed.
    const char BUTTON_PUSHED{ 'B' };

    /// @brief File path for the message file used in the program.
    const std::string MESSAGE_FILENAME{ "./message/message.txt" };

    /// @brief Morse code mapping for characters.
    const std::map<char, std::string> MORSE_CODE{
        {'a', ".-"},    {'b', "-..."}, {'c', "-.-."}, {'d', "-.."},  {'e', "."},
        {'f', "..-."},  {'g', "--."},  {'h', "...."}, {'i', ".."},   {'j', ".---"},
        {'k', "-.-"},   {'l', ".-.."}, {'m', "--"},   {'n', "-."},   {'o', "---"},
        {'p', ".--."},  {'q', "--.-"}, {'r', ".-."},  {'s', "..."},  {'t', "-"},
        {'u', "..-"},   {'v', "...-"}, {'w', ".--"},  {'x', "-..-"}, {'y', "-.--"},
        {'z', "--.."},  {'1', ".----"},{'2', "..---"},{'3', "...--"},{'4', "....-"},
        {'5', "....."}, {'6', "-...."},{'7', "--..."},{'8', "---.."},{'9', "----."},
        {'0', "-----"}, {' ', " "}  // Space between words.
    };
}

#endif // CONSTANTS_H
