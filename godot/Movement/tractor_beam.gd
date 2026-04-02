extends Node3D

var collected_points : int = 0;
var ray_points : Array;
var cone_points : Array;
@export var numRays : int;
@export var ray_height : float = 3.0;
@export var ImmediateGeo : ImmediateMesh;
signal collect;

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	for i in range(numRays):
		var angle = (2.0 * PI)/numRays * i;
		const dist = 1.0;
		var increment = (2.0 * PI)/numRays;
		ray_points.append(Vector2(dist * cos(angle), dist * sin (angle)));
		cone_points.append(Vector2(dist * cos(angle - increment / 2.0), dist * sin(angle - increment / 2.0)));
		cone_points.append(Vector2(dist * cos(angle + increment / 2.0), dist * sin(angle + increment / 2.0)));
	for i in range(numRays):
		ImmediateGeo.surface_begin(Mesh.PRIMITIVE_TRIANGLES);
		ImmediateGeo.surface_add_vertex(global_position);
		ImmediateGeo.surface_add_vertex(global_position + Vector3(cone_points[2 * i].x, -ray_height, cone_points[2 * i].y));
		ImmediateGeo.surface_add_vertex(global_position + Vector3(cone_points[2 * i + 1].x, -ray_height, cone_points[2 * i + 1].y));
		ImmediateGeo.surface_end();
	pass # Replace with function body.dx


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	var space_state = get_world_3d().direct_space_state;
	for offset in ray_points:
		var query = PhysicsRayQueryParameters3D.create(global_position, global_position + Vector3(offset.x, -ray_height, offset.y), 0x4);
		var result = space_state.intersect_ray(query) as Dictionary;
		if !result.is_empty():
			var rb = result["collider"] as RigidBody3D;
			if (!rb.get_parent().is_queued_for_deletion()):
				(rb.get_parent() as Tractable).add_global_force(result["position"], global_position - result["position"]);
	pass
