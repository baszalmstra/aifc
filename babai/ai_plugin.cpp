#include "ai_plugin.h"
#include "babai.h"
#include <iostream>

//-------------------------------------------------------------------------------------------------
BabaiPlugin::BabaiPlugin()
{

}

//-------------------------------------------------------------------------------------------------
BabaiPlugin::~BabaiPlugin()
{

}

//-------------------------------------------------------------------------------------------------
const char *BabaiPlugin::name() const
{
  return "Babai";
}

//-------------------------------------------------------------------------------------------------
const char *BabaiPlugin::author() const
{
  return "Bas";
}

//-------------------------------------------------------------------------------------------------
const char* BabaiPlugin::version() const
{
  return "0.1";
}

//-------------------------------------------------------------------------------------------------
std::unique_ptr<IAI> BabaiPlugin::CreateAI(uint32_t id) const
{
  return std::unique_ptr<IAI>(new Babai(id));
}

//-------------------------------------------------------------------------------------------------
// Magic function to expose this dll to the simulation
//-------------------------------------------------------------------------------------------------
#if WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C" EXPORT IAIPlugin* CreatePlugin()
{
  return new BabaiPlugin();
}