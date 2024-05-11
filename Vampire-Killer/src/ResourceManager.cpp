#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
    InitAudioDevice();
    LoadSounds();
    LoadMusic();
}
ResourceManager::~ResourceManager()
{
    Release();
}

void ResourceManager::LoadSounds() 
{
    soundList[(int)SoundResource::SOUND_ATTACK] = LoadSound("");
}
void ResourceManager::LoadMusic()
{
    musicList[(int)MusicResource::MUSIC_STAGE0] = LoadMusicStream("Assets/Music/Vampire Killer.ogg");
}
//Load a texture from a file and associate it with the key id
AppStatus ResourceManager::LoadTexture(Resource id, const std::string& file_path)
{
    //Load the texture
    Texture2D texture = ::LoadTexture(file_path.c_str());
    if (texture.id == 0)
    {
        //Error loading texture
        LOG("Failed to load texture ", file_path);
        return AppStatus::ERROR;
    }
    
    //Insert the loaded texture into the map with the specified key
    textures[id] = texture;
    return AppStatus::OK;
}

//Release the texture associated with the key id
void ResourceManager::ReleaseTexture(Resource id)
{
    //Find the texture associated with the key
    auto it = textures.find(id);

    //If found, unload the texture and remove it from the map
    if (it != textures.end())
    {
        UnloadTexture(it->second);
        textures.erase(it);
    }
}

//Get a texture by key
const Texture2D* ResourceManager::GetTexture(Resource id) const
{
    //Find the texture associated with the key and return it
    auto it = textures.find(id);
    if (it != textures.end())   return &(it->second);

    //Return nullptr if key is not found
    return nullptr;
}

Sound ResourceManager::GetSound(SoundResource id) const
{
    return (soundList[(int)id]);
}

Music ResourceManager::GetMusic(MusicResource id) const
{
    return (musicList[(int)id]);
}

void ResourceManager::Release()
{
    for (auto& pair : textures)
    {
        UnloadTexture(pair.second);
    }
    for (int i = 0; i < (int)SoundResource::NUM_SOUNDS; i++)
    {
        UnloadSound(soundList[i]);
    }
    for (int i = 0; i < (int)MusicResource::NUM_MUSIC; i++)
    {
        UnloadMusicStream(musicList[i]);
    }
    textures.clear();
    CloseAudioDevice();
}