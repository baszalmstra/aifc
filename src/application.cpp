#include "application.h"
#include <SDL.h>
#include <SDL_video.h>

//-------------------------------------------------------------------------------------------------
Application::Application()
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


  // Tear down the application
  return Destroy() ? 0 : -1;
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

  return true;
}

//-------------------------------------------------------------------------------------------------
bool Application::Destroy()
{
  SDL_Quit();
  return true;
}