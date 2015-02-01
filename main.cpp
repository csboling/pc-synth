#include <cstdint>
#include <cstdlib>

#include <stk/RtAudio.h>

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
  Voice<LFSRInstrument<uint16_t>> v(&dac, 48000.0, 1,
                                    new LFSRInstrument<uint16_t>(~0, 0xD008));
  v.start();
  std::cin.get();
  return 0;
}
