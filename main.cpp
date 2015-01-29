#include <cstdint>
#include <cstdlib>

#include <stk/FileLoop.h>
#include <stk/RtWvOut.h>

#include "lfsr.hpp"

using namespace stk;

int tick
  (void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
   double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
  auto lfsr = (LFSR<uint16_t> *)dataPointer;
  StkFloat * samples = (StkFloat *)outputBuffer;
  for ( unsigned int i=0; i<nBufferFrames; i++ )
    *samples++ = (float)lfsr->update() / ~(uint16_t)0;
  return 0;
}

class Voice
{
private:
  RtAudio dac;
  unsigned int frameBufferSize;

public:
  Voice
    (float rate, unsigned int channels)
  {
    Stk::setSampleRate(rate);
    Stk::showWarnings(true);
    RtAudio::StreamParameters parameters;
    parameters.deviceId  = dac.getDefaultOutputDevice();
    parameters.nChannels = channels;
    frameBufferSize = RT_BUFFER_SIZE;
    try
    {
      dac.openStream(&parameters, NULL, RTAUDIO_SINT16, (unsigned int)Stk::sampleRate(),
                     &frameBufferSize, &tick, (void *)&maximal16);
    }
    catch (RtAudioError &error)
    {
      error.printMessage();
      throw error;
    }
  }

  void start
    (void)
  {
    try
    {
      dac.startStream();
    }
    catch ( RtAudioError &error )
    {
      error.printMessage();
      throw error;
    }
  }
};

int main
  (void)
{
  Voice v(48000.0, 1);
  v.start();
  std::cin.get();
  return 0;
}
