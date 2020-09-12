#version 460

in vec2 texcoordF;

out vec4 FragColor;

uniform sampler2D screenTexture;
uniform int screenType;

uniform mat3 kernel;
uniform float texOffset;

vec4 InverseColor();
vec4 Gray();
vec4 Kernel(mat3 ker, float offset);

void main()
{
	vec4 resColor = vec4(0);
	if(screenType == 0)
		resColor = texture(screenTexture, texcoordF);
	else if(screenType == 1)
		resColor = InverseColor();
	else if(screenType == 2)
		resColor = Gray();
	else if(screenType == 3)
		resColor = Kernel(kernel, texOffset);

	FragColor = resColor;
}

vec4 InverseColor()
{
	return vec4(vec3(1 - texture(screenTexture, texcoordF)), 1.0);
}

vec4 Gray()
{
	vec3 texColor = texture(screenTexture, texcoordF).xyz;
	float average = 0.2 * texColor.r + 0.7 * texColor.g + 0.1 * texColor.b;
	return vec4(average, average, average, 1.0);
}

vec4 Kernel(mat3 ker, float offset)
{
	vec2 offsets[9] = vec2[](
		vec2(-offset,  offset), // 左上
		vec2( 0.0f,    offset), // 正上
		vec2( offset,  offset), // 右上
		vec2(-offset,  0.0f),   // 左
		vec2( 0.0f,    0.0f),   // 中
		vec2( offset,  0.0f),   // 右
		vec2(-offset, -offset), // 左下
		vec2( 0.0f,   -offset), // 正下
		vec2( offset, -offset)  // 右下
    );

	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++)
	{
		sampleTex[i] = texture(screenTexture, texcoordF.st + offsets[i]).rgb;
	}

	vec3 res = vec3(0);

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			res += sampleTex[i * 3 + j] * ker[i][j];
		}
	}


	return vec4(res, 1.0);
	//return vec4(0.5);
}