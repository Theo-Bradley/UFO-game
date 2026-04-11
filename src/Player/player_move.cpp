#include "Player/player_move.h"

void PlayerMove::_bind_methods()
{
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &PlayerMove::print_type);

	ClassDB::bind_method(D_METHOD("get_move_speed"), &PlayerMove::get_move_speed);
	ClassDB::bind_method(D_METHOD("set_move_speed", "val"), &PlayerMove::set_move_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Max Speed"), "set_move_speed", "get_move_speed");

	ClassDB::bind_method(D_METHOD("get_move_accel"), &PlayerMove::get_move_accel);
	ClassDB::bind_method(D_METHOD("set_move_accel", "val"), &PlayerMove::set_move_accel);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Moving Acceleration"), "set_move_accel", "get_move_accel");

	ClassDB::bind_method(D_METHOD("get_turn_speed"), &PlayerMove::get_turn_speed);
	ClassDB::bind_method(D_METHOD("set_turn_speed", "val"), &PlayerMove::set_turn_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Turning Speed"), "set_turn_speed", "get_turn_speed");

	ClassDB::bind_method(D_METHOD("get_rb"), &PlayerMove::get_rb);
	ClassDB::bind_method(D_METHOD("set_rb", "ref"), &PlayerMove::set_rb);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Rigid Body", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_rb", "get_rb");
}

void PlayerMove::_process(double delta)
{
#define input Input::get_singleton()

	move_direction = Vector2(0, 0);
	if (input->get_action_strength("Left"))
	{
		move_direction += Vector2(-1, 0);
	}
	if (input->get_action_strength("Right"))
	{
		move_direction += Vector2(1, 0);
	}
	if (input->get_action_strength("Forward"))
	{
		move_direction += Vector2(0, -1);
	}
	if (input->get_action_strength("Backward"))
	{
		move_direction += Vector2(0, 1);
	}
}

void PlayerMove::_physics_process(double delta)
{
	if (rb.is_valid())
	{
		RigidBody3D* ref = get_rb();
		Vector2 u = Vector2(ref->get_linear_velocity().x, ref->get_linear_velocity().y); //inital velocity
		Vector2 f = ref->get_mass() * (move_direction * Math::min(Vector2(move_accel, move_accel), Vector2(move_speed, move_speed) - u));
		if (f.length() > 0)
		{
			Vector3 forward = ref->get_basis().rows[2].normalized();
			float angle = forward.signed_angle_to(Vector3(f.normalized().x, 0.0f, -f.normalized().y), Vector3(0.f, -1.f, 0.f));
			if (angle != 0)
				get_rb()->rotate_y(Math::min(turn_speed * (float)delta, Math::abs(angle)) * Math::abs(angle) / angle);
		}
		ref->apply_central_force(Vector3(f.x, 0.0f, f.y));
	}
}

float PlayerMove::get_move_speed()
{
	return move_speed;
}

void PlayerMove::set_move_speed(float val)
{
	move_speed = val;
}


float PlayerMove::get_move_accel()
{
	return move_accel;
}

void PlayerMove::set_move_accel(float val)
{
	move_accel = val;
}

float PlayerMove::get_turn_speed()
{
	return turn_speed;
}

void PlayerMove::set_turn_speed(float val)
{
	turn_speed = val;
}

RigidBody3D* PlayerMove::get_rb()
{
	return Object::cast_to<RigidBody3D>(ObjectDB::get_instance(rb));
}

void PlayerMove::set_rb(RigidBody3D* ref)
{
	rb = ref != nullptr ? ref->get_instance_id() : ObjectID();
}

void PlayerMove::print_type(const Variant& p_variant) const
{
	print_line(vformat("Type: %d", p_variant.get_type()));
}