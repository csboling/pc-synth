#ifndef __EventManager_HPP_GUARD
#define __EventManager_HPP_GUARD

#include <SDL.h>
#include <map>
#include <queue>

namespace std
{
  template <>
  struct less<SDL_Event *>
  {
    bool operator()
      (const SDL_Event*& x, const SDL_Event*& y)
    {
      return (x->type < y->type);
    }
  };
};

template <typename T>
class EventManager
{
using eventMap_t = std::map<const SDL_Event *, std::priority_queue<T>>;
private:
  eventMap_t eventMap;
  SDL_EventFilter lastFilter;
  void * lastFilterData;
public:
  EventManager
    (eventMap_t keyMap);
  ~EventManager();
};

#define __EventManager_IMP_HPP_PROTECT
#include "EventManager_imp.hpp"
#undef  __EventManager_IMP_HPP_PROTECT

#endif /* __KEYBOARD_HPP_GUARD */
