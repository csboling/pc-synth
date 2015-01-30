#ifndef __VOICE_HPP_GUARD
#define __VOICE_HPP_GUARD

#include <stk/RtWvOut.h>


template <typename Source>
class Voice
{
private:
  RtAudio * dac;
  Source  * source;
public:
  Voice
    (RtAudio * dac, float rate, unsigned int channels,
     Source * source);

  virtual int tick
    (void * outputBuffer, void * inputBuffer, unsigned int nBufferFrames,
     double streamTime, RtAudioStreamStatus status);
  void start
    (void);
};

#define __VOICE_IMP_HPP_PROTECT
#include "voice_imp.hpp"
#undef __VOICE_IMP_HPP_PROTECT

#endif /* __VOICE_HPP_GUARD */
