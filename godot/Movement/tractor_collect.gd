extends Area3D

var UIManager : Node;

func _ready() -> void:
	UIManager = get_node(^"/root").get_child(0).get_node("UIManager");
	connect("body_entered", Callable(self, "body_entered_area"));

func body_entered_area(body: Node3D) -> void:
	var points = (body.get_parent() as Tractable).collect();
	UIManager.call("points_collected", points);
