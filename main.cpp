#include <cstdint>
#include <cstdlib>

#include <stk/RtAudio.h>

#include "lfsr.hpp"
#include "voice.hpp"

unsigned int global_counter = 0;

int main
  (void)
{
  RtAudio dac;
  Voice<LFSR<uint16_t>> v(&dac, 48000.0, 1, &maximal16);
  v.start();
  std::cin.get();
  return 0;
}
