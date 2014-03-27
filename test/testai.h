#pragma once

#include "ai/i_ai.h"

class TestAI : public IAI {

public:
    TestAI();

    virtual ~TestAI();

    void Update(const AIInput& input, AICommand& command) override;
};
