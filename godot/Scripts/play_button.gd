extends Node

@export var next_scene: PackedScene;

# Called when the node enters the scene tree for the first time.
func button_pressed() -> void:
	if (next_scene):
		get_tree().change_scene_to_packed(next_scene);
