#pragma once
#include<glad/glad.h>
#include<glm.hpp>
using namespace glm;

#include"ShaderManager.h"
#include"Transform.h"
#include"ShaderDataTool.h"
#include"TextureManager.h"
#include"TextureCube.h"
#include"stb_image.h"

enum RenderMode
{
    Opaque,
    Cutout,
    Fade,
    Transparent
};

// ÿ��������Ҫһ��Material
class Material
{
protected:
    TextureManager& texManager = TextureManager::GetInstance();
public:
    RenderMode renderMode;
    weak_ptr<ShaderProgram> shader;
    //ShaderProgram shaderProgram;
public:
    string name;
    vec4 baseColor = vec4(225, 225, 225, 255);      // ������ɫֵ
    shared_ptr<Texture2D> baseTex;                    // ������ͼ

    bool isSkyBox;
public:
    void SetTextureBase(string fileName);
    void SetTextureBase(shared_ptr<Texture2D> tex)
    { 
        baseTex = tex; 
        //baseTex->SettingTexture();
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
        shader = ShaderManager::GetInstance().GetShader("SF_SimpleColor");
    }
    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetUniform("color", baseColor / vec4(255), shader);
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
        renderMode = RenderMode::Opaque;
        specular = vec3(baseColor.x, baseColor.y, baseColor.z);
        shader = ShaderManager::GetInstance().GetShader("SF_DefaultSpecular");
        SetTextureBase("");
    }

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetUniform("baseColor", baseColor / vec4(255), shader);
        tool.SetUniform("specular", specular / vec3(255), shader);
        tool.SetUniform("shininess", shininess, shader);
        if(baseTex)
            tool.SetTexture(baseTex->id, 0, GL_TEXTURE0, "albedoMap", shader);

        
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
        shader = ShaderManager::GetInstance().GetShader("SF_Phong");
    }

    void SetBaseColor(vec4 _color)
    {
        baseColor = _color;
        ambient = vec3(_color);
        diffuse = vec3(_color);
        specular = vec3(_color);
    }

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetUniform("material.ambient", ambient / vec3(255), shader);
        tool.SetUniform("material.diffuse", diffuse / vec3(255), shader);
        tool.SetUniform("material.specular", specular / vec3(255), shader);
        tool.SetUniform("material.shininess", shininess, shader);
    }
};

class SkyBoxMaterial : public Material
{
public:
    shared_ptr<TextureCube> texCube;
public:
    SkyBoxMaterial()
    {
        shader = ShaderManager::GetInstance().GetShader("SF_SkyBox");
    }

    GLuint& GetTexCubeID()
    {
        return texCube->id;
    }

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetTextureCube(texCube->id, 0, GL_TEXTURE0, "cubemap", shader);
    }
};

// ʹ��cubeMap��ʼ����
class SkyBoxCubeMapMaterial : public SkyBoxMaterial
{
public:
    void SetTextureCube(shared_ptr<TextureCube> tex)
    {
        texCube = tex;
    }
};

// ʹ������ͼƬ��ʼ����
class SkyBox6SideMaterial : public SkyBoxMaterial
{
public:
    SkyBox6SideMaterial()
    {
        // ����Ҫ�ⲿ��cubemap���д���
        texCube = make_shared<TextureCube>();
    }
    // �ֱ��ʼ��ÿһ�����ֵ
    void InitSkyBoxPostiveX(string path)
    {
        texCube->LoadPostiveX(path);
    }
    void InitSkyBoxNegativeX(string path)
    {
        texCube->LoadNegativeX(path);
    }
    void InitSkyBoxPostiveY(string path)
    {
        texCube->LoadPostiveY(path);
    }
    void InitSkyBoxNegativeY(string path)
    {
        texCube->LoadNegativeY(path);
    }
    void InitSkyBoxPostiveZ(string path)
    {
        texCube->LoadPostiveZ(path);
    }
    void InitSkyBoxNegativeZ(string path)
    {
        texCube->LoadNegativeZ(path);
    }
};

class PBRMaterial :public Material
{
public:
    shared_ptr<Texture2D> metalicTex;
    float numMetallic = 0.5;

    shared_ptr<Texture2D> roughnessTex;
    float numRoughness = 0.5;

    shared_ptr<Texture2D> aoTex;
    shared_ptr<Texture2D> normalTex;
public:
    PBRMaterial()
    {
        isSkyBox = true;
        renderMode = RenderMode::Opaque;
        shader = ShaderManager::GetInstance().GetShader("SF_PBR");
        SetTextureBase("");
    }

    void SetTextureMetallic(string fileName) 
    {
        metalicTex = texManager.GetTexture2D(fileName);
        //metalicTex->SettingTexture();
    }
    void SetTextureMetallic(shared_ptr<Texture2D> tex)
    {
        metalicTex = tex;
        //metalicTex->SettingTexture();
    }

    void SetTextureRoughness(string fileName)
    {
        roughnessTex = texManager.GetTexture2D(fileName);
        //roughnessTex->SettingTexture();
    }
    void SetTextureRoughness(shared_ptr<Texture2D> tex) 
    {
        roughnessTex = tex; 
        //roughnessTex->SettingTexture();
    }

    void SetTextureAO(string fileName)
    {
        aoTex = texManager.GetTexture2D(fileName); 
        //aoTex->SettingTexture();
    }
    void SetTextureAO(shared_ptr<Texture2D> tex) 
    {
        aoTex = tex; 
        //aoTex->SettingTexture();
    }

    void SetTextureNormal(string fileName) 
    {
        normalTex = texManager.GetTexture2D(fileName);
        //normalTex->SettingTexture();
    }
    void SetTextureNormal(shared_ptr<Texture2D> tex) 
    {
        normalTex = tex;  
        //normalTex->SettingTexture();
    }

    void SetRenderMode(RenderMode mode) { renderMode = mode; }

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();

        // ����˳������Զ����
        glEnable(GL_BLEND);
        switch (renderMode)
        {
        case RenderMode::Opaque:
            // ����Դ������Ŀ��
            glBlendFunc(GL_ONE, GL_ZERO);
            break;
        case RenderMode::Cutout:
            glBlendFunc(GL_ONE, GL_ZERO);
            break;
        case RenderMode::Fade:
            // Cs* Fs + Ct * (1 - Fs)
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case RenderMode::Transparent:
            // Cs* 1 + Ct * (1 - Fs) �����������ɫ�������Һͺ���Ļ��
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            break;
        default:
            break;
        }

        tool.SetUniform("renderMode", renderMode, shader);
        
        tool.SetUniform("baseColor", vec3(baseColor.x, baseColor.y, baseColor.z) / vec3(255), shader);
        if (baseTex)
            tool.SetTexture(baseTex->id, 0, GL_TEXTURE0, "albedoMap", shader);

        if (metalicTex)
        {
            tool.SetUniform("isTextureMetallic", true, shader);
            tool.SetTexture(metalicTex->id, 1, GL_TEXTURE1, "metallicMap", shader);
        }
        else
        {
            tool.SetUniform("isTextureMetallic", false, shader);
            tool.SetUniform("numMetallic", numMetallic, shader);
        }

        if (roughnessTex)
        {
            tool.SetUniform("isTextureRoughness", true, shader);
            tool.SetTexture(roughnessTex->id, 2, GL_TEXTURE2, "roughnessMap", shader);
        }
        else
        {
            tool.SetUniform("isTextureRoughness", false, shader);
            tool.SetUniform("numRoughness", numRoughness, shader);
        }

        if (aoTex)
        {
            tool.SetUniform("isTextureAO", true, shader);
            tool.SetTexture(aoTex->id, 3, GL_TEXTURE3, "aoMap", shader);
        }
        else
            tool.SetUniform("isTextureAO", false, shader);

        if (normalTex)
        {
            tool.SetUniform("isTextureNormal", true, shader);
            tool.SetTexture(normalTex->id, 4, GL_TEXTURE4, "normalMap", shader);
        }
        else
            tool.SetUniform("isTextureNormal", false, shader);

        if (!isSkyBox)
        {
            tool.SetUniform("isSkyBox", false, shader);
            return;
        }
        auto skyBox = RenderFrameModel::GetInstance().GetSkyBoxMaterial();
        if (skyBox)
        {
            tool.SetUniform("isSkyBox", true, shader);
            tool.SetTextureCube(skyBox->GetTexCubeID(), 10, GL_TEXTURE10, "skyBoxMap", shader);
        }
        else
        {
            tool.SetUniform("isSkyBox", false, shader);
        }
    }
};



class EnvironmentMapping : public Material
{
public:
    float ratio = 1.f / 1.52f;
    int mode = 0;

    shared_ptr<Texture2D> aoTex;
public:
    EnvironmentMapping()
    {
        isSkyBox = true;
        shader = ShaderManager::GetInstance().GetShader("SF_ReflectAndRefract");
        SetTextureBase("");
    }

    void SetMode(int _mode)
    {
        mode = _mode;
    }

    void SetTextureAO(string fileName)
    {
        aoTex = texManager.GetTexture2D(fileName);
        //aoTex->SettingTexture();
    }

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetUniform("mode", mode, shader);
        tool.SetUniform("ratio", ratio, shader);
        tool.SetTexture(baseTex->id, 0, GL_TEXTURE0, "baseColorMap", shader);
        if (aoTex)
        {
            tool.SetUniform("isAO", true, shader);
            tool.SetTexture(aoTex->id, 1, GL_TEXTURE1, "AOMap", shader);
        }
        tool.SetUniform("isAO", false, shader);

        if (!isSkyBox)
        {
            tool.SetUniform("isSkyBox", false, shader);
            return;
        }
        auto skyBox = RenderFrameModel::GetInstance().GetSkyBoxMaterial();
        if (skyBox)
        {
            tool.SetUniform("isSkyBox", true, shader);
            tool.SetTextureCube(skyBox->GetTexCubeID(), 10, GL_TEXTURE10, "skyBoxMap", shader);
        }
        else
        {
            tool.SetUniform("isSkyBox", false, shader);
        }
    }
};