#include <cstdint>
#include <cstdlib>
#include <cstdio>

#include <stk/RtAudio.h>
#include <SDL.h>

#include "output/LFSRInstrument.hpp"
#include "output/Voice.hpp"
#include "input/Keyboard.hpp"

unsigned int global_counter = 0;

void startSDL
  (void)
{
  if (SDL_Init(SDL_INIT_EVENTS))
  {
    std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
    throw;
  }
  if (!SDL_CreateWindow("", 100, 100, 50, 50, SDL_WINDOW_SHOWN))
  {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    throw;
  }
}

int main
  (void)
{
  using output::Voice;
  using output::LFSRInstrument;

  RtAudio dac;
  Voice<LFSRInstrument<uint16_t>> v(&dac, 48000.0, 1,
                                    new LFSRInstrument<uint16_t>(~0, 0xD008));
  input::KeyMap keymap
    {
      {
        SDLK_q,
        {
          input::KeyAction
          (
            [v] (void)
            {
              v.source->noteOn((float)(1 << 0));
            },
            [v] (void)
            {
              v.source->noteOff();
            }
          ),
        },
      },
      {
        SDLK_w,
        {
          input::KeyAction
          (
            [v] (void)
            {
              v.source->noteOn((float)(1 << 1));
            },
            [v] (void)
            {
              v.source->noteOff();
            }
          ),
        },
      },
      {
        SDLK_e,
        {
          input::KeyAction
          (
            [v] (void) { v.source->noteOn((float)(1 << 2)); },
            [v] (void) { v.source->noteOff(); }
          ),
        },
      },
    };
  input::KeyManager keyMgr(keymap);

  try
  {
    startSDL();
  }
  catch (...)
  {
    return -1;
  }

  v.start();

  while (1)
  {
    SDL_PumpEvents();
  }

  SDL_Quit();
  return 0;
}
