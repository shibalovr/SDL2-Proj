#ifndef SOUND_H
#define SOUND_H
#include <SDL_mixer.h>
#include <SDL.h>
#include <string>
#include <stdio.h>
#include <map>



class SoundManager {
    public: 
        static SoundManager* GetInstances();
        Mix_Music* LoadMusic(std::string path);
        bool LoadChunk(std::string id, std::string path);

        void PlayMusic(Mix_Music* musik);
        void PlayChunk(std::string id);


    private:
        static SoundManager* s_Instance;
        std::map<std::string, Mix_Chunk*> m_SoundList;

};

#endif