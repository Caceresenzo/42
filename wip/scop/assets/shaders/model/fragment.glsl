#version 330 core

in vec3 pass_Positions;
in vec2 pass_TextureCoordinates;

out vec4 FragColor;

uniform bool useTexture;
uniform sampler2D textureSampler;

void main()
{
	if (useTexture)
   		FragColor = texture(textureSampler, pass_TextureCoordinates);
   	else
    	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
