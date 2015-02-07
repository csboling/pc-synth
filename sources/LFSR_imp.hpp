#ifndef __LFSR_IMP_HPP_PROTECT
#error "Include LFSR.hpp instead"
#endif

template <typename T>
T LFSR<T>::update
  (void)
{
  if (rateCounter == rate)
  {
    rateCounter = 0;
    current_ = combine(cycle(current_), eval(current_, taps));
  }
  else
  {
    rateCounter++;
  }
  return current_;
}

template <typename T>
T LFSR<T>::update
  (T new_taps)
{
  taps = new_taps;
  return update();
}
