#include "camera_follow.h"

void CameraFollow::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &CameraFollow::print_type);
	ClassDB::bind_method(D_METHOD("get_target"), &CameraFollow::get_target);
	ClassDB::bind_method(D_METHOD("set_target", "ref"), &CameraFollow::set_target);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Target", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_target", "get_target");

	ClassDB::bind_method(D_METHOD("get_delay_frames"), &CameraFollow::get_delay_frames);
	ClassDB::bind_method(D_METHOD("set_delay_frames", "val"), &CameraFollow::set_delay_frames);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Delay Frames Count"), "set_delay_frames", "get_delay_frames");

	ClassDB::bind_method(D_METHOD("get_offset"), &CameraFollow::get_offset);
	ClassDB::bind_method(D_METHOD("set_offset", "val"), &CameraFollow::set_offset);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "Camera Offset"), "set_offset", "get_offset");
}

void CameraFollow::_ready()
{
	init_delay_array();
}

void CameraFollow::_physics_process(double delta)
{
	if (delay_array != nullptr && target.is_valid())
	{
		delay_array[(array_index + delay_frames - 1) % delay_frames] = get_target()->get_global_position();
		set_global_position(delay_array[array_index] + offset);
		look_at(delay_array[array_index]);
		array_index = ++array_index % delay_frames;
	}
}

void CameraFollow::init_delay_array()
{
	if (delay_array != nullptr)
	{
		memdelete(delay_array);
		delay_array = nullptr;
	}

	delay_array = memnew_arr(Vector3, delay_frames);
	array_index = 0;

	if (target.is_valid())
	{
		Vector3 pos = get_target()->get_global_position();
		for (int i = 0; i < delay_frames; i++)
		{
			delay_array[i] = pos;
		}
	}
	else
	{
		UtilityFunctions::push_warning("Follow Camera failed to populate delay_array! target.is_valid() == false");
	}
}

void CameraFollow::set_target(Node3D* ref)
{
	target = ref != nullptr ? ref->get_instance_id() : ObjectID();
}

Node3D* CameraFollow::get_target()
{
	return Object::cast_to<Node3D>(ObjectDB::get_instance(target));
}

void CameraFollow::set_delay_frames(int val)
{
	if (delay_frames > 0)
	{
		delay_frames = val;	
		init_delay_array();
	}
#ifdef _DEBUG
	else
	{
		UtilityFunctions::push_warning("Follow Camera failed to set delay_frames, value must be greater than zero! Did not init_delay_array()!");
	}
#endif
}

int CameraFollow::get_delay_frames()
{
	return delay_frames;
}

void CameraFollow::set_offset(Vector3 val)
{
	offset = val;
}

Vector3 CameraFollow::get_offset()
{
	return offset;
}

void CameraFollow::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}
