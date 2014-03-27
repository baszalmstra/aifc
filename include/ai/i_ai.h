#pragma once

class AIInput;
class AICommand;

class IAI
{
public:
    virtual ~IAI() {};

    // Update hook called every frame
    virtual void Update(const AIInput& input, AICommand& command) = 0;
};
