#pragma once
#include<glad/glad.h>
#include<glm.hpp>
using namespace glm;

#include"Program.h"
#include"ShaderDataTool.h"

enum class MATERIALTYPE
{
    MATERIAL_DEFAULT_DIFFUSE,
    MATERIAL_DEFAULT_SPECULAR,
    MATERIAL_PHONG
};

// ÿ��������Ҫһ��Material
class Material
{
public:
    vec4 baseColor = vec4(125, 125, 125, 255);      // ������ɫֵ
    GLuint textureBase;                             // ������ͼ
    bool isTextureBase = false;                     // �Ƿ�ʹ�û�����ͼ��������baseColor��Ϊ������ɫ
    MATERIALTYPE type;
public:
    //Material()
    //{
    //    baseColor = vec4(255, 255, 255, 255);       // ����255�Ƶ���ɫֵ������shader��ʱ���ڻ����0~1
    //    isTextureBase = false;
    //}

    // ÿ���������Լ��ķ��������ݴ��䵽shader��
    virtual void Transfer(ShaderProgram& shaderProgram) = 0;
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
    vec3 ambient = vec3(baseColor.x, baseColor.y, baseColor.z);
    vec3 diffuse = vec3(baseColor.x, baseColor.y, baseColor.z);
    vec3 specular = vec3(125, 125, 125);
    float shininess = 32.0f;
    bool isVertexLight = false;
public:
    PhongMaterial() 
    {
        type = MATERIALTYPE::MATERIAL_PHONG;
    }

    void Transfer(ShaderProgram& shaderProgram) override;
};

class PBRMaterial :public Material
{

};