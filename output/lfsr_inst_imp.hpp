#ifndef __LFSR_INST_IMP_HPP_PROTECT
#error "Include lfsr_inst.hpp instead"
#endif

template <typename LFSRBaseType>
void LFSRInstrument<LFSRBaseType>::noteOn
  (StkFloat frequency, StkFloat amplitude)
{
  LFSRBaseType maximum = (1 << (sizeof(LFSRBaseType) * 3)) - 1;
  this->set_taps((LFSRBaseType)maximum*(frequency / sampleRate()));
}

template <typename LFSRBaseType>
void LFSRInstrument<LFSRBaseType>::noteOff
  (StkFloat amplitude)
{
  this->clear_taps(~0);
}

template <typename LFSRBaseType>
StkFloat LFSRInstrument<LFSRBaseType>::tick
  (unsigned int channel)
{
  return (StkFloat)this->update();
}

template <typename LFSRBaseType>
StkFrames& LFSRInstrument<LFSRBaseType>::tick
  (StkFrames& frames, unsigned int channel)
{
  return frames;
}
