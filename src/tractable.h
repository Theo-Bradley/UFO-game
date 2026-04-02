#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/classes/engine.hpp"
#include "globals.h"

using namespace godot;

class Tractable : public Node3D {
	GDCLASS(Tractable, Node3D)

protected:
	static void _bind_methods();
	ObjectID rigidbody;
	Array positions;
	Vector3 force_direction;
	int points = 1;

public:
	Tractable() = default;
	~Tractable() override = default;
	void _physics_process(double delta);

	void add_global_force(Vector3 global_position, Vector3 direction);
	void add_local_force(Vector3 local_position, Vector3 direction);
	int collect();

	RigidBody3D* get_rigidbody();
	void set_rigidbody(RigidBody3D* ref);
	int get_points();
	void set_points(int val);

	void print_type(const Variant &p_variant) const;
};
