#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 color;

out vec3 col;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(aPos.x, aPos.y, 0.0, 1.0);
    gl_PointSize = 10.0;
    col = color;
}