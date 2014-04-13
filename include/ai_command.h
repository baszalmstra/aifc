#pragma once

#include <vector>
#include <cstdint>

typedef uint32_t ShipId;

class AICommand {

public:
  /// Default constructor
  AICommand() {};

  /// Default destructor
  virtual ~AICommand(){};
};
