#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

out vec3 fragmentColor;

void main(){
  //gl_Position.xyz = vertexPosition_modelspace;
  //gl_Position.w = 1.0;
  
  gl_Position = p*v*m * vec4( vertexPosition_modelspace, 1.0 );
  
    fragmentColor = vertexColor;
}