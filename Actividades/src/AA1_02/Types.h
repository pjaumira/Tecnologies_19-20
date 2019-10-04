#pragma once
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

struct Vec2 {
	int x = 0;
	int y = 0;
};

bool collision(Vec2 origin, SDL_Rect target) {
	return (origin.x > target.x && origin.x < target.x + target.w && origin.y > target.y && origin.y < target.y + target.h);
}