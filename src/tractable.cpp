#include "tractable.h"

void Tractable::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_rigidbody"), &Tractable::get_rigidbody);
	ClassDB::bind_method(D_METHOD("set_rigidbody", "ref"), &Tractable::set_rigidbody);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "RigidBody", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_rigidbody", "get_rigidbody");

	ClassDB::bind_method(D_METHOD("add_global_force", "global_position", "direction"), &Tractable::add_global_force);
	ClassDB::bind_method(D_METHOD("add_local_force", "local_position"), &Tractable::add_local_force);
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Tractable::print_type);
}

RigidBody3D* Tractable::get_rigidbody()
{
	return Object::cast_to<RigidBody3D>(ObjectDB::get_instance(rigidbody));
}

void Tractable::add_global_force(Vector3 global_position, Vector3 direction)
{
	if (rigidbody.is_valid())
	{
		positions.append(get_rigidbody()->get_basis().xform(global_position)); //make position local
		force_direction = direction;
	}
#ifdef _DEBUG
	else
	{
		UtilityFunctions::push_warning("Error failed to add force in Tractable::add_global_force(...) on ", get_path(), " : rigidbody.is_valid() == false");
	}
#endif
}

void Tractable::add_local_force(Vector3 local_position)
{
	if (rigidbody.is_valid())
	{
		positions.append(get_rigidbody()->get_basis().xform(local_position)); //make position local
	}
#ifdef _DEBUG
	else
	{
		UtilityFunctions::push_warning("Error failed to add force in Tractable::add_global_force(...) on ", get_path(), " : rigidbody.is_valid() == false");
	}
#endif
}

void Tractable::_physics_process(double delta)
{
	float force = Object::cast_to<Globals>(Engine::get_singleton()->get_singleton("Globals"))->tractor_beam_force;
	int n = 0;
	Vector3 mean_pos = Vector3(0.0f, 0.0f, 0.0f);
	for (Array::Iterator pos = positions.begin(); pos != positions.end(); ++pos)
	{
		n += 1;
		mean_pos += *pos;
	}
	if (n > 0)
	{
		mean_pos = mean_pos / n;
		print_line("n: ", n, " mean_pos: ", mean_pos);
		if (rigidbody.is_valid())
		{
			get_rigidbody()->apply_impulse(force * force_direction.normalized(), mean_pos);
		}
	}
	positions.clear();
}

void Tractable::set_rigidbody(RigidBody3D* ref)
{
	rigidbody = ref != nullptr ? ref->get_instance_id() : ObjectID();
}

void Tractable::print_type(const Variant& p_variant) const
{
	print_line(vformat("Type: %d", p_variant.get_type()));
}
