#pragma once
#include<glad/glad.h>
#include<glm.hpp>
using namespace glm;
// ÿ��������Ҫһ��Material
class Material
{
public:
    vec4 baseColor;             // ������ɫֵ
    GLuint textureBase;         // ������ͼ
    bool isTextureBase;         // �Ƿ�ʹ�û�����ͼ��������baseColor��Ϊ������ɫ
public:
    Material()
    {
        baseColor = vec4(255, 255, 255, 255);       // ����255�Ƶ���ɫֵ������shader��ʱ���ڻ����0~1
        isTextureBase = false;
    }
};

// Ĭ�����������
class DefaultDiffuseMaterial : public Material
{
     
};

// Ĭ�Ͼ��淴�����
class DefaultSpecularMaterial : public Material
{
    vec3 specular;
};

// �����˻��� ������ ���淴��Ĳ��ʣ���ֻ�����ֿ��ƣ����漰��ͼ
class PhongMaterial:public Material
{
public:
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
public:
    PhongMaterial()
    {
        Material();
        ambient = baseColor;
        diffuse = baseColor;
        specular = vec3(0.5, 0.5, 0.5);
        shininess = 32.0f;
    }

};

class PBRMaterial :public Material
{

};