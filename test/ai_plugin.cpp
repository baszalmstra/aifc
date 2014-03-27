#include "ai_plugin.h"
#include "testai.h"
#include <iostream>

//-------------------------------------------------------------------------------------------------
TestAIPlugin::TestAIPlugin()
{

}

//-------------------------------------------------------------------------------------------------
TestAIPlugin::~TestAIPlugin()
{

}

//-------------------------------------------------------------------------------------------------
const char *TestAIPlugin::name() const
{
  return "TestAI";
}

//-------------------------------------------------------------------------------------------------
const char *TestAIPlugin::author() const
{
  return "The Authors of Everything";
}

//-------------------------------------------------------------------------------------------------
const char* TestAIPlugin::version() const
{
  return "first";
}

//-------------------------------------------------------------------------------------------------
std::unique_ptr<IAI> TestAIPlugin::CreateAI() const
{
  return std::unique_ptr<IAI>(new TestAI());
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
  return new TestAIPlugin();
}