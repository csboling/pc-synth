#ifndef __Keyboard_HPP_GUARD
#define __Keyboard_HPP_GUARD

#include <functional>
#include <map>

#include <SDL.h>

#include "EventManager.hpp"

namespace input
{
  using std::placeholders::_1;

  struct KeyAction
  {
    std::function<void(void)> down, up;
    KeyAction
      (std::function<void(void)> down,
       std::function<void(void)> up)
      : down(down)
      , up(up) {}
  };

  typedef std::map
          <
            SDL_Keycode,
            std::vector< KeyAction >
          > KeyMap;

  class KeyManager : private EventManager
  {
  private:
    EventMap events
      {
        {
          SDL_KEYDOWN,
          {
            std::bind(&KeyManager::down,   this, _1),
            std::bind(&KeyManager::repeat, this, _1),
          },
        },
        {
          SDL_KEYUP,
          {
            std::bind(&KeyManager::down,   this, _1),
          },
        },
      };

    KeyMap& keys;

  public:
    KeyManager
      (KeyMap& keys)
      : EventManager(events)
      , keys(keys)
      {}

    void down
      (const SDL_Event& e);
    void repeat
      (const SDL_Event& e);
    void up
      (const SDL_Event& e);
  };
};

#define __Keyboard_IMP_HPP_PROTECT
#include "Keyboard_imp.hpp"
#undef  __Keyboard_IMP_HPP_PROTECT

#endif /* __Keyboard_HPP_GUARD */
