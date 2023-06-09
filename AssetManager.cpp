#include "AssetManager.h"
#include "ECS/Components.h"



AssetManager::AssetManager(Manager* man) : manager(man) {

}
AssetManager::~AssetManager(){

}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id){
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    projectile.addComponent<SpriteComponent>(id, false);
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup(Game::groupProjectiles);
}

Entity& AssetManager::CreatePlayer(){
    auto& player(manager->addEntity());
	player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 4);
	player.addComponent<SpriteComponent>("player", true);
	//player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
    player.addComponent<HealthComponent>();
	player.addGroup(Game::groupPlayers);
    return player;
}


void AssetManager::AddTexture(std::string id, const char* path){
    textures.emplace(id, TextureManager::LoadTexture(path));
}
    
    
SDL_Texture* AssetManager::GetTexture(std::string id){
    return textures[id];
}


void AssetManager::addFont(std::string id, std::string path, int fontSize){
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}


TTF_Font* AssetManager::GetFont(std::string id){
    return fonts[id];
}
