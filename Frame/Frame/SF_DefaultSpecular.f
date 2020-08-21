#version 460

in vec3 positionW;
in vec3 normalW;
in vec2 texCoordF;

out vec4 FragColor;

uniform vec3 eyePos;
uniform vec3 specular;
uniform float shininess;

uniform sampler2D albedoMap;
uniform vec3 baseColor;

struct DirLight
{
	vec3 position;
	vec3 color;
	vec3 dir;
};

struct PointLight
{
	vec3 position;
	vec3 color;
	float radius;
	float attenuation;
};

#define DIR_LIGHT_NUM 1
uniform DirLight dirLights[DIR_LIGHT_NUM];
#define POINT_LIGHT_NUM 1
uniform PointLight pointLights[POINT_LIGHT_NUM];

vec3 CalDirLight(DirLight dirLight, vec3 normal, vec3 viewDir)
{
	// 环境光（镜面反射只能在特定角度才能看见）
	vec3 texColor = vec3(texture(albedoMap, texCoordF));
	vec3 ambient = dirLight.color * baseColor * texColor;
	vec3 lightDir = - dirLight.dir;

	// 镜面反射
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specularRes = dirLight.color * (spec * specular) * texColor; 

	vec3 result = specularRes + ambient;
	return result;
}

vec3 DefaultSpecular(vec3 posW, vec3 normalW)
{
	vec3 viewDir = normalize(eyePos - posW);
	vec3 normal = normalize(normalW);
	vec3 color = vec3(0);

	for(int i = 0;i < DIR_LIGHT_NUM; i++)
		color += CalDirLight(dirLights[i], normal, viewDir);

	return color;
}

void main()
{
	FragColor = vec4(DefaultSpecular(positionW, normalW), 1.0);
}