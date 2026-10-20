#pragma once
#include "SDL_mixer.h"
#include <vector>
#include <map>

class SoundLector
{
private:
	std::map<const char* , Mix_Chunk*> _lightSounds;
	std::map<const char*, Mix_Music*> _longSounds;

	static SoundLector* _instance;
public:

	static SoundLector* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new SoundLector();
		return _instance;
	}

	void Initialize();
	void LoadLightMusic(const char* name, const char* filename);
	void PlayLightMusic(const char* name, int playCount);
	void LoadLongMusic(const char* name, const char* filename);
	void PlayLongMusic(const char* name, int playCount);
	void SetChunkVolume(const char* name, int volume);
	void SetMusicVolume(int volume);
	void Clean();

	friend class GameManager;
	friend class Player;
};

