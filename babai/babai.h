#pragma once

#include "ai/i_ai.h"
#include <cstdint>

class Babai : public IAI 
{
public:
  Babai(uint32_t id);

  virtual ~Babai();

  /// Update the state of the world
  void Update(const AIInput& input, AICommand& command) override;

private:
  uint32_t id_;
  uint32_t randomOffset_;
};
