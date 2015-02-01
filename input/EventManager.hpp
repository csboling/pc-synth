#ifndef __EventManager_HPP_GUARD
#define __EventManager_HPP_GUARD

#include <SDL.h>
#include <map>
#include <queue>

namespace input
{
  template <typename SpecializedEvtMgr>
  int processEvents
    (void * data, SDL_Event * event);

  template <typename Behavior>
  class EventManager
  {
    using eventMap_t = std::map
                       <
                         decltype(SDL_Event::type),
                         std::vector< Behavior >
                       >;
  private:
    eventMap_t eventMap;
    SDL_EventFilter lastFilter;
    void * lastFilterData;
  public:
    EventManager
      (eventMap_t& keyMap);
    ~EventManager();

  template <typename SpecializedEvtMgr>
  friend int processEvents
    (void * data, SDL_Event * event);
  };
};

#define __EventManager_IMP_HPP_PROTECT
#include "EventManager_imp.hpp"
#undef  __EventManager_IMP_HPP_PROTECT

#endif /* __KEYBOARD_HPP_GUARD */
