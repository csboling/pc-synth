#ifndef __Keyboard_IMP_HPP_PROTECT
#error "Include Keyboard.hpp instead"
#endif

namespace input
{
  void KeyManager::down
    (const SDL_Event& e)
  {
    /* skip key repeat events */
    if (e.key.repeat || (e.key.state != SDL_PRESSED))
    {
      return;
    }

    auto keyList = keys.find(e.key.keysym.sym);
    if (keyList != keys.end())
    {
      for (auto key : keyList->second)
      {
        key.down();
      }
    }
  }

  void KeyManager::repeat
    (const SDL_Event& e)
  {
    if (!e.key.repeat)
    {
      return;
    }
  }

  void KeyManager::up
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
