#pragma once

#include <vector>
#include "thruster_description.h"

class ShipDescription
{

public:

    ShipDescription();

    virtual ~ShipDescription();

    const std::vector<ThrusterDescription>& thrusters() const { return thrusters_; }

private:

    std::vector<ThrusterDescription> thrusters_;

};
