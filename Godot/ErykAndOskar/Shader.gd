extends Sprite

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	var blue_value = 1.0
	material.set_shader_param("blue", blue_value)

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
