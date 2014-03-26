#pragma once

#include "float2.h"

class ShipInfo {

public:

    ShipInfo();

    virtual ~ShipInfo();

    inline int getHP() const { return hp_; }

    inline const Float2& getPosition() const { return pos_; }

    inline float getOrientation() const { return orientation_; }

private:

    int hp_;

    Float2 pos_;

    float orientation_;

};
