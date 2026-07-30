extends Node

func finito() -> void:
	if (!is_queued_for_deletion()):
		queue_free();
