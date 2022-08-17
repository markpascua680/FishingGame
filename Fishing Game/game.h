#include <vector>
#include <random>
#include <Windows.h>
#include "interface.h"

class Game
{
public:
	Game();
	~Game();

	void setup();
	void displayBackground();
	void handleEvents();

	// Starts the game
	void run();

	bool gameRunning;

	enum Direction {
		LEFT = 0, RIGHT
	};
	Direction dir = RIGHT;

private:
	Interface window;

	SDL_Event e;
	
	SDL_Rect ocean = { 0, 500, window.WINDOW_WIDTH, 500 };
	SDL_Rect sky = { -1, 0, window.WINDOW_WIDTH, window.WINDOW_HEIGHT / 2 };
	SDL_Rect fish = { 10, 600, 50, 50 };
	SDL_Rect boat = { window.WINDOW_WIDTH / 3, (int)(window.WINDOW_HEIGHT / 3.5), 500, 250 };

	SDL_Color blue = { 0, 94, 184 };
	SDL_Color skyBlue = { 0, 181, 226 };
};

