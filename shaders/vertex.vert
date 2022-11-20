#version 330 core

/* precision mediump float; */

layout(location = 0) in vec3 vertexPosition_modelspace;
attribute vec3 CLR;
varying vec3 vColor;
uniform mat4 MVP;

void main() {
    vColor = CLR;
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
}
