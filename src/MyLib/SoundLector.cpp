#include "SoundLector.h"
#include <iostream>


SoundLector* SoundLector::_instance = nullptr;

void SoundLector::Initialize()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
}

void SoundLector::LoadLightMusic(const char* name, const char* filename)
{
	Mix_Chunk* chunk = Mix_LoadWAV(filename);

	if (!chunk) {
		std::cout<<("Erreur chargement son '%s' : %s", filename, Mix_GetError());
		return;
	}
	_lightSounds.emplace(name, chunk);
}


void SoundLector::PlayLightMusic(const char* name, int playCount)
{

	Mix_PlayChannel(-1, _lightSounds[name], playCount);

}


void SoundLector::LoadLongMusic(const char* name, const char* filename)
{
	Mix_Music* music = Mix_LoadMUS(filename);

	if (!music) {
		std::cout << ("Erreur chargement son '%s' : %s", filename, Mix_GetError());
		return;
	}
	_longSounds.emplace(name, music);
}


void SoundLector::PlayLongMusic(const char* name, int playCount)
{
	
	Mix_PlayMusic(_longSounds[name], playCount);
	
}

void SoundLector::SetChunkVolume(const char* name, int volume)
{
	Mix_VolumeChunk(_lightSounds[name], volume);

}

void SoundLector::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}


void SoundLector::Clean()
{
	for (const auto& [name, chunk] : _lightSounds)
	{
		Mix_FreeChunk(chunk);
		_lightSounds.clear();
	}

	for (const auto& [name, music] : _longSounds)
	{
	
 		Mix_FreeMusic(music);	
		_longSounds.clear();
	}

	Mix_CloseAudio();
}


