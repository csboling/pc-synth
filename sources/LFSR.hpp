#ifndef __LFSR_HPP_GUARD
#define __LFSR_HPP_GUARD

#include <functional>

template <typename T>
class LFSR
{
private:
  T init_;
  T current_;
  T taps;
  unsigned int rate;
  unsigned int rateCounter;
  std::function<T (T value)>         cycle;
  std::function<T (T value, T taps)> eval;
  std::function<T (T curr,  T next)> combine;

public:
  /* constructor & destructor */
  LFSR
    ( T init,
      T taps,
      unsigned int rate = 0,
      T (*cycle)(T value)
        = [](T l) { return (T)(l << 1); },
      T (*eval)(T value, T taps)
        = [](T v, T t) { return (T)(__builtin_popcount(v & t) % 2); },
      T (*combine)(T curr,  T next)
        = [](T l, T r) { return (T)(l | r); }
    )
    : init_      (init)
    , current_   (init)
    , taps       (taps)
    , rate       (rate)
    , rateCounter(0)

    , cycle   (cycle)
    , eval    (eval)
    , combine (combine) {}

  /* accessor methods */
  const T & init()    const { return init_; }
  const T & current() const { return current_; }
  void set_taps
    (T mask) { taps |= mask; }
  void clear_taps
    (T mask) { taps &= ~mask; }

  /* methods */
  T update
    (void);

  T update
    (T new_taps);
};

LFSR<uint16_t> maximal16(~0, 0xD008);

#define __LFSR_IMP_HPP_PROTECT
#include "LFSR_imp.hpp"
#undef  __LFSR_IMP_HPP_PROTECT

#endif /* #ifndef __LFSR_HPP_GUARD */
