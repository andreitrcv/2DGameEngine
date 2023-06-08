#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>



Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 800, 640};


Manager manager;

AssetManager* Game::assets = new AssetManager(&manager);

//auto& player(manager.addEntity());

auto& label(manager.addEntity());
auto& tank(manager.addEntity());


enum groupLabels : std::size_t { // max : 32 Groups
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupVehicles
};


bool Game::isRunning = false;




Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem Initialized!..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	if(TTF_Init() == -1){
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("projectile", "assets/proj.png");
	assets->AddTexture("tank", "assets/tank.png");

	assets->addFont("arial", "assets/Arial Unicode.ttf", 16);

	map = new Map("terrain", 3, 32);
	map->LoadMap("assets/map.map", 25, 20);

/*
	player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
*/

	auto& player = Game::assets->CreatePlayer();


	SDL_Color white = {255, 255, 255, 255};
	label.addComponent<UILabel>(10, 10, "Test String", "arial", white);

	//assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");
	tank.addComponent<TransformComponent>(1100.0f, 580.0f, 128, 128, 1);
	tank.addComponent<SpriteComponent>("tank");
	tank.addComponent<ColliderComponent>("tank");
	tank.addComponent<TankController>();
	tank.addGroup(groupVehicles);

}


auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& vehicles(manager.getGroup(Game::groupVehicles));

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {


	SDL_Rect tankCol = tank.getComponent<ColliderComponent>().collider;
	Vector2D tankPos = tank.getComponent<TransformComponent>().position;

	std::stringstream ss;
	ss << "TANK position: " << tankPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");


	manager.refresh();
	manager.update(); // update all entities, so all components

	for (auto& c : colliders){
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if(Collision::AABB(cCol, tankCol)){
			tank.getComponent<TransformComponent>().position = tankPos;
		}
	}

	for(auto& pl : players){
		for(auto& p: projectiles){
			if(Collision::AABB(pl->getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
			{
				p->destroy();
			}
		}
	}

	camera.x = tank.getComponent<TransformComponent>().position.x - 400;
	camera.y = tank.getComponent<TransformComponent>().position.y - 320;

	if(camera.x < 0)
		camera.x = 0;
	
	if(camera.y < 0)
		camera.y = 0;
	
	if(camera.x > camera.w)
		camera.x = camera.w;
			
	if(camera.y > camera.h)
		camera.y = camera.h;
	



}



void Game::render() {
	SDL_RenderClear(renderer);

	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& p : players) {
		p->draw();
	}

	for (auto& c : colliders){
		c->draw();
	}

	for (auto& p : projectiles){
		p->draw();
	}

	for (auto& v : vehicles){
		v->draw();
	}


	label.draw();

	SDL_RenderPresent(renderer);

}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;

}

