#pragma once

class Float2 {

public:

    Float2();

    virtual ~Float2();

    union {
        struct { float x, y; };
        float m[2];
    };

};
