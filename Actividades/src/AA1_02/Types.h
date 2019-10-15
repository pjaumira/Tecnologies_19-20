#pragma once
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CLOCKS_PER_SEC ((clock_t) 1000)
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

struct Vec2 {
	int x = 0;
	int y = 0;
};

bool collision(Vec2 origin, SDL_Rect target) {
	return (origin.x > target.x && origin.x < target.x + target.w && origin.y > target.y && origin.y < target.y + target.h);
}

bool collisionR(SDL_Rect origin, SDL_Rect target) {
	return (origin.x > target.x && origin.x < target.x + target.w && origin.y > target.y && origin.y < target.y + target.h);
}
