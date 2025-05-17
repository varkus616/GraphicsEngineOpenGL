//#pragma once
//#include "ResourceManager.hpp"
//#include <unordered_map>
//#include <string>
//#include <iostream>
//
//struct Texture {
//    std::string name;
//    Texture() {}
//    explicit Texture(const std::string& n) : name(n) {
//        std::cout << "Texture [" << name << "] loaded\n";
//    }
//    void use() const {
//        std::cout << "Using texture: " << name << "\n";
//    }
//};
//
//struct Sound {
//    std::string name;
//    Sound() {}
//    explicit Sound(const std::string& n) : name(n) {
//        std::cout << "Sound [" << name << "] loaded\n";
//    }
//    void play() const {
//        std::cout << "Playing sound: " << name << "\n";
//    }
//};
//
//// ResourceSystem zarz¹dza wszystkimi typami zasobów
//class ResourceSystem {
//public:
//    typedef ResourceManager<Texture>::Handle TextureHandle;
//    typedef ResourceManager<Sound>::Handle SoundHandle;
//
//    ResourceSystem();
//
//    // Metody ³adowania zasobów
//    TextureHandle loadTexture(const std::string& name);
//    SoundHandle loadSound(const std::string& name);
//
//    // Metody uzyskiwania zasobów
//    Texture* getTexture(TextureHandle handle);
//    Sound* getSound(SoundHandle handle);
//    Texture* getTextureByName(const std::string& name);
//    Sound* getSoundByName(const std::string& name);
//
//    // Usuwanie zasobów
//    void destroyTexture(TextureHandle handle);
//    void destroySound(SoundHandle handle);
//
//    // Sprawdzenie pojemnoœci
//    size_t getTextureCapacity() const;
//    size_t getSoundCapacity() const;
//
//private:
//    ResourceManager<Texture> textureManager_;
//    ResourceManager<Sound> soundManager_;
//};
