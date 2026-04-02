#include "tractable.h"

void Tractable::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_points"), &Tractable::get_points);
	ClassDB::bind_method(D_METHOD("set_points", "val"), &Tractable::set_points);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Points"), "set_points", "get_points");

	ClassDB::bind_method(D_METHOD("get_rigidbody"), &Tractable::get_rigidbody);
	ClassDB::bind_method(D_METHOD("set_rigidbody", "ref"), &Tractable::set_rigidbody);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "RigidBody", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_rigidbody", "get_rigidbody");

	ClassDB::bind_method(D_METHOD("add_global_force", "global_position", "direction"), &Tractable::add_global_force);
	ClassDB::bind_method(D_METHOD("add_local_force", "local_position"), &Tractable::add_local_force);
	ClassDB::bind_method(D_METHOD("collect"), &Tractable::collect);
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Tractable::print_type);
}

void Tractable::add_global_force(Vector3 global_position, Vector3 direction)
{
	if (!is_queued_for_deletion() && rigidbody.is_valid())
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

void Tractable::add_local_force(Vector3 local_position, Vector3 direction)
{
	if (!is_queued_for_deletion() && rigidbody.is_valid())
	{
		positions.append(get_rigidbody()->get_basis().xform(local_position)); //make position local
		force_direction = direction;
	}
#ifdef _DEBUG
	else
	{
		UtilityFunctions::push_warning("Error failed to add force in Tractable::add_global_force(...) on ", get_path(), " : rigidbody.is_valid() == false");
	}
#endif
}

int Tractable::collect()
{
	queue_free();
	print_line(points);
	return points;
}

void Tractable::_physics_process(double delta)
{
	if (!is_queued_for_deletion())
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
}

void Tractable::set_rigidbody(RigidBody3D* ref)
{
	rigidbody = ref != nullptr ? ref->get_instance_id() : ObjectID();
}

RigidBody3D* Tractable::get_rigidbody()
{
	return Object::cast_to<RigidBody3D>(ObjectDB::get_instance(rigidbody));
}

void Tractable::set_points(int val)
{
	points = val;
}

int Tractable::get_points()
{
	return points;
}

void Tractable::print_type(const Variant& p_variant) const
{
	print_line(vformat("Type: %d", p_variant.get_type()));
}
