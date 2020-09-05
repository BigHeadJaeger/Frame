#pragma once
#include<glad/glad.h>
#include<glm.hpp>
using namespace glm;

#include"ShaderManager.h"
#include"Transform.h"
#include"ShaderDataTool.h"
#include"TextureManager.h"

enum RenderMode
{
    Opaque,
    Cutout,
    Fade,
    Transparent
};

// 每个物体需要一个Material
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
    vec4 baseColor = vec4(225, 225, 225, 255);      // 基础颜色值
    shared_ptr<Texture> baseTex;                    // 基础贴图

    bool isSkyBox;
public:
    void SetTextureBase(string fileName);
    void SetTextureBase(shared_ptr<Texture> tex)
    { 
        baseTex = tex; 
        baseTex->SettingTexture();
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
        shader = ShaderManager::GetInstance().GetShader("SF_SimpleColor");
    }
    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        tool.SetUniform("color", baseColor / vec4(255), shader);
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
        shader = ShaderManager::GetInstance().GetShader("SF_Phong");
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
    GLuint texBoxID;
public:
    SkyBoxMaterial()
    {
        shader = ShaderManager::GetInstance().GetShader("SF_SkyBox");
        glGenTextures(1, &texBoxID);
    }
    // 初始化六张图片（根据前缀自动按照1~6， 右左上下后前的顺序初始化， 文件名为 pathPreix + _1,2...）
    void InitSkyBox(string pathPreix)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, texBoxID);
        int width, height, numChannels;
        unsigned char* pResult;
        for (size_t i = 0; i < 6; i++)
        {
            string imgPath = pathPreix + "_" + to_string(i + 1) + ".jpg";
            pResult = SOIL_load_image(imgPath.c_str(), &width, &height, &numChannels, SOIL_LOAD_RGB);
            if (pResult)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pResult);
                SOIL_free_image_data(pResult);
            }
            else
            {
                cout << "the " + imgPath + " cubemap load failed" << endl;
                SOIL_free_image_data(pResult);
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    // 分别初始化每一个面的值
    void InitSkyBoxPostiveX(string path);
    void InitSkyBoxNegativeX(string path);
    void InitSkyBoxPostiveY(string path);
    void InitSkyBoxNegativeY(string path);
    void InitSkyBoxPostiveZ(string path);
    void InitSkyBoxNegativeZ(string path);

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();
        //GLuint texLocation;
        //glActiveTexture(0);							//激活纹理单元(纹理位置)。
        //glBindTexture(GL_TEXTURE_CUBE_MAP, texBoxID);				//将纹理对象绑定到当前激活的纹理单元处
        ////接下来指定采样器对应哪个纹理单元
        //texLocation = glGetUniformLocation(shader.lock()->p, "cubemap");	//获取采样器的location
        //glUniform1i(texLocation, 0);									//指定采样器对应当前绑定的纹理单元0
        tool.SetTextureCube(texBoxID, 0, GL_TEXTURE0, "cubemap", shader);
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
        isSkyBox = true;
        renderMode = RenderMode::Opaque;
        shader = ShaderManager::GetInstance().GetShader("SF_PBR");
        SetTextureBase("");
    }

    void SetTextureMetallic(string fileName) 
    {
        metalicTex = texManager.GetTexture(fileName);
        metalicTex->SettingTexture();
    }
    void SetTextureMetallic(shared_ptr<Texture> tex)
    {
        metalicTex = tex;
        metalicTex->SettingTexture();
    }

    void SetTextureRoughness(string fileName)
    {
        roughnessTex = texManager.GetTexture(fileName);
        roughnessTex->SettingTexture();
    }
    void SetTextureRoughness(shared_ptr<Texture> tex) 
    {
        roughnessTex = tex; 
        roughnessTex->SettingTexture();
    }

    void SetTextureAO(string fileName)
    {
        aoTex = texManager.GetTexture(fileName); 
        aoTex->SettingTexture();
    }
    void SetTextureAO(shared_ptr<Texture> tex) 
    {
        aoTex = tex; 
        aoTex->SettingTexture();
    }

    void SetTextureNormal(string fileName) 
    {
        normalTex = texManager.GetTexture(fileName);
        normalTex->SettingTexture();
    }
    void SetTextureNormal(shared_ptr<Texture> tex) 
    {
        normalTex = tex;  
        normalTex->SettingTexture();
    }

    void SetRenderMode(RenderMode mode) { renderMode = mode; }

    void Transfer() override
    {
        decltype(auto) tool = ShaderDataTool::GetInstance();

        // 绘制顺序是由远到近
        glEnable(GL_BLEND);
        switch (renderMode)
        {
        case RenderMode::Opaque:
            // 保留源，舍弃目标
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
            // Cs* 1 + Ct * (1 - Fs) 保留自身的颜色完整，且和后面的混合
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
            tool.SetTextureCube(skyBox->texBoxID, 10, GL_TEXTURE10, "skyBoxMap", shader);
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

    shared_ptr<Texture> aoTex;
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
        aoTex = texManager.GetTexture(fileName);
        aoTex->SettingTexture();
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
            tool.SetTextureCube(skyBox->texBoxID, 10, GL_TEXTURE10, "skyBoxMap", shader);
        }
        else
        {
            tool.SetUniform("isSkyBox", false, shader);
        }
    }
};