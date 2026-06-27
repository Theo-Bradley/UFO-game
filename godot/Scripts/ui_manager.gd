extends Node

@export var sum_points : SumPoints;
@export var points_progress_bar : TextureProgressBar;
@export var points_label : Label;

var current_points : int = 0;
var total_points : int = 0;

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if (sum_points != null):
		total_points = sum_points.get("Total Points");
		if (points_progress_bar != null):
			points_progress_bar.max_value = total_points;
		else:
			push_warning("Warning! UIManager:points_progress_bar not set, failed to set max_value!");
	else:
		push_warning("Warning! UIManager:sum_points not set, failed to set total_points!");


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	if (points_progress_bar != null && total_points != null):
		points_progress_bar.value = current_points;
	if (points_label != null && total_points != null):
		points_label.text = str(current_points);
		

func points_collected(amt: int) -> void:
	current_points += amt;
