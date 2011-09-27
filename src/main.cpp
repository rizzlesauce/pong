/*
 * main.cpp
 *
 *  Created on: Nov 26, 2010
 *      Author: ross
 */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_draw.h>
#include <cstdlib>
#include <ctime>>
#include "Ball.h"
#include <cmath>

#define PI 3.141592654f

Uint32 loop_duration, current_ticks, loop_start;

int screen_width = 1680;
int screen_height = 1050;

int main(int argc, char *argv[]) {
    SDL_Surface *screen;
    SDL_Surface *image;

    Uint32 flags = SDL_SWSURFACE|SDL_FULLSCREEN;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
       return -1;
    }

    screen = SDL_SetVideoMode(screen_width, screen_height, 16, flags);
    if (screen == NULL) {
       printf(SDL_GetError());
    }

    // Load PNG using SDL
    image  = SDL_LoadBMP("main_background.bmp");
    if (image == NULL) {
       printf(SDL_GetError());
    }

    SDL_Surface *ball_image = SDL_LoadBMP("ball.bmp");
    if (ball_image == NULL) {
        printf(SDL_GetError());
    }

    Ball ball;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.diameter = 30;
//    ball.velocity = 10.0f;
    ball.velocity = 4.0f;

    SDL_Rect ball_rect;
    ball_rect.x = 0;
    ball_rect.y = 0;
    ball_rect.w = ball.diameter;
    ball_rect.h = ball.diameter;

    SDL_Rect ball_screen_rect;

    // get random direction
    srand(time(NULL));
//    ball.direction = (rand() % 2) * PI;
    ball.direction = (rand() % 360) * (2.0f * PI) / 360.0f;

    loop_start = SDL_GetTicks();
    bool play = true;
    SDL_Event event;
    while (play) {
       // get events
       if (SDL_PollEvent(&event)) {
           switch(event.type) {
           case SDL_KEYDOWN:
               play = false;
               // handle key down
               break;
           case SDL_KEYUP:
               // handle key up
               break;
           case SDL_QUIT:
               play = false;
               break;
           }
       }
       current_ticks = SDL_GetTicks();
       loop_duration = current_ticks - loop_start;
       loop_start = current_ticks;

        // Puting image on the screen up
        if (SDL_BlitSurface(image, NULL, screen, NULL) == -1) {
           printf("Error with blit surface\n");
        }

        // move the ball
        float new_x, new_y;

        new_x = ball.x + cos(ball.direction) * ball.velocity;
        new_y = ball.y + sin(ball.direction) * ball.velocity;

        // check for ball intersection
        if ((new_x + ball.diameter) > screen_width || new_x < 0) {
            ball.direction = ball.direction + PI;
        }
        if ((new_y < 0 || (new_y + ball.diameter) > screen_height)) {
            ball.direction = (2.0f * PI) - ball.direction;
        }
        ball.x = new_x;
        ball.y = new_y;

        ball.x = ball.x + cos(ball.direction) * ball.velocity;
        ball.y = ball.y + sin(ball.direction) * ball.velocity;

        ball_screen_rect.x = floor(ball.x);
        ball_screen_rect.y = floor(ball.y);
        ball_screen_rect.w = ball.diameter;
        ball_screen_rect.h = ball.diameter;

        if (SDL_BlitSurface(ball_image, &ball_rect, screen, &ball_screen_rect)) {
            printf("Error with blit surface\n");
        }

        // flip the double buffer
        if (SDL_Flip(screen) == -1) {
           printf("Error with SDL_Flip\n");
        }
    }
}

