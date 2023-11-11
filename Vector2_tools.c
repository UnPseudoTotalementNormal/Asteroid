#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vector2_tools.h"

sfVector2f Vector2_normalized(sfVector2f vector) {
	float v_len = Vector2_length(vector);
	return (sfVector2f) { vector.x / v_len, vector.y / v_len };
}

float Vector2_length(sfVector2f vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}
