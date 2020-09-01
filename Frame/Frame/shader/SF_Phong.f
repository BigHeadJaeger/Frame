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

uniform vec3 eyePos;
uniform Material material;
#define DIR_LIGHT_NUM 1
uniform DirLight dirLights[DIR_LIGHT_NUM];
#define POINT_LIGHT_NUM 1
uniform PointLight pointLights[POINT_LIGHT_NUM];

vec3 CalDirLight(DirLight dirLight, vec3 normal, vec3 viewDir)
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

	vec3 result = ambient + diffuse + specular;
	return result;
}

// 计算需要的都是世界坐标下的量
vec3 PhongLight(vec3 posW, vec3 normalW)
{
	vec3 normal = normalize(normalW);
	vec3 viewDir = normalize(eyePos - posW);
	vec3 color = vec3(0);

	for(int i = 0; i < DIR_LIGHT_NUM; i++)
		color += CalDirLight(dirLights[i], normal, viewDir);

	//color = vec3(1,0,0);
	return color;
}

void main()
{
	//FragColor = vec4(1,0,0,1);
	FragColor = vec4(PhongLight(positionW, normalW), 1.0);
}	