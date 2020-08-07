#pragma once
#include<glad/glad.h>
#include<glm.hpp>
using namespace glm;

#include"Program.h"
#include"ShaderDataTool.h"

enum MATERIALTYPE
{
    MATERIAL_DEFAULT_DIFFUSE,
    MATERIAL_DEFAULT_SPECULAR,
    MATERIAL_PHONG
};

// ÿ��������Ҫһ��Material
class Material
{
public:
    vec4 baseColor = vec4(255, 255, 255, 255);      // ������ɫֵ
    GLuint textureBase;                             // ������ͼ
    bool isTextureBase = false;                     // �Ƿ�ʹ�û�����ͼ��������baseColor��Ϊ������ɫ
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
    vec3 ambient = baseColor;
    vec3 diffuse = baseColor;
    vec3 specular = vec3(125, 125, 125);
    float shininess = 32.0f;
    bool isVertexLight = false;
public:
    PhongMaterial() {}

    void Transfer(ShaderProgram& shaderProgram) override
    {
        auto tool = ShaderDataTool::GetInstance();
        tool.SetUniform("isVertexLight", isVertexLight, shaderProgram);
        tool.SetUniform("material.ambient", ambient / vec3(255), shaderProgram);
        tool.SetUniform("material.diffuse", diffuse / vec3(255), shaderProgram);
        tool.SetUniform("material.specular", specular / vec3(255), shaderProgram);
        tool.SetUniform("material.shininess", shininess, shaderProgram);
    }
};

class PBRMaterial :public Material
{

};