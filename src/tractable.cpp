#include "tractable.h"

void Tractable::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_points"), &Tractable::get_points);
	ClassDB::bind_method(D_METHOD("set_points", "val"), &Tractable::set_points);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Points"), "set_points", "get_points");

	ClassDB::bind_method(D_METHOD("get_rigidbody"), &Tractable::get_rigidbody);
	ClassDB::bind_method(D_METHOD("set_rigidbody", "ref"), &Tractable::set_rigidbody);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "RigidBody", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_rigidbody", "get_rigidbody");

	ClassDB::bind_method(D_METHOD("add_global_force", "global_position", "direction", "force"), &Tractable::add_global_force);
	ClassDB::bind_method(D_METHOD("add_local_force", "local_position", "direction", "force"), &Tractable::add_local_force);
	
	ClassDB::bind_method(D_METHOD("get_collect_particles"), &Tractable::get_collect_particles);
	ClassDB::bind_method(D_METHOD("set_collect_particles", "ref"), &Tractable::set_collect_particles);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Collect Particles"), "set_collect_particles", "get_collect_particles");
	ClassDB::bind_method(D_METHOD("collect"), &Tractable::collect);
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &Tractable::print_type);
}

void Tractable::add_global_force(Vector3 global_position, Vector3 direction, float force)
{
	if (!is_queued_for_deletion() && rigidbody.is_valid())
	{
		positions.append(get_rigidbody()->get_basis().xform(global_position)); //make position local
		force_direction = direction;
		force_strength = force;
	}
#ifdef _DEBUG
	else
	{
		UtilityFunctions::push_warning("Error failed to add force in Tractable::add_global_force(...) on ", get_path(), " : rigidbody.is_valid() == false");
	}
#endif
}

void Tractable::add_local_force(Vector3 local_position, Vector3 direction, float force)
{
	if (!is_queued_for_deletion() && rigidbody.is_valid())
	{
		positions.append(get_rigidbody()->get_basis().xform(local_position)); //make position local
		force_direction = direction;
		force_strength = force;
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
	if (!is_queued_for_deletion())
	{
		if (collect_particles != nullptr)
		{		
			Node3D* particles = cast_to<Node3D>(collect_particles->instantiate());
			get_tree()->get_current_scene()->add_child(particles);
			particles->set_global_position(get_rigidbody()->get_global_position());
		}

		queue_free();
		return points;
	}
	else //avoid getting double points if double collected
		return 0;
}

void Tractable::_physics_process(double delta)
{
	if (!is_queued_for_deletion())
	{
		int n = 0;
		Vector3 mean_pos = Vector3(0.0f, 0.0f, 0.0f);
		for (Array::Iterator pos = positions.begin(); pos != positions.end(); ++pos) //loop over every force and get the mean position
		{
			n += 1;
			mean_pos += *pos;
		}
		if (n > 0) //if there were some force applied
		{
			mean_pos = mean_pos / n; //calculate mean pos
			if (rigidbody.is_valid())
			{
				get_rigidbody()->apply_impulse(force_strength * n * force_direction.normalized(), mean_pos); //apply force and scale based on how many forces (individual rays) applied
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

Ref<PackedScene> Tractable::get_collect_particles()
{
	return collect_particles;
}

void Tractable::set_collect_particles(Ref<PackedScene> ref)
{
	collect_particles = ref;
}

void Tractable::print_type(const Variant& p_variant) const
{
	print_line(vformat("Type: %d", p_variant.get_type()));
}
