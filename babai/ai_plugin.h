#pragma once

#include <ai/i_ai_plugin.h>

class BabaiPlugin : public IAIPlugin
{
public:
  // Default constructor
  BabaiPlugin();

  // Default destructor
  virtual ~BabaiPlugin();

  // Creates an AI to play against another AI in a single epic match
  std::unique_ptr<IAI> CreateAI(uint32_t id) const override;

  // Returns the name of the plugin
  const char* name() const override;

  // Returns the name of the author of the plugin
  const char* author() const override;

  // Returns the version description of the plugin
  const char* version() const override;
};
