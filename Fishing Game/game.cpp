#include "game.h"

Game::Game() {

}

Game::~Game() {
	SDL_Quit();
}

void Game::setup() {
	window.setFontSize(36);
	window.setFont("assets/font/raleway.ttf");

	gameRunning = true;
	numFish = 6;	// Number of fish in ocean
	hookDir = DOWN;

	window.addImage("boat", &boat, "assets/images/boat.png");

	// Populate fish array
	
	for (int i = 0; i < numFish; i++) { // Generate fishes
		
		Fish f = generateFish();
		fish.push_back(f);
	}	
}

Fish Game::generateFish() {

	Direction d;
	SDL_Rect rect = { 0, 0, 75, 75 };

	if (getRandNum(1, 2) == 1) {	// Determine fish starting direction and location
		d = RIGHT;
	}
	else {
		d = LEFT;
	}

	rect.x = getRandNum(0, window.WINDOW_WIDTH);
	rect.y = getRandNum(ocean.y + 200, ocean.y + ocean.h - 50);

	std::string num = std::to_string(getRandNum(1, 5));	// Generate filepath of random fish image
	std::string path = "assets/images/fish" + num + ".png";

	Fish f = { rect, rect.y, d, false, path };
	return f;
}

int Game::getRandNum(const int& x, const int& y) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<> dist(x, y);

	return dist(rng);
}

void Game::displayPoints() {
	window.displayText("Points: " + std::to_string(points), &pointsTxt, white);
}

void Game::displayBackground() {
	window.displayRect(&sky, skyBlue);
	window.displayRect(&ocean, blue);
	window.render(NULL, &boat, "assets/images/boat.png");
	window.render(NULL, &hook, "assets/images/hook.png");
	window.render(NULL, &fisherman, "assets/images/fisherman.png");
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

		if (x.rect.y == window.WINDOW_HEIGHT / 2 + 20) {	// If fish location = hook's starting, remove fish from hook and add points
			for (int i = 0; i < numFish; i++) {
				if (fish[i].isCaught) {
					fish[i].isCaught = false;
					fish.erase(fish.begin() + i);
					Fish f = generateFish();
					fish.insert(fish.begin() + i, f);
					points += 10;
					audio.playSound("assets/sfx/pointEarned.wav");
				}
			}
		}
	}
}

void Game::handleEvents() {

	// Check if hook collides with any fish
	onCollision();

	// Handle if a key is being held
	handleKeyHold();

	// Handle single key presses
	handleKeyPress();	
}

void Game::handleKeyHold() {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	// Hook inputs
	if (keyState[SDL_SCANCODE_SPACE] && hook.y < window.WINDOW_HEIGHT - 50 && hookDir!= UP) {
		hook.y += 10;
		hookDir = DOWN;
	}
	else if (hook.y > ocean.y + 50) {
		hook.y -= 10;
		hookDir = UP;
	}
	else {
		hookDir = DOWN;
	}
}

void Game::handleKeyPress() {
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	default:
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

void Game::run() {
	while (gameRunning) {

		window.clear();

		handleEvents();

		displayBackground();
		displayFish();
		displayPoints();

		window.update();

	}
}
