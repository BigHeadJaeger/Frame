#version 460

in vec3 positionW;
in vec3 normalW;
in vec2 texcoordF;

out vec4 FragColor;

uniform vec3 eyePos;
uniform vec3 specular;
uniform float shininess;

uniform sampler2D albedoMap;
uniform vec4 baseColor;

uniform bool isSkyBox;
uniform samplerCube skyBoxMap;

struct DirLight
{
	bool isAble;
	vec3 position;
	vec3 color;
	vec3 dir;
};

struct PointLight
{
	bool isAble;
	vec3 position;
	vec3 color;
	float radius;
	float constant;
	float linear;
	float quadratic;
};

#define DIR_LIGHT_NUM 10
uniform DirLight dirLights[DIR_LIGHT_NUM];
#define POINT_LIGHT_NUM 10
uniform PointLight pointLights[POINT_LIGHT_NUM];

vec4 GetSkyBoxColor(vec3 reflectV)
{
	vec4 res = vec4(texture(skyBoxMap, reflectV).rgb, 1.0);
	return res;
	//return vec4(1, 0, 0, 1);
}

// 获取世界坐标下的视点到顶点的向量
vec3 WorldViewObjDir()
{
	vec3 res = normalize(positionW - eyePos);
	return res;
}

vec4 CalDirLight(DirLight dirLight, vec3 normal, vec3 viewDir)
{
	// 环境光（镜面反射只能在特定角度才能看见）
	vec4 texColor = texture(albedoMap, texcoordF);
	vec4 ambient = vec4(dirLight.color, 1.0) * baseColor * texColor;
	vec3 lightDir = - dirLight.dir;

	// 镜面反射
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec4 specularRes = vec4(dirLight.color * (spec * specular), 1.0) * texColor; 

	vec4 result = specularRes + ambient;
	return result;
}

vec4 CalPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 posW)
{
	// 环境光（镜面反射只能在特定角度才能看见）
	vec4 texColor = texture(albedoMap, texcoordF);
	vec4 ambient = vec4(light.color, 1.0) * baseColor * texColor;
	vec3 lightDir = normalize(light.position - posW);
	// 镜面反射
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec4 specularRes = vec4(light.color * (spec * specular), 1.0) * texColor;
	
	// 衰减
	float distance = length(light.position - posW);
	float attenuation = 1.0 / (light.constant + light.linear * distance + (distance * distance) * light.quadratic);
	vec4 result = (specularRes + ambient) * attenuation;
	return result;
}

vec4 DefaultSpecular(vec3 posW, vec3 normalW)
{
	vec3 viewDir = normalize(eyePos - posW);
	vec3 normal = normalize(normalW);
	vec4 color = vec4(0);

	for(int i = 0;i < DIR_LIGHT_NUM; i++)
	{
		if(dirLights[i].isAble)
			color += CalDirLight(dirLights[i], normal, viewDir);
	}

	for(int i = 0; i < POINT_LIGHT_NUM; i++)
	{
		if(pointLights[i].isAble)
		{
			color += CalPointLight(pointLights[i], normal, viewDir, posW);
		}
	}

	return color;
}

void main()
{
	vec4 res = DefaultSpecular(positionW, normalW);
	/*if(res.a < 0.05)
		discard;*/
	/*if(isSkyBox)
	{
		vec3 viewObjRe = reflect(WorldViewObjDir(), normalize(normalW));
		vec4 skyBoxRes = GetSkyBoxColor(viewObjRe);
		res *= skyBoxRes;
	}*/
	 FragColor = res;
}