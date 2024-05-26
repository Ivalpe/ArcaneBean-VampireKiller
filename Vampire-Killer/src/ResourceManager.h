#pragma once

#include "raylib.h"
#include "Globals.h"
#include <unordered_map>
#include <string>

enum class Resource {
    IMG_MSCREEN,
    IMG_MENU,
    IMG_PLAYER,
    IMG_TILES,
    IMG_ITEMS,
    IMG_WHIP,
    IMG_GAMEOVER,
    IMG_FIRE, 
    IMG_CANDLE,
    IMG_KNIGHT,
    IMG_BAR
};

enum class MusicResource {
    MUSIC_STAGE0,
    MUSIC_STAGE2,
    NUM_MUSIC
};

enum class SoundResource {
    SOUND_ATTACK,
    NUM_SOUNDS
};

class ResourceManager {
public:
    //Singleton instance retrieval
    static ResourceManager& Instance()
    {
        static ResourceManager instance; //Guaranteed to be initialized only once
        return instance;
    }

    //Load and unload texture
    AppStatus LoadTexture(Resource id, const std::string& file_path);
    void LoadSounds();
    void LoadMusic();
    void ReleaseTexture(Resource id);

    //Get texture by key
    const Texture2D* GetTexture(Resource id) const;
    Sound GetSound(SoundResource id) const;
    Music GetMusic(MusicResource id) const;


    //Release resources
    void Release();

    //Ensure Singleton cannot be copied or assigned
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    //Private constructor to prevent instantiation
    ResourceManager();
    //Destructor
    ~ResourceManager();

    //Dictionary to store loaded textures
    std::unordered_map<Resource, Texture2D> textures;

    Music musicList[(int)MusicResource::NUM_MUSIC];
    Sound soundList[(int)SoundResource::NUM_SOUNDS];
};