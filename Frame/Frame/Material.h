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

// 每个物体需要一个Material
class Material
{
protected:
    TextureManager& texManager = TextureManager::GetInstance();
public:
    ShaderProgram shaderProgram;
public:
    vec4 baseColor = vec4(225, 225, 225, 255);      // 基础颜色值
    shared_ptr<Texture> baseTex;                    // 基础贴图
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

    // 每个材质有自己的方法将数据传输到shader中
    virtual void Transfer() = 0;
};

// 当材质丢失时使用的默认材质
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

// 默认漫反射材质
class DefaultDiffuseMaterial : public Material
{
     
};

// 默认镜面反射材质
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

// 包含了环境 漫反射 镜面反射的材质，且只用数字控制，不涉及贴图
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