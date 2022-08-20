#include "game.h"

Game::Game() {

}

Game::~Game() {
	SDL_Quit();
}

void Game::setup() {
	gameRunning = true;
	numFish = 6;	// Number of fish in ocean

	window.addImage("boat", &boat, "assets/boat.png");

	// Populate fish array
	Direction d;
	SDL_Rect rect = { 0, 0, 75, 75 };
	for (int i = 0; i < numFish; i++) { // Generate fishes
		if (getRandNum(1, 2) == 1) {	// Determine fish starting direction and location
			d = RIGHT;
		}
		else {
			d = LEFT;
		}
		
		rect.x = getRandNum(0, window.WINDOW_WIDTH);
		rect.y = getRandNum(ocean.y + 200, ocean.y + ocean.h - 50);

		std::string num = std::to_string(getRandNum(1, 5));	// Generate filepath of random fish image
		std::string path = "assets/fish" + num + ".png";

		Fish f = { rect, rect.y, d, false, path };

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
	window.render(NULL, &hook, "assets/hook.png");
}

void Game::displayFish() {
	for (Fish& x : fish) {
		if (x.rect.x > 0 && x.dir == LEFT && !x.isCaught) {
			x.rect.x -= 7;
			x.rect.y = 20 * std::sin(0.01 * x.rect.x) + x.centerLine;
			window.renderFlip(NULL, &x.rect, x.imagePath, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}
		else {
			x.dir = RIGHT;
		}

		if (x.rect.x < window.WINDOW_WIDTH - x.rect.w && x.dir == RIGHT && !x.isCaught) {
			x.rect.x += 7;
			x.rect.y = 20 * std::sin(0.01 * x.rect.x) + x.centerLine;
			window.render(NULL, &x.rect, x.imagePath);
		}
		else {
			x.dir = LEFT;
		}

		if (x.isCaught) {
			x.rect.x = hook.x - 50;
			x.rect.y = hook.y + 10;
			window.render(NULL, &x.rect, x.imagePath);
		}

		if (x.rect.y == window.WINDOW_HEIGHT / 2 + 20) {	// If fish location = hook's starting 
			for (int i = 0; i < numFish; i++) {
				if (fish[i].isCaught) {
					fish[i].isCaught = false;
					fish.erase(fish.begin() + i);
					Fish f;
					fish.insert(fish.begin() + i, f);
				}
			}
		}
	}
}

void Game::handleEvents() {

	SDL_PollEvent(&e);
	char keyDown = e.key.keysym.scancode;

	onCollision();

	// Handle input events
	switch (e.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	case SDL_KEYDOWN:
		if (keyDown == SDL_SCANCODE_SPACE) {
			hook.y += 10;
		}
		break;
	default:
		if (hook.y > ocean.y + 50 && keyDown == SDL_SCANCODE_SPACE) {
			hook.y -= 5;
		}
		break;
	}
}

void Game::onCollision() {	// Check if hook collides with any fish
	for (Fish& x : fish) {	
		if ((std::abs(x.rect.x - hook.x) <= hook.w) && std::abs(x.rect.y - hook.y) <= hook.h) {
			x.isCaught = true;
		}
	}
}

void Game::removeFish() {

}

void Game::run() {
	while (gameRunning) {

		window.clear();

		handleEvents();			// Multiple event checks to reduce input delays

		displayBackground();

		handleEvents();

		displayFish();

		handleEvents();

		window.update();

	}
}
