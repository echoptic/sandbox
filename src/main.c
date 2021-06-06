#include "SDL2/SDL.h"
#include "particles.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define CELL_SIZE 20

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define NUM_COLS WINDOW_WIDTH / CELL_SIZE
#define NUM_ROWS WINDOW_HEIGHT / CELL_SIZE

typedef int Grid[NUM_COLS][NUM_ROWS];

Grid grid;

SDL_Event event;
SDL_Window *window;
SDL_Renderer *renderer;

void update(Grid grid);
// Render particles on screen
void render(Grid grid, int col, int row);

// Sets all elements to 0
void clear_grid(Grid grid);
void fill_grid(Grid grid);

void quit(void);

struct
{
    int x, y;
} mouse;

void update(Grid grid)
{
    for (int col = 0; col < NUM_COLS; col++)
        for (int row = 0; row < NUM_ROWS; row++)
            if (grid[col][row])
            {
                if (grid[col][row] == SAND)
                {
                    if (row < NUM_ROWS - 1 && grid[col][row + 1] == AIR)
                    {
                        grid[col][row] = 0;
                        grid[col][row + 1] = 1;
                    }
                }

                render(grid, col, row);
            }
}

void render(Grid grid, int col, int row)
{
    if (grid[col][row])
    {
        SDL_Rect cell = {
            .x = col * CELL_SIZE,
            .y = row * CELL_SIZE,
            .w = CELL_SIZE,
            .h = CELL_SIZE,
        };

        // Add colors for particle ids
        switch (grid[col][row])
        {
        case SAND:
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
            break;
        case STONE:
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
            break;
        }

        SDL_RenderFillRect(renderer, &cell);
    }
}

void clear_grid(Grid grid)
{
    for (int col = 0; col < NUM_COLS; col++)
        for (int row = 0; row < NUM_ROWS; row++)
            grid[col][row] = AIR;
}

void fill_grid(Grid grid)
{
    for (int col = 0; col < NUM_COLS; col++)
        for (int row = 0; row < NUM_ROWS; row++)
            grid[col][row] = STONE;
}

void quit()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

int main(int argc, char *argv[])
{
    Uint32 last_update = SDL_GetTicks();

    // Look keyboard events
    Uint8 selected_particle;
    selected_particle = SAND;

    bool running = true;
    bool clicked = false;
    bool paused = false;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "Sandbox",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    while (running)
    {
        // grid[NUM_COLS - 1][NUM_ROWS - 1] = 1;

        // Calculate delta time
        Uint32 current = SDL_GetTicks();
        float dT = (current - last_update) / 1000.0f;

        // FPS Counter
        Uint64 start = SDL_GetPerformanceCounter();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEMOTION)
                SDL_GetMouseState(&mouse.x, &mouse.y);

            // Keyboard events
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_c:
                    clear_grid(grid);
                    break;

                case SDLK_f:
                    fill_grid(grid);
                    break;

                case SDLK_SPACE:
                    paused = !paused;
                    break;

                // Select particles 0-9
                case SDLK_0:
                    selected_particle = AIR;
                    break;
                case SDLK_1:
                    selected_particle = SAND;
                    break;
                case SDLK_2:
                    selected_particle = STONE;
                    break;
                default:
                    break;
                }
            }
            // Mouse click events
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicked = true;
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicked = false;
        } // SDL_PollEvent

        if (clicked)
            if (!grid[mouse.x / CELL_SIZE][mouse.y / CELL_SIZE])
                grid[mouse.x / CELL_SIZE][mouse.y / CELL_SIZE] = selected_particle;

        // Rendering
        SDL_RenderClear(renderer);

        update(grid);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        // Possible pause implementation
        if (!paused)
        {
        }

        // FPS and dT Counter
        last_update = current;
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        printf("\rFPS: %f dT: %f", 1.0f / elapsed, dT);
    }

    quit();
    return 0;
}
