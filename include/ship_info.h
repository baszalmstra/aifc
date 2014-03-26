#pragma once

#include "float2.h"
#include "ship_description.h"

#include <cstdint>

typedef uint32_t ShipId;

class ShipInfo {

public:

    ShipInfo();

    virtual ~ShipInfo();

    ShipId id() const { return id_; }

    int hp() const { return hp_; }

    const Float2& position() const { return pos_; }

    float orientation() const { return orientation_; }

    const ShipDescription& description() const { return description_; }

private:

    ShipId id_;

    int hp_;

    Float2 pos_;

    float orientation_;

    ShipDescription description_;

};
