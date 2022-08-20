#include <vector>
#include <random>
#include <string>
#include <cmath>
#include <Windows.h>
#include "interface.h"


class Game
{
public:
	Game();
	~Game();

	// Setup function
	void setup();

	// Draw functions
	void displayBackground();
	void displayFish();

	// Event handler
	void handleEvents();
	void onCollision();
	void removeFish();

	// Starts the game
	void run();

	// Generate random number between x and y
	int getRandNum(const int& x, const int& y);

	// Game variables
	bool gameRunning;
	int numFish;	// Number of fish in ocean

	enum Direction {
		LEFT = 0, RIGHT
	};

private:
	Interface window;

	SDL_Event e;
	
	SDL_Rect ocean = { 0, 500, window.WINDOW_WIDTH, 500 };
	SDL_Rect sky = { -1, 0, window.WINDOW_WIDTH, window.WINDOW_HEIGHT / 2 };
	SDL_Rect boat = { window.WINDOW_WIDTH / 4, (int)(window.WINDOW_HEIGHT / 3.5), 500, 250 };
	SDL_Rect hook = { window.WINDOW_WIDTH / 2 - 35, window.WINDOW_HEIGHT / 2, 35, 50 };

	SDL_Color blue = { 0, 94, 184 };
	SDL_Color skyBlue = { 0, 181, 226 };
	
	struct Fish {
		SDL_Rect rect;
		int centerLine;	// Centerline that fish oscillates (swims) around
		Direction dir;
		bool isCaught;
		std::string imagePath;
	};

	std::vector<Fish> fish;

};

