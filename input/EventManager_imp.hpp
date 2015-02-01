#ifndef __EventManager_IMP_HPP_PROTECT
#error "Include EventManager.hpp instead"
#endif

namespace input
{
  template <typename SpecializedEvtMgr>
  int processEvents
    (void * data, SDL_Event * event)
  {
    unsigned int actionCount = 0;
    SpecializedEvtMgr * m = (SpecializedEvtMgr *)data;

    m->lastFilter(m->lastFilterData, event);
    for (auto action : m->eventMap.find(event->type)->second)
    {
      action(*event);
      actionCount++;
    }

    return actionCount;
  }

  template <typename Behavior>
  EventManager<Behavior>::EventManager
    (eventMap_t& eventMap)
    : eventMap(eventMap)
  {
    SDL_GetEventFilter(&lastFilter, &lastFilterData);
    SDL_SetEventFilter(processEvents<EventManager<Behavior>>, (void *)this);
  }

  template <typename Behavior>
  EventManager<Behavior>::~EventManager()
  {
    SDL_SetEventFilter(lastFilter, lastFilterData);
  }
};
