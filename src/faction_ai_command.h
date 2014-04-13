#pragma once 
#include "ai_command.h"
#include "action_buffer.h"


class FactionAICommand : public AICommand
{
public:
	
	FactionAICommand();
	~FactionAICommand();

	/// Return the read buffer for the command
	const ActionBuffer& read_buffer() const { return buffer_; };

private:
	ActionBuffer buffer_;
};

