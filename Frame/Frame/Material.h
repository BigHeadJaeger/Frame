#pragma once
#include<glad/glad.h>
#include<glm.hpp>
using namespace glm;

#include"Program.h"

// 每个物体需要一个Material
class Material
{
public:
    vec4 baseColor = vec4(255, 255, 255, 255);      // 基础颜色值
    GLuint textureBase;                             // 基础贴图
    bool isTextureBase = false;                     // 是否使用基础贴图，否则用baseColor作为基础颜色
public:
    //Material()
    //{
    //    baseColor = vec4(255, 255, 255, 255);       // 采用255制的颜色值，传入shader的时候在换算成0~1
    //    isTextureBase = false;
    //}

    // 每个材质有自己的方法将数据传输到shader中
    virtual void Transfer(ShaderProgram& shaderProgram) = 0;
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
    vec3 ambient = baseColor;
    vec3 diffuse = baseColor;
    vec3 specular = vec3(125, 125, 125);
    float shininess = 32.0f;
public:
    PhongMaterial() { }

    void Transfer(ShaderProgram& shaderProgram) override
    {

    }
};

class PBRMaterial :public Material
{

};