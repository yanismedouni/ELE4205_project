#ifndef MORSE_H
#define MORSE_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <thread>
#include <chrono>

/// @brief  Base class for a song parser
class Morse
{
public:
	/// @brief Default constructor
	Morse() = default;

	/// @brief Parse the song file which contains notes to play
	/// @param filename Name of the song file
	void ParseSongFile(const std::string& filename);

	/// @brief Play the song 
	void PlaySong() const;

protected:
	/// @brief Play a music note
	/// @param frequency Frequency of the note to play
	/// @param length Duration of the note to play in ms
	void PlayNote(uint32_t frequency, uint32_t length) const;

	/// @brief Frequency of the notes to play
	std::vector<uint32_t> _noteFrequency;

	/// @brief Length of the notes to play in ms
	std::vector<uint32_t> _noteLength;

	/// @brief Delay before next music note to play in ms
	std::vector<uint32_t> _noteDelay;
};
/// @brief 
/// @param input 
/// @param filename 
void WriteMorseToFile(const std::string& input);
#endif
