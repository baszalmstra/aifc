#include "application.h"
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_opengl.h>

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
  SDL_GetWindowSize(window_, &vpWidth, &vpHeight);
  glViewport(0, 0, vpWidth, vpHeight);

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

  return true;
}

//-------------------------------------------------------------------------------------------------
bool Application::Destroy()
{
  // Shut down SDL
  SDL_Quit();

  return true;
}