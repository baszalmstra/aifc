#pragma once

class AIInput;
class AICommand;

class IAI
{

public:

    IAI();

    virtual ~IAI();

    // Update hook called every frame
    void update(const AIInput& input, AICommand& command);

};
