#include <iostream>
#include <fstream>
#include <cstdint>

#include <functional>

using namespace std::placeholders;



template <class T>
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
    , combine(combine)
  {
  }

  /* accessor methods */
  const T & init()    const { return init_; }
  const T & current() const { return current_; }
  const T & taps()    const { return taps_; }

  /* methods */
  T update
    (void)
  {
    current_ = combine(cycle(current_), eval(current_, taps_));
    return current_;
  }

  T update
    (T new_taps)
  {
    taps_ = new_taps;
    return update();
  }
};

int main
  (void)
{

  const uint16_t init = ~0;
  const uint16_t taps = (1 << 15)
                      | (1 << 14)
                      | (1 << 12)
                      | (1 << 3);

  std::ofstream lfsrFile;
  LFSR<uint16_t> lfsrVal(0xFFFF, 0xD008);

    lfsrFile.open("maximal.raw", std::ios::out | std::ios::binary);

  do
  {
    lfsrFile << lfsrVal.current() << std::endl;
    lfsrVal.update();
  } while (lfsrVal.current() != lfsrVal.init());

  return 0;
}
