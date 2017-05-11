#version 150

in vec2 position;

uniform	mat4 projection;
uniform mat4 view;
uniform float height;
void main()
{
	mat4 vp = projection * view;
	vec2 computedPosition = position * 20.0;
	computedPosition = computedPosition / height;
	computedPosition.y = -(computedPosition.y - 10.0);
    gl_Position = vp * vec4(computedPosition, 0.0, 1.0);
}