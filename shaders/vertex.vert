#version 330 core

layout(location = 0) in vec3 v_Org;
uniform vec2 v_Pos;

void main() {
    gl_Position = vec4(
        v_Org.x + v_Pos.x,
        v_Org.y + v_Pos.y,
        v_Org.z, 1
    );
}
