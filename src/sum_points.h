#pragma once

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/tree.hpp"
#include "godot_cpp/classes/scene_tree.hpp"

using namespace godot;

class SumPoints : public Node {
	GDCLASS(SumPoints, Node)

protected:
	static void _bind_methods();

public:
	SumPoints() = default;
	~SumPoints() override = default;
	void _ready();
	TypedArray<Node> traverse_children(Node* parent);

	void print_type(const Variant &p_variant) const;
};
