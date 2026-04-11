#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/core/gdvirtual.gen.inc"

using namespace godot;

class PlayerMove : public Node3D {
	GDCLASS(PlayerMove, Node3D)

protected:
	static void _bind_methods();
	float move_accel = 1.0;
	float move_speed = 5.0;
	float turn_speed = 0.1f; //rad*sec^-1
	Vector2 move_direction = Vector2(0.0f, 0.0f);
	ObjectID rb;

public:
	PlayerMove() = default;
	~PlayerMove() override = default;

	void print_type(const Variant &p_variant) const;
	void _process(double delta);
	void _physics_process(double delta);

	float get_move_speed();
	void set_move_speed(float val);
	float get_move_accel();
	void set_move_accel(float val);
	float get_turn_speed();
	void set_turn_speed(float val);
	RigidBody3D* get_rb();
	void set_rb(RigidBody3D* ref);
};
