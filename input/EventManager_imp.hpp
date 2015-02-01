#ifndef __EventManager_IMP_HPP_PROTECT
#error "Include EventManager.hpp instead"
#endif

namespace input
{
  int processEvents
    (void * data, SDL_Event * event)
  {
    unsigned int actionCount = 0;
    EventManager * m = (EventManager *)data;

    m->lastFilter(m->lastFilterData, event);
    for (auto action : m->eventMap.find(event->type)->second)
    {
      action(*event);
      actionCount++;
    }

    return actionCount;
  }

  EventManager::EventManager
    (eventMap_t& eventMap)
    : eventMap(eventMap)
  {
    SDL_GetEventFilter(&lastFilter, &lastFilterData);
    SDL_SetEventFilter(processEvents, (void *)this);
  }

  EventManager::~EventManager()
  {
    SDL_SetEventFilter(lastFilter, lastFilterData);
  }
};
