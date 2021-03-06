#ifndef __Voice_IMP_HPP_PROTECT
#error "Include Voice.hpp instead"
#endif

using namespace stk;

template <typename Source>
static int tick_callback
  (void * outputBuffer, void * inputBuffer, unsigned int nBufferFrames,
   double streamTime, RtAudioStreamStatus status, void * dataPointer)
{
  output::Voice<Source> * v = (output::Voice<Source> *)dataPointer;
  return v->tick(outputBuffer, inputBuffer, nBufferFrames,
                 streamTime, status);
}

namespace output
{
  template <typename Source>
  Voice<Source>::Voice
    (RtAudio * dac, float rate, unsigned int channels,
     Source * source)
    : dac(dac)
    , source(source)
  {
    Stk::setSampleRate(rate);
    Stk::showWarnings(true);
    RtAudio::StreamParameters parameters;
    unsigned int frameBufferSize = RT_BUFFER_SIZE;

    parameters.deviceId  = dac->getDefaultOutputDevice();
    parameters.nChannels = channels;

    try
    {
      dac->openStream(&parameters, NULL, RTAUDIO_SINT16,
                      (unsigned int)Stk::sampleRate(), &frameBufferSize,
                      &tick_callback<Source>, (void *)this);
    }
    catch (RtAudioError &error)
    {
      error.printMessage();
      throw error;
    }
  }

  template <typename Source>
  int Voice<Source>::tick
    (void * outputBuffer, void * inputBuffer, unsigned int nBufferFrames,
     double streamTime, RtAudioStreamStatus status)
  {
    StkFloat * samples = (StkFloat *)outputBuffer;
    for ( unsigned int i=0; i<nBufferFrames; i++ )
    {
      *samples++ = (StkFloat)source->tick() / ~(uint16_t)0;
    }
    return 0;
  }

  template <typename Source>
  void Voice<Source>::start
    (void)
  {
    try
    {
      dac->startStream();
    }
    catch ( RtAudioError &error )
    {
      error.printMessage();
      throw error;
    }
  }
};
