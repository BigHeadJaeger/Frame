#include "Material.h"
#include"FileInterface.h"

void Material::SetTextureBase(string fileName)
{
    decltype(auto) tool = ShaderDataTool::GetInstance();
    if (fileName == "")
    {
        baseTex = texManager.GetTexture2D(file::GetResPath("Material/Default/BaseColor.png"));
    }
    else
    {
        baseTex = texManager.GetTexture2D(fileName);
    }
    // ���ʰ󶨵�ʱ����������������
    //baseTex->SettingTexture();
}
