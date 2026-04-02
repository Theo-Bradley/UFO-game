#include "Player/player_move.h"

void PlayerMove::_bind_methods()
{
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &PlayerMove::print_type);

	ClassDB::bind_method(D_METHOD("get_moveSpeed"), &PlayerMove::get_moveSpeed);
	ClassDB::bind_method(D_METHOD("set_moveSpeed", "val"), &PlayerMove::set_moveSpeed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Max Speed"), "set_moveSpeed", "get_moveSpeed");

	ClassDB::bind_method(D_METHOD("get_moveAccel"), &PlayerMove::get_moveAccel);
	ClassDB::bind_method(D_METHOD("set_moveAccel", "val"), &PlayerMove::set_moveAccel);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Moving Acceleration"), "set_moveAccel", "get_moveAccel");

	ClassDB::bind_method(D_METHOD("get_rb"), &PlayerMove::get_rb);
	ClassDB::bind_method(D_METHOD("set_rb", "ref"), &PlayerMove::set_rb);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Rigid Body", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_rb", "get_rb");
}

void PlayerMove::_process(double delta)
{
#define input Input::get_singleton()

	moveDirection = Vector2(0, 0);
	if (input->get_action_strength("Left"))
	{
		moveDirection += Vector2(-1, 0);
	}
	if (input->get_action_strength("Right"))
	{
		moveDirection += Vector2(1, 0);
	}
	if (input->get_action_strength("Forward"))
	{
		moveDirection += Vector2(0, -1);
	}
	if (input->get_action_strength("Backward"))
	{
		moveDirection += Vector2(0, 1);
	}
}

void PlayerMove::_physics_process(double delta)
{
	if (rb.is_valid())
	{
		Vector2 u = Vector2(get_rb()->get_linear_velocity().x, get_rb()->get_linear_velocity().y); //inital velocity
		//Basis basis = get_basis(); //get basis so we can make forces local
		//if (playerLook != nullptr) //if we have playerlook, we can get it's basis instead
		//	basis = playerLook->get_basis(); //this makes the forces local to the PlayerLook instead of this class
		Vector2 f = get_rb()->get_mass() * (moveDirection * Math::min(Vector2(moveAccel, moveAccel), Vector2(moveSpeed, moveSpeed) - u));
		get_rb()->apply_central_force(Vector3(f.x, 0.0f, f.y));
	}
}

float PlayerMove::get_moveSpeed()
{
	return moveSpeed;
}

void PlayerMove::set_moveSpeed(float val)
{
	moveSpeed = val;
}


float PlayerMove::get_moveAccel()
{
	return moveAccel;
}

void PlayerMove::set_moveAccel(float val)
{
	moveAccel = val;
}

RigidBody3D* PlayerMove::get_rb()
{
	return 	Object::cast_to<RigidBody3D>(ObjectDB::get_instance(rb));
}

void PlayerMove::set_rb(RigidBody3D* ref)
{
	rb = ref != nullptr ? ref->get_instance_id() : ObjectID();
}

void PlayerMove::print_type(const Variant& p_variant) const
{
	print_line(vformat("Type: %d", p_variant.get_type()));
}