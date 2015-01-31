#ifndef __LFSR_INST_IMP_HPP_PROTECT
#error "Include lfsr_inst.hpp instead"
#endif

template <typename LFSRBaseType>
void LFSRInstrument<LFSRBaseType>::noteOn
  (StkFloat frequency, StkFloat amplitude)
{
}

template <typename LFSRBaseType>
void LFSRInstrument<LFSRBaseType>::noteOff
  (StkFloat amplitude)
{
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
