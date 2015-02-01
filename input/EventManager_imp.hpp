#ifndef __EventManager_IMP_HPP_PROTECT
#error "Include EventManager.hpp instead"
#endif

template <typename T>
static int processEvents
  (const SDL_Event * event, void * data)
{
  unsigned int actionCount = 0;
  T * m = (T *)data;

  m->lastFilter(event, m->lastFilterData);
  for (auto action : m->eventMap.find(event))
  {
    action();
    actionCount++;
  }

  return actionCount;
}

template <typename T>
EventManager<T>::EventManager
  (eventMap_t eventMap)
  : eventMap(eventMap)
{
  SDL_GetEventFilter(&lastFilter, &lastFilterData);
  SDL_SetEventFilter(processEvents<EventManager<T>>, this);
}

template <typename T>
EventManager<T>::~EventManager()
{
  SDL_SetEventFilter(lastFilter, lastFilterData);
}
