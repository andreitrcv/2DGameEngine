#pragma once


#include "SDL2/SDL.h"



#include "SDL2/SDL_image.h"



#include <iostream>
#include <vector>

class ColliderComponent;
class AssetManager;

class Game{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; };
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static 	bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;
	
enum groupLabels : std::size_t { // max : 32 Groups
	groupMap,
	groupPlayers,
	groupColliders,
	groupProjectiles,
	groupVehicles
};

private:
	int cnt = 0;
	SDL_Window* window;
	


};

