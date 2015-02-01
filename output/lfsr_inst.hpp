#ifndef __LFSR_INST_HPP_GUARD
#define __LFSR_INST_HPP_GUARD

#include "../sources/lfsr.hpp"
#include <stk/Instrmnt.h>

using stk::Instrmnt;
using stk::StkFloat;
using stk::StkFrames;

template <typename LFSRBaseType>
class LFSRInstrument : private LFSR<LFSRBaseType>
                     , public virtual Instrmnt
{
  using LFSR<LFSRBaseType>::LFSR;

public:
  void noteOn
    (StkFloat frequency, StkFloat amplitude);
  void noteOff
    (StkFloat amplitude);

  StkFloat tick
    (unsigned int channel = 0);
  StkFrames& tick
    (StkFrames& frames, unsigned int channel = 0);
};

#define __LFSR_INST_IMP_HPP_PROTECT
#include "lfsr_inst_imp.hpp"
#undef  __LFSR_INST_IMP_HPP_PROTECT

#endif /* __LFSR_INST_HPP_GUARD */
