#version 330 core

in vec2 pass_UV;

out vec4 out_fragColor;

uniform sampler2D textureSampler;

void
main()
{
	out_fragColor = texture(textureSampler, pass_UV);
	if (out_fragColor.rgb == vec3(0, 0, 0))
		out_fragColor.a = 0;
}
