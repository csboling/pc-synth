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
    for (auto action : m->events.find(event->type)->second)
    {
      action(*event);
      actionCount++;
    }

    return actionCount;
  }

  EventManager::EventManager
    (EventMap& events)
    : events(events)
  {
    SDL_GetEventFilter(&lastFilter, &lastFilterData);
    SDL_SetEventFilter(processEvents, (void *)this);
  }

  EventManager::~EventManager()
  {
    SDL_SetEventFilter(lastFilter, lastFilterData);
  }
};
