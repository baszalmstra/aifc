#pragma once

#include <vector>
#include <cstdint>

typedef uint32_t ShipId;

enum AICommandAction {
	FORCE = 0x0, 
	TORQUE, 
	SHOOT
};

class AICommand {

public:
  /// Default constructor
  AICommand() {};

  /// Default destructor
  virtual ~AICommand(){};
};
