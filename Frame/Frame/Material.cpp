#include "Material.h"
#include"FileInterface.h"

void Material::SetTextureBase(string fileName)
{
    decltype(auto) tool = ShaderDataTool::GetInstance();
    if (fileName == "")
    {
        baseTex = texManager.GetTexture(file::GetResPath("Material/Default/BaseColor.png"));
    }
    else
    {
        baseTex = texManager.GetTexture(fileName);
    }
    // 材质绑定的时候再设置纹理属性
    baseTex->SettingTexture();
}
