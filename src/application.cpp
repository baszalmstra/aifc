#include "application.h"
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_opengl.h>
#include "plugin_wrapper.h"
#include "ai/i_ai_plugin.h"
#include "ai/i_ai.h"
#include <algorithm>
#include "battle.h"
#include <time.h>

//-------------------------------------------------------------------------------------------------
Application::Application() :
  window_(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
Application::~Application()
{

}

//-------------------------------------------------------------------------------------------------
int Application::Run()
{
  // Initialize the application
  if (!Initialize())
    return -1;

  // Main loop
  while (ProcessEvents())
  {
    Update();
    Draw();
  }

  // Tear down the application
  return Destroy() ? 0 : -1;
}

//-------------------------------------------------------------------------------------------------
bool Application::ProcessEvents()
{
  bool shouldQuit = false;

  SDL_Event evt;
  while (SDL_PollEvent(&evt))
    shouldQuit |= !HandleEvent(evt);

  return !shouldQuit;
}

//---------------------------------------------------------------------------------------------------
bool Application::HandleEvent(const SDL_Event& evt)
{
  // Handle quit 
  if (evt.type == SDL_QUIT || evt.type == SDL_WINDOWEVENT_CLOSE)
    return false;

  // Handle alt+F4
  if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_F4 &&
    (evt.key.keysym.mod == KMOD_LALT || evt.key.keysym.mod == KMOD_RALT))
    return false;

  return true;
}

//---------------------------------------------------------------------------------------------------
void Application::Update()
{
  battle_->Update();
}

//---------------------------------------------------------------------------------------------------
void Application::Draw()
{
  // Set the clear color
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  // Actually clear
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Setup viewport size
  int vpWidth, vpHeight;
  SDL_GL_GetDrawableSize(window_, &vpWidth, &vpHeight);
  glViewport(0, 0, vpWidth, vpHeight);

  // Determine aspect ratio
  float aspectRatio = (float) vpWidth / vpHeight;
  const float viewportSize = 50.0f;
  const float halfViewportSize = viewportSize * 0.5f;

  // Setup view matrix
  glLoadIdentity();
  glOrtho(-halfViewportSize * aspectRatio, halfViewportSize * aspectRatio, -halfViewportSize, halfViewportSize, 0.0f, 1.0f);

  // Draw the world
  battle_->Draw();

  // Preset the view
  SDL_GL_SwapWindow(window_);
}

//-------------------------------------------------------------------------------------------------
bool Application::Initialize()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  // Create an opengl context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // Create a window and a renderer
  if ((window_ = SDL_CreateWindow("aifc", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_ALLOW_HIGHDPI)) == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Unable to initialize SDL graphics: %s", SDL_GetError());
    return false;
  }

  // Create an opengl context
  mainContext = SDL_GL_CreateContext(window_);
  if (!mainContext)
  {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Unable to initialize SDL OpenGL: %s", SDL_GetError());
    return false;
  }

  // Initialize random seed
  srand((uint32_t)time(nullptr));

  // Load the plugin with the given name
  plugins_.emplace_back(PluginWrapper::LoadPlugin("testai"));
  if (std::any_of(plugins_.cbegin(), plugins_.cend(), [](const std::unique_ptr<PluginWrapper> &wrapper) { return !wrapper; }))
    return false;

  // Create a battle
  std::vector<IAIPlugin*> plugins;
  std::transform(plugins_.begin(), plugins_.end(), std::back_inserter<std::vector<IAIPlugin*>>(plugins), [](const std::unique_ptr<PluginWrapper> &wrapper) { return wrapper->plugin(); });
  battle_ = std::unique_ptr<Battle>(new Battle());
  battle_->Initialize(plugins);

  return true;
}

//-------------------------------------------------------------------------------------------------
bool Application::Destroy()
{
  // Shut down SDL
  SDL_Quit();

  return true;
}