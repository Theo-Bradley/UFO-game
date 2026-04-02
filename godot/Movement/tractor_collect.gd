extends Area3D

func _ready() -> void:
	connect("body_entered", Callable(self, "body_entered_area"));

func body_entered_area(body: Node3D) -> void:
	(body.get_parent() as Tractable).collect();
