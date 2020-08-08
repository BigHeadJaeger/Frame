#version 460

layout(location=0) in vec3 positionL;
layout(location=1) in vec3 normalL;

out vec3 posW;					// 光照计算需要物体的世界坐标
out vec3 normalW;				// 顶点法向量的世界坐标
out vec4 vertexColor;			// 顶点的颜色

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light
{
	vec3 position;
	vec3 color;
};

uniform mat4 world;
uniform mat4 worldViewProj;
uniform mat4 worldInvTranspose;

uniform bool isVertexLight;
uniform vec3 eyePos;
uniform Material material;
uniform Light light;



// 计算需要的都是世界坐标下的量
vec3 PhongLight(vec3 posW, vec3 normalW)
{
	// 环境光
	vec3 ambient = light.color * material.ambient;

	// 漫反射
	vec3 normal = normalize(normalW);
	vec3 lightDir = normalize(light.position - posW);
	float diffcoeff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.color * (diffcoeff * material.diffuse);

	// 镜面反射
	vec3 viewDir = normalize(eyePos - posW);
	vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.color * (spec * material.specular); 

	vec3 result = ambient + diffuse + specular;

	return result;
}

void main()
{
	posW=(world*vec4(positionL,1.0)).xyz;
	normalW=(worldInvTranspose*vec4(normalL,1.0)).xyz;
	gl_Position = worldViewProj * vec4(positionL, 1.0);



	if(isVertexLight)
		vertexColor = vec4(PhongLight(posW, normalW), 1.0);
	else
		vertexColor = vec4(1.0, 0, 1.0, 1.0);
}

