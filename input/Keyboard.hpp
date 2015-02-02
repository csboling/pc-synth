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
            std::bind(&KeyManager::down, this, _1),
          },
        },
        {
          SDL_KEYUP,
          {
            std::bind(&KeyManager::down, this, _1),
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
      (const SDL_Event& e)
    {
      auto keyList = keys.find(e.key.keysym.sym);
      if (keyList != keys.end())
      {
        for (auto key : keyList->second)
        {
          key.down();
        }
      }
    }

    void up
      (const SDL_Event& e)
    {
      auto keyList = keys.find(e.key.keysym.sym);
      if (keyList != keys.end())
      {
        for (auto key : keyList->second)
        {
          key.up();
        }
      }
    }
  };
};


#endif /* __Keyboard_HPP_GUARD */
