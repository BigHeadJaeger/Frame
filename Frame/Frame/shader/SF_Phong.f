#version 460

in vec3 positionW;
in vec3 normalW;

out vec4 FragColor;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

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

uniform vec3 eyePos;
uniform Material material;
#define DIR_LIGHT_NUM 10
uniform DirLight dirLights[DIR_LIGHT_NUM];
#define POINT_LIGHT_NUM 10
uniform PointLight pointLights[POINT_LIGHT_NUM];

vec4 CalDirLight(DirLight dirLight, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = - dirLight.dir;

	// 环境光
	vec3 ambient = dirLight.color * material.ambient;

	// 漫反射
	float diffcoeff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = dirLight.color * (diffcoeff * material.diffuse);

	// 镜面反射
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = dirLight.color * (spec * material.specular); 

	vec4 result = vec4((ambient + diffuse + specular), 1.0);
	return result;
}

vec4 CalPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 posW)
{
	vec3 ambient = light.color * material.ambient;
	vec3 lightDir = normalize(light.position - posW);
	// 镜面反射
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.color * (spec * material.specular); 

	// 漫反射
	float diffcoeff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.color * (diffcoeff * material.diffuse);
	
	// 衰减
	float distance = length(light.position - posW);
	float attenuation = 1.0 / (light.constant + light.linear * distance + (distance * distance) * light.quadratic);
	vec4 result = vec4((specular + ambient + diffuse) * attenuation, 1.0);
	return result;
}

// 计算需要的都是世界坐标下的量
vec4 PhongLight(vec3 posW, vec3 normalW)
{
	vec3 normal = normalize(normalW);
	vec3 viewDir = normalize(eyePos - posW);
	vec4 color = vec4(0);

	for(int i = 0; i < DIR_LIGHT_NUM; i++)
	{
		if(dirLights[i].isAble)
			color += CalDirLight(dirLights[i], normal, viewDir);
	}

	for(int i = 0; i < POINT_LIGHT_NUM; i++)
	{
		if(pointLights[i].isAble)
			color += CalPointLight(pointLights[i], normal, viewDir, positionW);
	}
		

	return color;
}

void main()
{
	//FragColor = vec4(1,0,0,1);
	FragColor = PhongLight(positionW, normalW);
}	