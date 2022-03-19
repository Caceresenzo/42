#version 330 core

in vec2 pass_UV;

out vec4 FragColour;

uniform sampler2D textureSampler;

void
main()
{
	FragColour = texture(textureSampler, pass_UV);
}
