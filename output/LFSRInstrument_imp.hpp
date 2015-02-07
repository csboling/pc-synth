#ifndef __LFSRInstrument_IMP_HPP_PROTECT
#error "Include LFSRInstrument.hpp instead"
#endif

namespace output
{
  template <typename LFSRBaseType>
  void LFSRInstrument<LFSRBaseType>::noteOn
    (StkFloat frequency, StkFloat amplitude)
  {
    std::cout << frequency << std::endl;
    this->set_taps((LFSRBaseType)frequency);
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
};
