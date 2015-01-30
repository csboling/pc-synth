#ifndef __LFSR_IMP_HPP_PROTECT
#error "Include lfsr.hpp instead"
#endif

template <typename T>
T LFSR<T>::tick
  (void)
{
  current_ = combine(cycle(current_), eval(current_, taps_));
  return current_;
}

template <typename T>
T LFSR<T>::tick
  (T new_taps)
{
  taps_ = new_taps;
  return tick();
}
