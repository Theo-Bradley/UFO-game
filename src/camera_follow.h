#pragma once

#include "godot_cpp/classes/camera3d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;

class CameraFollow : public Camera3D {
	GDCLASS(CameraFollow, Camera3D)

protected:
	static void _bind_methods();
	ObjectID target;
	int delay_frames = 1;
	Vector3* delay_array = nullptr;
	int array_index = 0;
	void init_delay_array();
	Vector3 offset;
	Vector3 tilt_offset;

public:
	CameraFollow() = default;
	~CameraFollow() override = default;
	void _ready();
	void _physics_process(double delta);

	void set_target(Node3D* ref);
	Node3D* get_target();
	void set_delay_frames(int val);
	int get_delay_frames();
	void set_offset(Vector3 val);
	Vector3 get_offset();
	void set_tilt_offset(Vector3 val);
	Vector3 get_tilt_offset();
	void print_type(const Variant &p_variant) const;
};
