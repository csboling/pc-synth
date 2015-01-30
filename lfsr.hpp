#ifndef __LFSR_HPP_GUARD
#define __LFSR_HPP_GUARD

#include <functional>
#include <stk/Generator.h>

template <typename T>
class LFSR
{
private:
  T init_;
  T current_;
  T taps_;
  std::function<T (T value)>         cycle;
  std::function<T (T value, T taps)> eval;
  std::function<T (T curr,  T next)> combine;

public:
  /* constructor & destructor */
  LFSR
    ( T init,
      T taps,
      T (*cycle)(T value)
        = [](T l) { return (T)(l << 1); },
      T (*eval)(T value, T taps)
        = [](T v, T t) { return (T)(__builtin_popcount(v & t) % 2); },
      T (*combine)(T curr,  T next)
        = [](T l, T r) { return (T)(l | r); }
    )
    : init_(init)
    , current_(init)
    , taps_(taps)
    , cycle(cycle)
    , eval(eval)
    , combine(combine) {}

  /* accessor methods */
  const T & init()    const { return init_; }
  const T & current() const { return current_; }
  const T & taps()    const { return taps_; }

  /* methods */
  T tick
    (void);

  T tick
    (T new_taps);
};

LFSR<uint16_t> maximal16(~0, 0xD008);

#define __LFSR_IMP_HPP_PROTECT
#include "lfsr_imp.hpp"
#undef  __LFSR_IMP_HPP_PROTECT

#endif /* #ifndef __LFSR_HPP_GUARD */
