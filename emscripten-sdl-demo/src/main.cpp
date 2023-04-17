#include <emscripten.h>
#include <emscripten/html5.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;
int BOX_WIDTH = 20;
int BOX_HEIGHT = 20;

SDL_Window *pWindow;
SDL_Renderer *pRenderer;
Mix_Music *pMusic;
int count = 0;
int color = 0;

void loop() {
  SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
  SDL_RenderClear(pRenderer);

  SDL_Rect rect = {count, count, BOX_WIDTH, BOX_HEIGHT};
  switch (color) {
    case 0:
      SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
      break;
    case 1:
      SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
      break;
    case 2:
      SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
      break;
    case 3:
      SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
      break;
  }
  SDL_RenderFillRect(pRenderer, &rect);
  SDL_RenderPresent(pRenderer);

  count = (count + 1) % (WINDOW_HEIGHT - BOX_HEIGHT);
}

int filter(void *userdata, SDL_Event *event) {
  if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
    color = (color + 1) % 4;
  }
  return 0;
}

int main() {
  SDL_Init(SDL_INIT_EVERYTHING);
  pWindow = SDL_CreateWindow("hello wasm", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
  Mix_Init(MIX_INIT_MP3);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
  pMusic = Mix_LoadMUS("/BGM.mp3");
  Mix_PlayMusic(pMusic, -1);
  SDL_AddEventWatch(filter, 0);
  emscripten_set_main_loop(loop, 0, 0);
}
