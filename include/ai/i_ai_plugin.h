#pragma once

#include <memory>

class IAI;
class IAIPlugin 
{
public:
  // Default destructor
  virtual ~IAIPlugin() {};

  // Creates an AI to play against another AI in a single epic match
  virtual std::unique_ptr<IAI> CreateAI(uint32_t id) const = 0;

  // Returns the name of the plugin
  virtual const char* name() const = 0;

  // Returns the name of the author of the plugin
  virtual const char* author() const = 0;

  // Returns the version description of the plugin
  virtual const char* version() const = 0;
};