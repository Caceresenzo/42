#version 330 core

in vec3 pass_Positions;
in vec2 pass_TextureCoordinates;

out vec4 out_FragColor;

uniform bool useTexture;
uniform sampler2D textureSampler;
uniform float transition;

void main()
{
	float greyIntensity = (gl_PrimitiveID % 12) / 10.0;
	vec4 grey = vec4(greyIntensity, greyIntensity, greyIntensity, 1.0);
	
	if (useTexture)
	{
		vec4 t = texture(textureSampler, pass_TextureCoordinates);
		vec4 a = vec4(transition, transition, transition, 1.0);
		
		out_FragColor = mix(t, grey, a);
	}
	else
		out_FragColor = grey;
}
