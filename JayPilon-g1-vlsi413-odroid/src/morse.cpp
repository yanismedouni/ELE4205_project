#include "morse.h"
#include "constants.h"


void Morse::ParseSongFile(const std::string& filename)
{
	std::ifstream file(filename.c_str(), std::ifstream::in);
	if ( file.fail() ) 
	{
        std::cout << "Failed to open " + filename << std::endl;
		exit(-1);
	}	

	auto frequency = 0;
	auto length = 0;
	auto delay = 0;
	while(file >> frequency >> length >> delay)
	{
		_noteFrequency.push_back( static_cast<uint32_t>( frequency ) );
		_noteLength.push_back(  static_cast<uint32_t>( length ) );
		_noteDelay.push_back(  static_cast<uint32_t>( delay ) );
	}
}

void Morse::PlaySong() const
{
	const auto numberOfNotes =_noteFrequency.size();
	for(int i(0); i<numberOfNotes; ++i)
	{
		std::cout << "Freq: " << _noteFrequency[i] << " length: " << _noteLength[i] << std::endl;
		PlayNote(_noteFrequency[i], _noteLength[i]);

		std::cout << "Delay: " << _noteDelay[i] << std::endl;
		usleep((_noteDelay[i]) * 1000);
	}
}

void Morse::PlayNote(uint32_t frequency, uint32_t length) const {
    const std::string filePath = "/sys/devices/pwm-ctrl.42/";
    std::ofstream fileenable(filePath + "enable0");
    if (!fileenable.is_open()) {
        throw std::runtime_error("Failed to open enable0 file");
    }
    std::ofstream filefreq(filePath + "freq0");
    if (!filefreq.is_open()) {
        throw std::runtime_error("Failed to open enable0 file");
    }
    std::ofstream fileduty(filePath + "duty0");
    if (!fileduty.is_open()) {
        throw std::runtime_error("Failed to open enable0 file");
    }
    fileduty << 512;
    fileduty.close();
    if(frequency != 0){
        fileenable << 1;
        fileenable.close();
        filefreq << frequency;
        filefreq.close();
        try {
            std::this_thread::sleep_for(std::chrono::milliseconds(length));
        } catch (const std::exception& e) {
            std::cerr << "Sleep interrupted: " << e.what() << std::endl;
        }
    }
    fileenable.open(filePath + "enable0");
    fileenable << 0;
    filefreq.close();
}


void WriteMorseToFile(const std::string& input) {
    // Durations in milliseconds
    const int dit = 60;
    const int dah = 3 * dit;
    const int interElementGap = 2 * dit;
    const int charGap = 5 * dit;
    const int wordGap = 8 * dit;
    const int frequency = 660;

    std::ofstream outFile(MESSAGE_FILENAME); // Open the file for writing
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << MESSAGE_FILENAME << std::endl;
        return;
    }

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (MORSE_CODE.find(c) != MORSE_CODE.end()) {
            const std::string& code = MORSE_CODE.at(c); // Get Morse code for character
            for (size_t j = 0; j < code.size(); ++j) {
                if ((j == code.size() - 1) && input[i + 1] == ' '){
                    if (code[j] == '.') { // Dit
                        outFile << frequency << " " << dit << " " << wordGap << "\n";
                    } else if (code[j] == '-') { // Dah
                        outFile << frequency << " " << dah << " " << wordGap << "\n";
                    }
                }
                else if ((j == code.size() - 1)){
                    if (code[j] == '.') { // Dit
                        outFile << frequency << " " << dit << " " << charGap << "\n";
                    } else if (code[j] == '-') { // Dah
                        outFile << frequency << " " << dah << " " << charGap << "\n";
                    }
                }
                else {
                    if (code[j] == '.') { // Dit
                        outFile << frequency << " " << dit << " " << interElementGap << "\n";
                    } else if (code[j] == '-') { // Dah
                        outFile << frequency << " " << dah << " " << interElementGap << "\n";
                    }
                }
            }
        }
    }

    // Add buzzer activation at the end
    outFile << frequency << " " << 1000 << " " << 0 << "\n"; // 1-second buzzer at the end

    outFile.close(); // Close the file
    std::cout << "Morse code successfully written to " << MESSAGE_FILENAME << std::endl;
}