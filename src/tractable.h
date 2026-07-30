#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/classes/engine.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/scene_tree.hpp"

using namespace godot;

class Tractable : public Node3D {
	GDCLASS(Tractable, Node3D)

protected:
	static void _bind_methods();
	ObjectID rigidbody;
	Array positions;
	Vector3 force_direction;
	float force_strength = 0.f;
	int points = 1;
	Ref<PackedScene> collect_particles = nullptr;

public:
	Tractable() = default;
	~Tractable() override = default;
	void _physics_process(double delta);

	void add_global_force(Vector3 global_position, Vector3 direction, float force);
	void add_local_force(Vector3 local_position, Vector3 direction, float force);
	int collect();

	RigidBody3D* get_rigidbody();
	void set_rigidbody(RigidBody3D* ref);
	int get_points();
	void set_points(int val);
	Ref<PackedScene> get_collect_particles();
	void set_collect_particles(Ref<PackedScene> ref);

	void print_type(const Variant &p_variant) const;
};
