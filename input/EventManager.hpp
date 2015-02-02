#ifndef __EventManager_HPP_GUARD
#define __EventManager_HPP_GUARD

#include <SDL.h>
#include <map>
#include <queue>

namespace input
{
  typedef std::map
          <
            decltype(SDL_Event::type),
            std::vector< std::function<void(SDL_Event&)> >
          > EventMap;

  int processEvents
    (void * data, SDL_Event * event);

  template <typename T>
  T& selectSDLEventMember(SDL_Event& u)
  {
    return *((T *)&u);
  }

  class EventManager
  {
  private:
    EventMap& events;
    SDL_EventFilter lastFilter;
    void * lastFilterData;
  public:
    EventManager
      (EventMap& keyMap);
    ~EventManager();

  friend int processEvents
    (void * data, SDL_Event * event);
  };
};

#define __EventManager_IMP_HPP_PROTECT
#include "EventManager_imp.hpp"
#undef  __EventManager_IMP_HPP_PROTECT

#endif /* __KEYBOARD_HPP_GUARD */
