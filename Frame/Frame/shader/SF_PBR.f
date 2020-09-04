#version 460

//������õ�ֱ�ӹ��գ������ǻ������գ����ÿһ����������ֻ���Ǵ��ڵĹ�Դ���������ܷ��ն���Ӽ��ɣ��������ȫ�ֹ��գ�����Ҫ����ּ���

in vec3 posW;
in vec3 normalW;
in vec2 TexCoord;
//in vec4 shadowCoord;

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

//��Ӱ��ͼ���������
uniform sampler2DShadow shadowTex;
uniform bool useShadowTex;

//����PBR����
//��ǰ���Ե�ֵ�Ƿ�������������
uniform sampler2D albedoMap;
uniform bool isTextureBase;
uniform vec3 baseColor;

uniform sampler2D normalMap;
uniform bool isTextureNormal;

uniform sampler2D metallicMap;
uniform bool isTextureMetallic;
uniform float numMetallic;

uniform sampler2D roughnessMap;
uniform bool isTextureRoughness;
uniform float numRoughness;

uniform sampler2D aoMap;
uniform bool isTextureAO;

uniform bool isSkyBox;
uniform samplerCube skyBoxMap;

uniform int renderMode;

//������Ϣ
#define DIR_LIGHT_NUM 10
uniform DirLight dirLights[DIR_LIGHT_NUM];
#define POINT_LIGHT_NUM 10
uniform PointLight pointLights[POINT_LIGHT_NUM];

//�۾�λ��
uniform vec3 eyePos;

const float PI=3.14159265359;
 
out vec4 FragColor;

vec3 CalculateBRDF(vec3 lightDir, vec3 radiance, vec3 albedo, vec3 N, float roughness, float ao, float metallic);
//��̬�ֲ�����
float DistributionGGX(vec3 H,vec3 N,float roughness);
//���κ���
float GeometrySchlickGGX(vec3 N,vec3 v,float roughness);
//������Ӱ�ͼ����ڱ�
float GeometrySmith(vec3 N,vec3 L,vec3 E,float roughness);	
//����������
vec3 Fresnel(float cosTheta,vec3 F0);

vec3 GetNormalFromMap();

vec4 GetSkyBoxColor(vec3 reflectV);

vec3 WorldViewObjDir();

void main() 
{
	
	
	vec3 albedo;
	vec3 N;
	float roughness;
	float ao;
	float metallic;

	//�Ӹ�����ͼ�л�ȡ����
	albedo = pow(texture(albedoMap, TexCoord).rgb, vec3(2.2));		//����������һ�㴴����rgb�ռ䣬������Ҫת�������Կռ�

	if(isTextureMetallic)
		metallic = texture(metallicMap, TexCoord).r;
	else
		metallic = numMetallic;

	if(isTextureRoughness)
		roughness = texture(roughnessMap, TexCoord).r;
	else
		roughness = numRoughness;

	if(isTextureAO)
		ao = texture(aoMap, TexCoord).r;
	else
		ao = 1.0;
	
	//���÷�����ͼ
	if(isTextureNormal)
		N = GetNormalFromMap();
	else
		N = vec3(0.0, 1.0, 0.0);
	 
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	vec3 color = vec3(0.0);
	for(int i = 0; i < POINT_LIGHT_NUM; i++)
	{
		if(pointLights[i].isAble)
		{
			vec3 lightColor = pointLights[i].color;
			vec3 lightDir = normalize(pointLights[i].position - posW);
			float distance = length(pointLights[i].position - posW);
			float attenuation = 1.0 / (pointLights[i].constant + pointLights[i].linear * distance + (distance * distance) * pointLights[i].quadratic);
			vec3 radiance = lightColor * attenuation;
			color += CalculateBRDF(lightDir, radiance, albedo, N, roughness, ao, metallic);
		}
	}

	for(int i = 0; i < DIR_LIGHT_NUM; i++)
	{
		if(dirLights[i].isAble)
		{
			vec3 lightColor = dirLights[i].color;
			vec3 lightDir = normalize(-dirLights[i].dir);
			vec3 radiance = lightColor;
			color += CalculateBRDF(lightDir, radiance, albedo, N, roughness, ao, metallic);
		}
	}

	//٤��У��
	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0 / 2.2));


	//�����ǰ�����ȴ��ڴ˵�����Ӱ��ͼ�е���ȣ�˵�����������Ӱ��
	float bias = 0.000;
	float visibility = 1.0;
	/*if(useShadowTex)
	{
		//if(texture(shadowTex,shadowCoord.xy).z+bias<shadowCoord.z)
		if(texture(shadowTex,vec3(shadowCoord.xy,shadowCoord.z-bias))!=1)
		visibility=0.5;	
	}*/
	color*=visibility;

	// �������ȫ͸������Ⱦģʽ���οգ�����������
	if(renderMode != 0 && texture(albedoMap, TexCoord).a < 0.1)
		discard;
	
    FragColor = vec4(color, texture(albedoMap, TexCoord).a); 
} 

//��̬�ֲ�����
float DistributionGGX(vec3 H,vec3 N,float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H),0.0);
	float NdotH2 = NdotH * NdotH;

	float denom = PI * (NdotH2 * (a2 - 1) + 1) * (NdotH2 * (a2 - 1) + 1);
	float nom = a2;

	return nom / max(denom, 0.001);
}

//���κ���
float GeometrySchlickGGX(vec3 N, vec3 v, float roughness)
{
	//�������ֱ�ӹ��յ�kֵ
	float k = (roughness + 1) * (roughness + 1) / 8.0;

	float Ndotv = max(dot(N, v), 0.0);
	float nom = Ndotv;

	float denom = Ndotv * (1.0 - k) + k;

	return nom / denom;
}

//������Ӱ�ͼ����ڱ�
float GeometrySmith(vec3 N,vec3 L,vec3 E,float roughness)			
{
	float GSGGXL=GeometrySchlickGGX(N,L,roughness);
	float GSGGXE=GeometrySchlickGGX(N,E,roughness);

	return GSGGXL*GSGGXE;
}

//����������
vec3 Fresnel(float cosTheta,vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 GetNormalFromMap()
{
	vec3 tangentNormal = texture(normalMap, TexCoord).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(posW);
    vec3 Q2  = dFdy(posW);
    vec2 st1 = dFdx(TexCoord);
    vec2 st2 = dFdy(TexCoord);

    vec3 N   = normalize(normalW);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

vec3 CalculateBRDF(vec3 lightDir, vec3 radiance, vec3 albedo, vec3 N, float roughness, float ao, float metallic)
{
	vec3 colorBRDF = vec3(0);
	vec3 V = normalize(eyePos - posW);
	vec3 H = normalize(V + lightDir);									//�����м�����

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	//����BDRF�еľ��淴��
	float D = DistributionGGX(H, N, roughness);
	float G = GeometrySmith(N, lightDir, V, roughness);
	vec3 F = Fresnel(clamp(dot(H, V), 0.0 ,1.0), F0);

	vec3 nom = D * G * F;
	float denom = 4 * max(dot(N, V), 0.0) * max(dot(N, lightDir), 0.0);	//0.001��ֹ��0
	vec3 specular = nom / max(denom, 0.001);

	//����BDRF�е�������
	vec3 KS = F;					//���������Ѿ�����˷�����ߵ�ռ��
	vec3 KD = vec3(1.0) - KS;
	KD *= 1.0 - metallic;			//��Ϊ����û�������䣬���Ը��ݽ��������¾���������


	float NdotL = max(dot(N, lightDir), 0.0);
	colorBRDF += (KD * albedo / PI + specular) * radiance * NdotL;


	vec3 skyBoxColor = vec3(1);
	if(isSkyBox)
	{
		vec3 sampleV = reflect(WorldViewObjDir(), normalize(normalW));
		skyBoxColor = GetSkyBoxColor(sampleV).rgb;
	}
	

	vec3 ambient = vec3(0.03) * albedo * ao * skyBoxColor;
	colorBRDF = ambient + colorBRDF;

	return colorBRDF;
}

vec4 GetSkyBoxColor(vec3 reflectV)
{
	vec4 res = vec4(texture(skyBoxMap, reflectV).rgb, 1.0);
	return res;
}

// ��ȡ���������µ��ӵ㵽���������
vec3 WorldViewObjDir()
{
	vec3 res = normalize(posW - eyePos);
	return res;
}