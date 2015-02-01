#ifndef __LFSR_IMP_HPP_PROTECT
#error "Include lfsr.hpp instead"
#endif

template <typename T>
T LFSR<T>::update
  (void)
{
  current_ = combine(cycle(current_), eval(current_, taps));
  return current_;
}

template <typename T>
T LFSR<T>::update
  (T new_taps)
{
  taps = new_taps;
  return update();
}
