#version 460

in vec3 positionW;
in vec3 normalW;
in vec2 texcoordF;

out vec4 FragColor;

// 反射还是折射
uniform int mode;

uniform float ratio;
uniform vec3 eyePos;

uniform bool isSkyBox;
uniform samplerCube skyBoxMap;

uniform sampler2D baseColorMap;
uniform sampler2D AOMap;
uniform bool isAO;

vec4 GetSkyBoxColor(vec3 reflectV)
{
	vec4 res = vec4(texture(skyBoxMap, reflectV).rgb, 1.0);
	return res;
}

// 获取世界坐标下的视点到顶点的向量
vec3 WorldViewObjDir()
{
	vec3 res = normalize(positionW - eyePos);
	return res;
}

void main()
{
	vec4 res;

	float reflectRate = 0.0;
	vec4 baseColor = vec4(texture(baseColorMap, texcoordF).rgb, 1.0);

	// AO贴图的第一位存的是反射率
	if(isAO)
		reflectRate = texture(AOMap, texcoordF).r;
	else
		reflectRate = 1.0;
	
	vec3 sampleV;
	if(mode == 0)
	{
		sampleV = reflect(WorldViewObjDir(), normalize(normalW));
		vec4 skyBoxRes = GetSkyBoxColor(sampleV);
		res = skyBoxRes * reflectRate + baseColor * (1 - reflectRate);
	}
	else
	{
		sampleV = refract(WorldViewObjDir(), normalize(normalW), ratio);
		vec4 skyBoxRes = GetSkyBoxColor(sampleV);
		res = skyBoxRes;
	}

	FragColor = res;
}