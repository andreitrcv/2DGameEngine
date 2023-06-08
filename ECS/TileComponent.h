#pragma once


#include "ECS.h"
#include "SDL2/SDL.h"
#include "../AssetManager.h"

class TileComponents : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponents() = default;

	~TileComponents(){
		SDL_DestroyTexture(texture);
	}

	TileComponents(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id) {
		texture = Game::assets->GetTexture(id);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
		}
	
	void update() override{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override{
		TextureManager::Draw(texture, srcRect, destRect, 0.0, SDL_FLIP_NONE);
	}


};
