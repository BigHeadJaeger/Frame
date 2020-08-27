#pragma once
#include<glad/glad.h>
#include<glm.hpp>
using namespace glm;

#include"Program.h"
#include"Transform.h"
#include"ShaderDataTool.h"
#include"TextureManager.h"

enum class MATERIALTYPE
{
    MATERIAL_DEFAULT_DIFFUSE,
    MATERIAL_DEFAULT_SPECULAR,
    MATERIAL_PHONG,
    MATERIAL_PBR,
    MATERIAL_SIMPLE_COLOR
};

// ÿ��������Ҫһ��Material
class Material
{
protected:
    TextureManager& texManager = TextureManager::GetInstance();
public:
    ShaderProgram shaderProgram;
public:
    vec4 baseColor = vec4(225, 225, 225, 255);      // ������ɫֵ
    shared_ptr<Texture> baseTex;                    // ������ͼ
    MATERIALTYPE type;
public:
    void SetTextureBase(string fileName)
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        if (fileName == "")
        {
            baseTex = texManager.GetTexture("Material\\Default\\BaseColor.png");
        }
        else
        {
            baseTex = texManager.GetTexture(fileName);
        }
    }

    // ÿ���������Լ��ķ��������ݴ��䵽shader��
    virtual void Transfer() = 0;
};

// �����ʶ�ʧʱʹ�õ�Ĭ�ϲ���
class NoneMaterial :public Material
{
public:
    NoneMaterial()
    {
        baseColor = vec4(238, 130, 238, 255);
        shaderProgram.SetShader("SF_SimpleColor.v", "SF_SimpleColor.f");
        type = MATERIALTYPE::MATERIAL_SIMPLE_COLOR;
    }
    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetUniform("color", baseColor / vec4(255), shaderProgram);
    }
};

// Ĭ�����������
class DefaultDiffuseMaterial : public Material
{
     
};

// Ĭ�Ͼ��淴�����
class DefaultSpecularMaterial : public Material
{
public:
    vec3 specular;
    float shininess = 32.0f;
public:
    DefaultSpecularMaterial()
    {
        specular = vec3(baseColor.x, baseColor.y, baseColor.z);
        shaderProgram.SetShader("SF_DefaultSpecular.v", "SF_DefaultSpecular.f");
    }

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetUniform("baseColor", vec3(baseColor.x, baseColor.y, baseColor.z) / vec3(255), shaderProgram);
        tool.SetUniform("specular", specular / vec3(255), shaderProgram);
        tool.SetUniform("shininess", shininess, shaderProgram);
        if(baseTex)
            tool.SetTexture(baseTex->id, 0, GL_TEXTURE0, "albedoMap", shaderProgram);
        
    }
};

// �����˻��� ������ ���淴��Ĳ��ʣ���ֻ�����ֿ��ƣ����漰��ͼ
class PhongMaterial:public Material
{
public:
    vec3 ambient = vec3(baseColor.x, baseColor.y, baseColor.z);
    vec3 diffuse = vec3(baseColor.x, baseColor.y, baseColor.z);
    vec3 specular = vec3(baseColor.x, baseColor.y, baseColor.z);
    float shininess = 32.0f;
public:
    PhongMaterial() 
    {
        shaderProgram.SetShader("SF_Phong.v", "SF_Phong.f");
        type = MATERIALTYPE::MATERIAL_PHONG;
    }

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetUniform("material.ambient", ambient / vec3(255), shaderProgram);
        tool.SetUniform("material.diffuse", diffuse / vec3(255), shaderProgram);
        tool.SetUniform("material.specular", specular / vec3(255), shaderProgram);
        tool.SetUniform("material.shininess", shininess, shaderProgram);
    }
};

class PBRMaterial :public Material
{

public:
    shared_ptr<Texture> metalicTex;
    float numMetallic = 0.5;

    shared_ptr<Texture> roughnessTex;
    float numRoughness = 0.5;

    shared_ptr<Texture> aoTex;
    shared_ptr<Texture> normalTex;
public:
    PBRMaterial()
    {
        shaderProgram.SetShader("SF_PBR.v", "SF_PBR.f");
        type = MATERIALTYPE::MATERIAL_PBR;
    }

    void SetTextureMetallic(string fileName)
    {
        metalicTex = texManager.GetTexture(fileName);
    }
    void SetTextureRoughness(string fileName)
    {
        roughnessTex = texManager.GetTexture(fileName);
    }
    void SetTextureAO(string fileName)
    {
        aoTex = texManager.GetTexture(fileName);
    }
    void SetTextureNormal(string fileName)
    {
        normalTex = texManager.GetTexture(fileName);
    }

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetUniform("baseColor", vec3(baseColor.x, baseColor.y, baseColor.z) / vec3(255), shaderProgram);
        if (baseTex)
            tool.SetTexture(baseTex->id, 0, GL_TEXTURE0, "albedoMap", shaderProgram);

        if (metalicTex)
        {
            tool.SetUniform("isTextureMetallic", true, shaderProgram);
            tool.SetTexture(metalicTex->id, 1, GL_TEXTURE1, "metallicMap", shaderProgram);
        }
        else
        {
            tool.SetUniform("isTextureMetallic", false, shaderProgram);
            tool.SetUniform("numMetallic", numMetallic, shaderProgram);
        }

        if (roughnessTex)
        {
            tool.SetUniform("isTextureRoughness", true, shaderProgram);
            tool.SetTexture(roughnessTex->id, 2, GL_TEXTURE2, "roughnessMap", shaderProgram);
        }
        else
        {
            tool.SetUniform("isTextureRoughness", false, shaderProgram);
            tool.SetUniform("numRoughness", numRoughness, shaderProgram);
        }

        if (aoTex)
        {
            tool.SetUniform("isTextureAO", true, shaderProgram);
            tool.SetTexture(aoTex->id, 3, GL_TEXTURE3, "aoMap", shaderProgram);
        }
        else
            tool.SetUniform("isTextureAO", false, shaderProgram);

        if (normalTex)
        {
            tool.SetUniform("isTextureNormal", true, shaderProgram);
            tool.SetTexture(normalTex->id, 4, GL_TEXTURE4, "normalMap", shaderProgram);
        }
        else
            tool.SetUniform("isTextureNormal", false, shaderProgram);
    }

};