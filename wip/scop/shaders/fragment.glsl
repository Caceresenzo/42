#version 330 core
out vec3 color;
in vec3 fragmentColor;
in vec3 fragmentColor2;
in vec3 fragmentColor3;

void main(){
  color = vec3(1.0, 0, 0); //fragmentColor;
}