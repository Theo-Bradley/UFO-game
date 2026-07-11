#include "sum_points.h"

void SumPoints::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_total_points", "amt"), &SumPoints::set_total_points);
	ClassDB::bind_method(D_METHOD("get_total_points"), &SumPoints::get_total_points);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Total Points"), "set_total_points", "get_total_points");

	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &SumPoints::print_type);
}

void SumPoints::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}

void SumPoints::_ready()
{
	TypedArray<Node> nodes = traverse_children(get_tree()->get_current_scene()); //get all nodes in scene
	int points = 0;
	for (Array::Iterator node = nodes.begin(); node != nodes.end(); ++node) //loop over every node
	{
		Object* current = (*node).get_validated_object();
		if (current != nullptr && current->get_class() == "Tractable") //if it is a valid object and of type Tractable
		{
			points += (int)(current->get("Points")); //add points to total
		}
	}
	set_total_points(points);
}

TypedArray<Node> SumPoints::traverse_children(Node* parent) //depth wise recursive Node search
{
	TypedArray<Node> result;
	if (parent->get_child_count() == 0) //if no children
	{
		return result; //early exit
	}
	else
	{
		TypedArray<Node> children = parent->get_children(); //get all children of this node
		for (Array::Iterator child = children.begin(); child != children.end(); ++child) //loop over every child of parent
		{
			Node* current = Object::cast_to<Node>((*child).get_validated_object()); //cast child to Node pointer
			if (current != nullptr) //if cast was sucessful
			{
				result.append(current); //append current child node to result array
				result.append_array(traverse_children(current)); //recurse over children
			}
		}
		return result; //after looping over all children, close this recursive branch
	}
}

void SumPoints::set_total_points(int amt)
{
	total_points = amt;
}

int SumPoints::get_total_points()
{
	return total_points;
}