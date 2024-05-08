#include "Sound.h"

SoundManager* SoundManager::s_Instance = nullptr;

SoundManager* SoundManager::GetInstances() {
    if (s_Instance == nullptr) {
        s_Instance = new SoundManager();
    }
    return s_Instance;
}

Mix_Music* SoundManager::LoadMusic(std::string path) {
    Mix_Music* musik =  Mix_LoadMUS(path.c_str());
    return musik;
}

bool SoundManager::LoadChunk(std::string id, std::string path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (chunk == nullptr) {
        return false;
    }

    m_SoundList[id] = chunk;
    return true;
}

void SoundManager::PlayMusic(Mix_Music* musik) {
    if (musik == nullptr) return;    
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(musik, -1);
    } else if (Mix_PlayingMusic() == 1) {
        Mix_ResumeMusic();
    } 
}

void SoundManager::PlayChunk(std::string id) {
    if (m_SoundList.find(id) != m_SoundList.end()) {
        Mix_PlayChannel(-1, m_SoundList[id], 0);
    }
} 

