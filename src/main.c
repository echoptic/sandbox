#include "SDL2/SDL.h"
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 1024
#define HEIGHT 768

#define ARRAY_SIZE 1000

SDL_Window *window;
SDL_Renderer *renderer;

Vec2 particle_array[HEIGHT][WIDTH];

typedef struct
{
    int x, y;
} Vec2;

void draw_particle(int x, int y);
void add_to_array(Vec2 particle, Vec2 *particle_array, int index);

Vec2 mouse;

void draw_particle(int x, int y)
{
    SDL_Rect particle;
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);

    particle.x = x;
    particle.y = y;
    particle.w = 10;
    particle.h = 10;

    SDL_RenderFillRect(renderer, &particle);
}

Vec2 new_particle(int x, int y)
{
    Vec2 particle;
    particle.x = x;
    particle.y = y;

    return particle;
}

int main(int argc, char *argv[])
{
    bool running = true;
    bool clicked = false;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "Sandbox",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            // Mouse movement
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouse.x, &mouse.y);

            // Mouse clicked
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    clicked = true;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    clicked = false;
                    break;
                }
                break;
            }
            break;
        }

        if (clicked)
        {
            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                Vec2 particle = {.x = mouse.x, .y = mouse.y};
                particle_array[h][w] = particle;
            }
        }

        // Rendering
        SDL_RenderClear(renderer);

        // Draw particles
        for (int h = 0; h < HEIGHT; h++)
            for (int w = 0; w < WIDTH; w++)
                draw_particle(particle_array[h][w], particle_array[h][w]);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    free(particle_array);

    return 0;
}