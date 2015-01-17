#include <iostream>
#include <fstream>
#include <cstdint>

#include <functional>

using namespace std::placeholders;



template <class T>
class LFSR
{
private:
  T taps;
  std::function<T (T value)>         cycle;
  std::function<T (T value, T taps)> eval;
  std::function<T (T curr,  T next)> combine;

public:
  T init;
  T current;
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
    : init(init)
    , current(init)
    , taps(taps)
    , cycle(cycle)
    , eval(eval)
    , combine(combine)
  {
  }

  T update
    (void)
  {
    current = combine(cycle(current), eval(current, taps));
    return current;
  }

  T update
    (T new_taps)
  {
    taps = new_taps;
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
//    lfsrFile.write((const char *)&lfsrVal.current, sizeof(lfsrVal.current));
    lfsrFile << lfsrVal.current << std::endl;
    lfsrVal.update();
  } while (lfsrVal.current != lfsrVal.init);

  return 0;
}
