#ifndef __LFSRInstrument_HPP_GUARD
#define __LFSRInstrument_HPP_GUARD

#include "../sources/LFSR.hpp"
#include <stk/Instrmnt.h>

using stk::Instrmnt;
using stk::StkFloat;
using stk::StkFrames;

namespace output
{
  template <typename LFSRBaseType>
  class LFSRInstrument : private LFSR<LFSRBaseType>
                       , public virtual Instrmnt
  {
    using LFSR<LFSRBaseType>::LFSR;

  public:
    void noteOn
      (StkFloat frequency, StkFloat amplitude = 1.0);
    void noteOff
      (StkFloat amplitude);

    StkFloat tick
      (unsigned int channel = 0);
    StkFrames& tick
      (StkFrames& frames, unsigned int channel = 0);
  };
};

#define __LFSRInstrument_IMP_HPP_PROTECT
#include "LFSRInstrument_imp.hpp"
#undef  __LFSRInstrument_IMP_HPP_PROTECT

#endif /* __LFSR_INST_HPP_GUARD */
