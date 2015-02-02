#include <cstdint>
#include <cstdlib>
#include <cstdio>

#include <stk/RtAudio.h>
#include <SDL.h>

#include "output/LFSRInstrument.hpp"
#include "output/Voice.hpp"
#include "input/Keyboard.hpp"

unsigned int global_counter = 0;

int main
  (void)
{
  using output::Voice;
  using output::LFSRInstrument;

  RtAudio dac;

  SDL_Event dummy_event;
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
    return -1;
  }
  SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  if (win == nullptr){
  	std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
  	SDL_Quit();
  	return 1;
  }

  input::KeyMap keymap
    {
      {
        SDLK_q,
        {
          input::KeyAction
          (
            [] (void) { std::cout << 'Q'; std::cout.flush(); },
            [] (void) { std::cout << '!'; std::cout.flush(); }
          ),
        },
      },
    };
  input::KeyManager keyMgr(keymap);

  while (SDL_WaitEvent(&dummy_event));

//  Voice<LFSRInstrument<uint16_t>> v(&dac, 48000.0, 1,
//                                    new LFSRInstrument<uint16_t>(~0, 0xD008));
//  v.start();
//  std::cin.get();

  SDL_Quit();
  return 0;
}
