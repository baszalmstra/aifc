#pragma once

#include <ai/i_ai_plugin.h>

class TestAIPlugin : public IAIPlugin
{
public:
  // Default constructor
  TestAIPlugin();

  // Default destructor
  virtual ~TestAIPlugin();

  // Creates an AI to play against another AI in a single epic match
  std::unique_ptr<IAI> CreateAI() const override;

  // Returns the name of the plugin
  const char* name() const override;

  // Returns the name of the author of the plugin
  const char* author() const override;

  // Returns the version description of the plugin
  const char* version() const override;
};
