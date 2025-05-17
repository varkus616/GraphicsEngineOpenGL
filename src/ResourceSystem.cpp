//#include "ResourceSystem.hpp"
//
//// Konstruktor
//ResourceSystem::ResourceSystem() {}
//
//// £adowanie tekstury z nazwy
//ResourceSystem::TextureHandle ResourceSystem::loadTexture(const std::string& name) {
//    return textureManager_.create(Texture(name), name);  // Dodanie nazwy do create
//}
//
//// £adowanie dŸwiêku z nazwy
//ResourceSystem::SoundHandle ResourceSystem::loadSound(const std::string& name) {
//    return soundManager_.create(Sound(name), name);  // Dodanie nazwy do create
//}
//
//// Uzyskiwanie tekstury po nazwie
//Texture* ResourceSystem::getTextureByName(const std::string& name) {
//    return textureManager_.getByName(name);
//}
//
//// Uzyskiwanie dŸwiêku po nazwie
//Sound* ResourceSystem::getSoundByName(const std::string& name) {
//    return soundManager_.getByName(name);
//}
//
//// Pozosta³e metody: destroy, capacity...
