#pragma once

#include "ai/i_ai.h"

class TestAI : public IAI {

public:

    TestAI();

    virtual ~TestAI();

    void update(const AIInput& input, AICommand& command);

};
