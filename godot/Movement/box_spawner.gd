extends Node

@export var number : int;
@export var box : Node3D;

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.

func _enter_tree() -> void:
	if (!is_instance_valid(box)):
		return;
	for	i in range(number):
		var new = box.duplicate();
		get_tree().root.add_child.call_deferred(new);
		new.position = Vector3(randf_range(-7.5, 7.5), 0.25, randf_range(-7.5, 7.5));

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
