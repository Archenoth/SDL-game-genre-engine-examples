#include <stdio.h>
#include <SDL2/SDL.h>

// How much time do we want between frames (in milliseconds)?
#define FRAME_INTERVAL 20

// How fast do we want to move around the screen with the arrow keys?
// (In pixels per tick)
#define MOVEMENT_SPEED 3

/**
 * The player structure containing:
 *
 * SDL_Surface* surface: A pointer to an SDL_Surface containing the
 * player sprite
 *
 * int x: The player's X coordinate
 *
 * int y: The player's Y coordinate
 *
 * int previousX: The previous X coordinate of the player. Not
 * initialized until the first tick
 *
 * int previousY: The previous Y coordinate of the player. Not
 * initialized until the fisrt tick
 */
typedef struct player {
  SDL_Surface* surface;
  int x;
  int y;
  int previousX;
  int previousY;
} Player;


/**
 * Grabs user input from the keyboard, and updates the player location
 * based on it... (Or lack thereof).
 *
 * If "Q" is hit by the user, this function exits the program.
 *
 * @param <Player*> player: A pointer to a player struct to update
 * based on the keyboard input.
 */
void handleInput(Player* player){
  // Get new events, then grab a pointer to the state of the keyboard
  SDL_PumpEvents();
  const Uint8* keyState = SDL_GetKeyboardState(NULL);

  // If the user hits "Q", exit the program
  if(keyState[SDL_SCANCODE_Q] != 0){
    SDL_Quit();
    exit(0);
  }

  // Before we start changing the player coordinates, remember the
  // previous values.
  player->previousX = player->x;
  player->previousY = player->y;

  // Player pressing LEFT on the keybord, move left, to a minimum
  // coordinate of 5.
  if(keyState[SDL_SCANCODE_LEFT] && player->x > 5){
    player->x -= MOVEMENT_SPEED;
  }

  // Player pressing RIGHT on the keyboard, move right to a maximum
  // coordinate of 770.
  if(keyState[SDL_SCANCODE_RIGHT] && player->x < 770){
    player->x += MOVEMENT_SPEED;
  }

  // Player pressing UP on the keybord, move up to a minimum Y value
  // of 0.
  if(keyState[SDL_SCANCODE_UP] && player->y > 5){
    player->y -= MOVEMENT_SPEED;
  }

  // Player pressing DOWN on the keybord, move down to a maximum Y
  // value of 550.
  if(keyState[SDL_SCANCODE_DOWN] && player->y < 550){
    player->y += MOVEMENT_SPEED;
  }
}


/**
 * Renders the passed in player to the passed-in window.
 *
 * @param <SDL_Window*> window: A pointer to the window to render the
 * player to.
 * @param <Player*> player: A pointer to the player to render.
 */
void render(SDL_Window* window, Player* player){
  SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

  // Delay so that the engine isn't always at 100% CPU and slows down
  // events enough to make things playable. This isn't best practice,
  // but it is good enough for the purpose of this demonstration
  SDL_Delay(FRAME_INTERVAL);

  SDL_Rect destination = {player->x, player->y};
  SDL_Rect previous = {player->previousX, player->previousY};

  SDL_BlitSurface(windowSurface, NULL, windowSurface, &previous);
  SDL_BlitSurface(player->surface, NULL, windowSurface, &destination);

  SDL_UpdateWindowSurface(window);
}


/**
 * The main game loop, initializes a Player, then does three things
 * over and over again:
 *
 * 1) Grabs player input
 * 2) Updates the state of the world
 * 3) Renders the world
 *
 * @param <SDL_Window*> window: A pointer to a window to render the
 * output to.
 */
void gameLoop(SDL_Window* window){
  // Initiates the player at 10,10 with no velocity either direction
  Player player = {SDL_LoadBMP("StickGuy.bmp"), 10, 10, 0, 0};

  while(1){
    // Grabs input and updates the state of the world
    handleInput(&player);

    // Displays this new state
    render(window, &player);
  }
}


/**
 * The program entrypoint.
 */
int main(int argc, char* argv[]){
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    printf("\nSDL failed to initialize: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow(
    "Sidescroller engine",
    SDL_WINDOWPOS_UNDEFINED, // Undefined starting X window position
    SDL_WINDOWPOS_UNDEFINED, // Undefined starting Y window position
    800, 600, // The window has a resolution of 800x60
    0 // No special window flags
  );

  gameLoop(window);

  // Shouldn't get here, but in case it does, may as well do some
  // housekeeping.
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 1;
}
