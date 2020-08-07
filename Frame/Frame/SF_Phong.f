#version 460

in vec3 posW;
in vec3 normalW;
in vec4 vertexColor;

out vec4 FragColor;

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
}

uniform bool isVertexLight;
uniform vec3 eyePos;
uniform Material material;
uniform Light light;

// ������Ҫ�Ķ������������µ���
vec3 PhongLight(posW, normalW)
{
	// ������
	vec3 ambient = light.color * material.ambient;

	// ������
	vec3 normal = normalize(normalW);
	vec3 lightDir = normalize(light.position - posW);
	float diffcoeff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.color * (diffcoeff * material.diffuse);

	// ���淴��
	vec3 viewDir = normalize(eyePos - posW);
	vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.color * (spec * material.specular); 

	vec3 result = ambient + diffuse + specular;

	return result;
}

void main()
{
FragColor = vertexColor;
	/*if(isVertexLight)
		FragColor = vertexColor;
	else
		FragColor = vec4(PhongLight(posW, normalW), 1.0);*/
}	