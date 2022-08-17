#include <iostream>
#include <vector>
#include <random>
#include <Windows.h>
#include "interface.h"

enum Direction {
	LEFT = 0, RIGHT
};

int main(int argc, char* args[]) {

	Direction dir = RIGHT;

	Interface window;
	SDL_Rect ocean = { -1, 500, window.WINDOW_WIDTH + 1, 1000 };
	SDL_Rect sky = { -1, 0, window.WINDOW_WIDTH + 1, 1000 };
	SDL_Rect fish = { 10, 600, 50, 50 };
	SDL_Rect boat = { window.WINDOW_WIDTH / 3, window.WINDOW_HEIGHT / 3.5, 500, 250 };
	SDL_Color blue = { 0, 94, 184 };
	SDL_Color skyBlue = { 0, 181, 226};

	window.addImage("boat", &boat, "assets/boat.png");
	window.addImage("fish1", &fish, "assets/fish1.png");

	bool gameRunning = true;

	while (gameRunning) {

		window.clear();

		window.displayRect(&sky, skyBlue);
		window.displayRect(&ocean, blue);
		window.render(NULL, &boat, "assets/boat.png");

		SDL_Event e;
		SDL_PollEvent(&e);
	
		if (fish.x < window.WINDOW_WIDTH && dir == RIGHT) {
			fish.x += 5;
			window.render(NULL, &fish, "assets/fish1.png");
		}
		else
			dir = LEFT;
		
		if (fish.x > 0 && dir == LEFT) {
			fish.x -= 5;
			window.renderFlip(NULL, &fish, "assets/fish1.png", NULL, NULL, SDL_FLIP_HORIZONTAL);
		}
		else
			dir = RIGHT;

		window.update();
		
		// Handle events
		switch (e.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		default:
			break;
		}
	}

	
	return 0;
}