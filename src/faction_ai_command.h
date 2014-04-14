#pragma once 

#include "ai_command.h"
#include "action_buffer.h"

class FactionAICommand : public AICommand
{
public:
  /// Default constructor
	FactionAICommand();

  /// Default destructor
	~FactionAICommand();

	/// Return the read buffer for the command
	const ActionBuffer& read_buffer() const { return buffer_; };

public:
  /// Set the velocity of the ship with the given id
  void SetShipForce(uint32_t shipId, float force) override;

  /// Set the angular force of the ship with the given id
  void SetShipTorque(uint32_t shipId, float force) override;

  /// Tells the specified ship to fire
  void Fire(uint32_t shipId) override;

private:
	ActionBuffer buffer_;
};

