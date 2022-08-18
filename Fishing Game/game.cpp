#include "game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::setup() {
	gameRunning = true;
	numFish = 6;	// Number of fish in ocean

	window.addImage("boat", &boat, "assets/boat.png");

	// Populate fish array
	Direction d;
	SDL_Rect rect = { 0, 0, 50, 50 };
	for (int i = 0; i < numFish; i++) { // Generate fishes
		if (getRandNum(1, 2) == 1) {	// Determine fish starting direction and location
			d = RIGHT;
			rect.x = 0;

		}
		else {
			d = LEFT;
			rect.x = ocean.w - 50;
		}
			rect.y = getRandNum(ocean.y + 50, ocean.y + ocean.h - 50);

			std::string num = std::to_string(getRandNum(1, 5));	// Generate filepath of random fish image
			std::string path = "assets/fish" + num + ".png";

			Fish f = { rect, d, path };

			fish.push_back(f);
	}	
}

int Game::getRandNum(const int& x, const int& y) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<> dist(x, y);

	return dist(rng);
}

void Game::displayBackground() {
	window.displayRect(&sky, skyBlue);
	window.displayRect(&ocean, blue);
	window.render(NULL, &boat, "assets/boat.png");
}

void Game::displayFish() {
	for (Fish& x : fish) {
		if (x.rect.x > 0 && x.dir == LEFT) {
			x.rect.x -= 10;
			window.renderFlip(NULL, &x.rect, x.imagePath, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}
		else {
			x.dir = RIGHT;
		}

		if (x.rect.x < window.WINDOW_WIDTH && x.dir == RIGHT) {
			x.rect.x += 10;
			window.render(NULL, &x.rect, x.imagePath);
		}
		else {
			x.dir = LEFT;
		}
	}
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
		displayFish();

		window.update();

		handleEvents();
	}
}
