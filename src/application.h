#pragma once

#include <memory>
#include <vector>
#include <chrono>

struct SDL_Window;
union SDL_Event;
typedef void *SDL_GLContext;

class PluginWrapper;
class Battle;

class Application final
{
public:
  /// Default constructor (does nothing but initialize default values)
  Application();

  /// Default destructor
  ~Application();

  /// Called to actually run the application
  int Run();

private:
  /// Initializes the application
  bool Initialize();

  /// Tears down the application
  bool Destroy();

  /// Called to process window messages, returns false if the application should quit
  bool ProcessEvents();

  /// Called to handle an SDL event, returns false if the application should quit
  bool HandleEvent(const SDL_Event& evt);

  /// Called to update the running application
  void Update();

  /// Called to draw the running application
  void Draw();

private:
  SDL_Window *window_;
  SDL_GLContext mainContext;

  std::vector<std::unique_ptr<PluginWrapper>> plugins_;
  std::unique_ptr<Battle> battle_;  

  std::chrono::time_point<std::chrono::high_resolution_clock> lastTime_;
};