#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <SDL2/SDL_mixer.h>

// Plays a sound effect
class Sound
{
public:
	Sound();
	~Sound(void);

	bool Load(std::string filename);	 // Load the sound
	void Play(int loops, int channel); // Play the sound, with loops, -1 is infinite, 0 is once

private:
	std::string filename; // The filepath to the sound file
	Mix_Chunk *sound;			// The music data
};

#endif
