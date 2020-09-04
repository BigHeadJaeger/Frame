#version 460

//这里采用的直接光照，不考虑环境光照，因此每一个点的入射光只考虑存在的光源个数，将总辐照度相加即可，如果考虑全局光照，则需要解积分计算

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

//阴影贴图纹理采样器
uniform sampler2DShadow shadowTex;
uniform bool useShadowTex;

//物体PBR材质
//当前属性的值是否用纹理来决定
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

//光照信息
#define DIR_LIGHT_NUM 10
uniform DirLight dirLights[DIR_LIGHT_NUM];
#define POINT_LIGHT_NUM 10
uniform PointLight pointLights[POINT_LIGHT_NUM];

//眼睛位置
uniform vec3 eyePos;

const float PI=3.14159265359;
 
out vec4 FragColor;

vec3 CalculateBRDF(vec3 lightDir, vec3 radiance, vec3 albedo, vec3 N, float roughness, float ao, float metallic);
//正态分布函数
float DistributionGGX(vec3 H,vec3 N,float roughness);
//几何函数
float GeometrySchlickGGX(vec3 N,vec3 v,float roughness);
//几何阴影和几何遮蔽
float GeometrySmith(vec3 N,vec3 L,vec3 E,float roughness);	
//菲涅尔方程
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

	//从各种贴图中获取数据
	albedo = pow(texture(albedoMap, TexCoord).rgb, vec3(2.2));		//反射率纹理一般创建在rgb空间，所以需要转换到线性空间

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
	
	//采用法线贴图
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

	//伽马校正
	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0 / 2.2));


	//如果当前点的深度大于此点在阴影贴图中的深度，说明这个点在阴影中
	float bias = 0.000;
	float visibility = 1.0;
	/*if(useShadowTex)
	{
		//if(texture(shadowTex,shadowCoord.xy).z+bias<shadowCoord.z)
		if(texture(shadowTex,vec3(shadowCoord.xy,shadowCoord.z-bias))!=1)
		visibility=0.5;	
	}*/
	color*=visibility;

	// 如果是完全透明且渲染模式是镂空，则舍弃像素
	if(renderMode != 0 && texture(albedoMap, TexCoord).a < 0.1)
		discard;
	
    FragColor = vec4(color, texture(albedoMap, TexCoord).a); 
} 

//正态分布函数
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

//几何函数
float GeometrySchlickGGX(vec3 N, vec3 v, float roughness)
{
	//计算基于直接光照的k值
	float k = (roughness + 1) * (roughness + 1) / 8.0;

	float Ndotv = max(dot(N, v), 0.0);
	float nom = Ndotv;

	float denom = Ndotv * (1.0 - k) + k;

	return nom / denom;
}

//几何阴影和几何遮蔽
float GeometrySmith(vec3 N,vec3 L,vec3 E,float roughness)			
{
	float GSGGXL=GeometrySchlickGGX(N,L,roughness);
	float GSGGXE=GeometrySchlickGGX(N,E,roughness);

	return GSGGXL*GSGGXE;
}

//菲涅尔方程
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
	vec3 H = normalize(V + lightDir);									//计算中间向量

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	//计算BDRF中的镜面反射
	float D = DistributionGGX(H, N, roughness);
	float G = GeometrySmith(N, lightDir, V, roughness);
	vec3 F = Fresnel(clamp(dot(H, V), 0.0 ,1.0), F0);

	vec3 nom = D * G * F;
	float denom = 4 * max(dot(N, V), 0.0) * max(dot(N, lightDir), 0.0);	//0.001防止除0
	vec3 specular = nom / max(denom, 0.001);

	//计算BDRF中的漫反射
	vec3 KS = F;					//菲涅尔中已经求出了反射光线的占比
	vec3 KD = vec3(1.0) - KS;
	KD *= 1.0 - metallic;			//因为金属没有漫反射，所以根据金属度重新决定漫反射


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

// 获取世界坐标下的视点到顶点的向量
vec3 WorldViewObjDir()
{
	vec3 res = normalize(posW - eyePos);
	return res;
}