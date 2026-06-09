#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 projection;
uniform int spriteFrame;

out vec2 texCoord;

void main()
{
	gl_Position = projection * vec4(aPosition, 0.0, 1.0);

	const int frameWidthPixels = 64;
	const float frameOffset = 1.0 / frameWidthPixels;

	texCoord = aTexCoord + vec2(frameOffset * spriteFrame, 0.0);
}