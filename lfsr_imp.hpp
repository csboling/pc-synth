#ifndef __LFSR_HPP_GUARD
#error "Include lfsr.hpp instead"
#endif

template <typename T>
T LFSR<T>::update
  (void)
{
  current_ = combine(cycle(current_), eval(current_, taps_));
  return current_;
}

template <typename T>
T LFSR<T>::update
  (T new_taps)
{
  taps_ = new_taps;
  return update();
}
