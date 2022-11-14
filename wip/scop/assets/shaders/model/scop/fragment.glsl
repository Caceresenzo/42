#version 330 core

in vec3 pass_Positions;
in vec2 pass_TextureCoordinates;

out vec4 out_FragColor;

uniform bool useTexture;
uniform sampler2D textureSampler;

void main()
{
	if (useTexture)
		out_FragColor = texture(textureSampler, pass_TextureCoordinates);
   	else
   	{
        float grey = (gl_PrimitiveID % 12) / 10f;
        out_FragColor = vec4(grey, grey, grey, 1.0);
   	}
}
