#pragma once

#include <vector>
#include <cstdint>

typedef uint32_t ShipId;

class AICommand {

public:

    AICommand();

    virtual ~AICommand();

    void set_thruster(ShipId ship_id, uint32_t thruster_id, float level);

private:

    std::vector<float> thruster_levels_;

};
