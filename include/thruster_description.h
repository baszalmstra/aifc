#pragma once

#include "float2.h"

class ThrusterDescription
{

public:

    ThrusterDescription(const Float2& position, float orientation, float max_level)
        : position_(position), orientation_(orientation), max_level_(max_level_)
    {}

    virtual ~ThrusterDescription();

    const Float2& position() const { return position_; }

    float orientation() const { return orientation_; }

    float max_level() const { return max_level_; }

protected:

    Float2 position_;

    float orientation_;

    float max_level_;

};
