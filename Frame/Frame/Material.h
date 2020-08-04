#pragma once
#include<glad/glad.h>
#include<glm.hpp>
using namespace glm;
// 每个物体需要一个Material
class Material
{
public:
    vec4 baseColor;             // 基础颜色值
    GLuint textureBase;         // 基础贴图
    bool isTextureBase;         // 是否使用基础贴图，否则用baseColor作为基础颜色
public:
    Material()
    {
        baseColor = vec4(255, 255, 255, 255);       // 采用255制的颜色值，传入shader的时候在换算成0~1
        isTextureBase = false;
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