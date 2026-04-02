extends Node3D

var points : Array;
@export var numRays : int;

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	for i in range(numRays):
		var angle = (2.0 * PI)/numRays * i;
		const dist = 1.0;
		points.append(Vector2(dist * cos(angle), dist * sin (angle)));
		pass
	pass # Replace with function body.dx


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	var space_state = get_world_3d().direct_space_state;
	for offset in points:
		var query = PhysicsRayQueryParameters3D.create(global_position, global_position + Vector3(offset.x, -3.0, offset.y), 0x4);
		var result = space_state.intersect_ray(query) as Dictionary;
		if !result.is_empty():
			var rb = result["collider"] as RigidBody3D;
			var pos = rb.get_basis() * result["position"];
			if rb != null:
				rb.apply_force(Vector3(0.0, 9.0, 0.0), pos);
	pass
