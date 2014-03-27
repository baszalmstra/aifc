#include "plugin_wrapper.h"
#include "ai/i_ai_plugin.h"
#include <SDL_loadso.h>
#include <iostream>

typedef IAIPlugin* (*CreatePluginFn)();

//-------------------------------------------------------------------------------------------------
PluginWrapper::PluginWrapper() : sharedObject_(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
PluginWrapper::~PluginWrapper()
{
  // Destroy the plugin
  plugin_.reset();

  // Release the library
  if (sharedObject_ != nullptr)
  {
    SDL_UnloadObject(sharedObject_);
    sharedObject_ = nullptr;
  }
}

//-------------------------------------------------------------------------------------------------
bool PluginWrapper::Load(const std::string& path)
{
#ifdef _WIN32
  const char* extension = ".dll";
  const char* prepend = "";
#elif __APPLE__
  const char* extension = ".dylib";
  const char* prepend = "lib";
#else
  const char* extension = ".so";
  const char* prepend = "lib";
#endif

  // Load the library
  std::string pathAndExtensions = std::string(prepend) + path + extension;
  sharedObject_ = SDL_LoadObject(pathAndExtensions.c_str());
  if (sharedObject_ == nullptr)
  {
    std::cerr << "Unable to load '" << pathAndExtensions << "': " << SDL_GetError() << std::endl;
    return false;
  }

  // Load the creation function
  CreatePluginFn createPlugin = (CreatePluginFn)SDL_LoadFunction(sharedObject_, "CreatePlugin");
  if (createPlugin == nullptr)
  {
    std::cerr << "Unable to locate plugin entry point in '" << pathAndExtensions << "': " << SDL_GetError() << std::endl;
    return false;
  }

  // Otherwise create the darn object
  plugin_ = std::unique_ptr<IAIPlugin>(createPlugin());

  // Report on success
  if (plugin_)
    std::cout << "Succesfully loaded '" << plugin_->name() << "' (" << plugin_->version() << ") created by " << plugin_->author() << std::endl;

  return (bool)plugin_;
}

//-------------------------------------------------------------------------------------------------
std::unique_ptr<PluginWrapper> PluginWrapper::LoadPlugin(const std::string& path)
{
  std::unique_ptr<PluginWrapper> wrapper(new PluginWrapper());
  if (!wrapper->Load(path))
    return nullptr;

  return std::move(wrapper);
}