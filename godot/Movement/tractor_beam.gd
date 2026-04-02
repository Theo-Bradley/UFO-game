extends Node3D

var collected_points : int = 0;
var ray_points : Array;
@export var numRays : int;
@export var ImmediateGeo : ImmediateMesh;
signal collect;

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	for i in range(numRays):
		var angle = (2.0 * PI)/numRays * i;
		const dist = 1.0;
		ray_points.append(Vector2(dist * cos(angle), dist * sin (angle)));
		pass
	pass # Replace with function body.dx


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	var space_state = get_world_3d().direct_space_state;
	ImmediateGeo.clear_surfaces();
	for offset in ray_points:
		var query = PhysicsRayQueryParameters3D.create(global_position, global_position + Vector3(offset.x, -3.0, offset.y), 0x4);
		var result = space_state.intersect_ray(query) as Dictionary;
		if !result.is_empty():
			var rb = result["collider"] as RigidBody3D;
			if (!rb.get_parent().is_queued_for_deletion()):
				(rb.get_parent() as Tractable).add_global_force(result["position"], global_position - result["position"]);
				ImmediateGeo.surface_begin(Mesh.PRIMITIVE_LINES);
				ImmediateGeo.surface_add_vertex(global_position);
				ImmediateGeo.surface_add_vertex(result["position"]);
				ImmediateGeo.surface_end();
	pass
