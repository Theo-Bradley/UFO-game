#pragma once
#include "godot_cpp/classes/Node.hpp"

using namespace godot;

class Globals : public Node
{
    GDCLASS(Globals, Node);

protected:
    static void _bind_methods() {};

public:
    float tractor_beam_force = 0.2f;
};
