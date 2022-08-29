#include <vector>
#include <random>
#include <string>
#include <cmath>
#include <Windows.h>
#include "interface.h"
#include "audio.h"

	enum Direction {
		LEFT = 0, RIGHT, UP, DOWN
	};

	struct Fish {
		SDL_Rect rect;
		int centerLine;	// Centerline that fish oscillates (swims) around
		Direction dir;
		bool isCaught;
		std::string imagePath;
	};

class Game
{
public:
	Game();
	~Game();

	// Setup function
	void setup();
	Fish generateFish();

	// Draw functions
	void displayPoints();
	void displayBackground();
	void displayFish();

	// Event handlers
	void handleEvents();
	void handleKeyHold();
	void handleKeyPress();
	void onCollision();
	void gameOverScreen();

	// Starts the game
	void run();

	// Generate random number between x and y
	int getRandNum(const int& x, const int& y);

	// Game variables
	bool gameRunning;
	int points;
	int numFish;	// Number of fish in ocean
	int sharkCount;	// Keep track of how many sharks currently in ocean
	Direction hookDir;	// Determines the direction hook is currently going

private:
	Interface window;

	SDL_Event e;
	
	Audio audio;

	// Points rect
	SDL_Rect pointsTxt = { 50, 50, 0, 0 };

	// Image rects
	SDL_Rect ocean = { 0, 500, window.WINDOW_WIDTH, 500 };
	SDL_Rect sky = { 0, 0, window.WINDOW_WIDTH, window.WINDOW_HEIGHT / 2 };
	SDL_Rect boat = { window.WINDOW_WIDTH / 4, (int)(window.WINDOW_HEIGHT / 3.5), 500, 250 };
	SDL_Rect fisherman = { window.WINDOW_WIDTH / 2 - 150, (int)(window.WINDOW_HEIGHT / 3.25), 150, 200 };
	SDL_Rect hook = { window.WINDOW_WIDTH / 2 - 35, window.WINDOW_HEIGHT / 2, 35, 50 };

	SDL_Color white = { 255, 255, 255 };
	SDL_Color blue = { 0, 94, 184 };
	SDL_Color skyBlue = { 0, 181, 226 };	

	std::vector<Fish> fish;

};

