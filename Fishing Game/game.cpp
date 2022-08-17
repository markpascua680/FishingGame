#include "game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::setup() {
	gameRunning = true;

	//_window.addImage("boat", &boat, "assets/boat.png");
	window.addImage("fish1", &fish, "assets/fish1.png");
}

void Game::displayBackground() {
	window.displayRect(&sky, skyBlue);
	window.displayRect(&ocean, blue);
	window.render(NULL, &boat, "assets/boat.png");
}

void Game::handleEvents() {

	SDL_PollEvent(&e);

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

void Game::run() {
	while (gameRunning) {

		window.clear();

		displayBackground();

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

		handleEvents();
	}
}
