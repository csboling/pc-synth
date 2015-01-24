#include <cstdint>
#include <fstream>

#include <stk/FileLoop.h>
#include <stk/FileWvOut.h>

#include "lfsr.hpp"

using namespace stk;

int main
  (void)
{
  const uint16_t init = ~0;
  const uint16_t taps = (1 << 15)
                      | (1 << 14)
                      | (1 << 12)
                      | (1 << 3);
  std::ofstream lfsrFile("maximal.raw", std::ios::out | std::ios::binary);
  LFSR<uint16_t> lfsrVal(init, taps);

  do
  {
    lfsrFile << lfsrVal.current();
    lfsrVal.update();
  } while (lfsrVal.current() != lfsrVal.init());

  Stk::setSampleRate( 44100.0 );
  FileLoop input( "maximal.raw", true );
  FileWvOut output( "wavs/lfsr.wav", 1, FileWrite::FILE_WAV, Stk::STK_SINT16 );

  input.setFrequency( 440.0 );
  for ( int i = 0; i < 40000; ++i)
  {
    output.tick( input.tick() );
  }

  return 0;
}
