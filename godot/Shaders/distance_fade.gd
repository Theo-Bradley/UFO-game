extends Node3D

#Sets the visibility of the attached Node3D based on distance from main_cam and fade_distance

@export var main_cam : Camera3D;
@export var fade_distance : float;

func _ready() -> void:
	main_cam = get_viewport().get_camera_3d();

#Checks distance to main_cam and if the distance is greater than fade_distance, sets visibillity to false, else sets it to true
func _process(_delta: float) -> void:
	if (main_cam != null):
		var distance = (main_cam.global_position - global_position).length();
		if (distance > fade_distance):
			self.visible = false;
		else:
			self.visible = true;
