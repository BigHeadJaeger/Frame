#pragma once
#include<glad/glad.h>
#include<glm.hpp>
using namespace glm;

#include"Program.h"
#include"Transform.h"
#include"ShaderDataTool.h"

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
public:
    ShaderProgram shaderProgram;
public:
    vec4 baseColor = vec4(125, 30, 160, 255);      // 基础颜色值
    GLuint textureBase;                             // 基础贴图
    bool isTextureBase = false;                     // 是否使用基础贴图，否则用baseColor作为基础颜色
    MATERIALTYPE type;
public:
    void InitTextureBase(string fileName)
    {
        isTextureBase = true;
        auto tool = ShaderDataTool::GetInstance();
        tool.InitTextureWithFile(textureBase, fileName.c_str());
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
        auto tool = ShaderDataTool::GetInstance();
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
    vec3 specular;
};

// 包含了环境 漫反射 镜面反射的材质，且只用数字控制，不涉及贴图
class PhongMaterial:public Material
{
public:
    vec3 ambient = vec3(baseColor.x, baseColor.y, baseColor.z);
    vec3 diffuse = vec3(baseColor.x, baseColor.y, baseColor.z);
    vec3 specular = vec3(125, 125, 125);
    float shininess = 32.0f;
public:
    PhongMaterial() 
    {
        shaderProgram.SetShader("SF_Phong.v", "SF_Phong.f");
        type = MATERIALTYPE::MATERIAL_PHONG;
    }

    void Transfer() override
    {
        auto tool = ShaderDataTool::GetInstance();
            
        tool.SetUniform("material.ambient", ambient / vec3(255), shaderProgram);
        tool.SetUniform("material.diffuse", diffuse / vec3(255), shaderProgram);
        tool.SetUniform("material.specular", specular / vec3(255), shaderProgram);
        tool.SetUniform("material.shininess", shininess, shaderProgram);
    }
};

class PBRMaterial :public Material
{
public:
    GLuint textureMetallic;
    bool isTextureMetallic = false;
    float numMetallic = 0.5;
    GLuint textureRoughness;
    bool isTextureRoughness = false;
    float numRoughness = 0.5;
    GLuint textureAO;
    bool isTextureAO = false;
    GLuint textureNormal;
    bool isTextureNormal = false;

public:
    PBRMaterial()
    {
        shaderProgram.SetShader("SF_PBR.v", "SF_PBR.f");
        type = MATERIALTYPE::MATERIAL_PBR;
    }

    void InitTextureMetallic(string fileName)
    {
        isTextureMetallic = true;
        auto tool = ShaderDataTool::GetInstance();
        tool.InitTextureWithFile(textureMetallic, fileName.c_str());
    }
    void InitTextureRoughness(string fileName)
    {
        isTextureRoughness = true;
        auto tool = ShaderDataTool::GetInstance();
        tool.InitTextureWithFile(textureRoughness, fileName.c_str());
    }
    void InitTextureAO(string fileName)
    {
        isTextureAO = true;
        auto tool = ShaderDataTool::GetInstance();
        tool.InitTextureWithFile(textureAO, fileName.c_str());
    }
    void InitTextureNormal(string fileName)
    {
        isTextureNormal = true;
        auto tool = ShaderDataTool::GetInstance();
        tool.InitTextureWithFile(textureNormal, fileName.c_str());
    }

    void Transfer() override
    {
        auto tool = ShaderDataTool::GetInstance();
        tool.SetUniform("isTextureBase", isTextureBase, shaderProgram);
        if (isTextureBase)
            tool.SetTexture(textureBase, 0, GL_TEXTURE0, "albedoMap", shaderProgram);
        else
            tool.SetUniform("baseColor", vec3(baseColor.x, baseColor.y, baseColor.z) / vec3(255), shaderProgram);

        tool.SetUniform("isTextureMetallic", isTextureMetallic, shaderProgram);
        if (isTextureMetallic)
            tool.SetTexture(textureMetallic, 1, GL_TEXTURE1, "metallicMap", shaderProgram);
        else
            tool.SetUniform("numMetallic", numMetallic, shaderProgram);

        tool.SetUniform("isTextureRoughness", isTextureRoughness, shaderProgram);
        if (isTextureRoughness)
            tool.SetTexture(textureRoughness, 2, GL_TEXTURE2, "roughnessMap", shaderProgram);
        else
            tool.SetUniform("numRoughness", numRoughness, shaderProgram);

        tool.SetUniform("isTextureAO", isTextureAO, shaderProgram);
        if (isTextureAO)
            tool.SetTexture(textureAO, 3, GL_TEXTURE3, "aoMap", shaderProgram);
            
        tool.SetUniform("isTextureNormal", isTextureNormal, shaderProgram);
        if (isTextureNormal)
            tool.SetTexture(textureNormal, 4, GL_TEXTURE4, "normalMap", shaderProgram);
    }

};