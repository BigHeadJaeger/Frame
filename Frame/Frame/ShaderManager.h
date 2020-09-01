// 管理编译好的shader文件 可以复用
#pragma once
#include<map>
#include<string>
#include<iostream>
#include<memory>
#include"Program.h"
#include"FileInterface.h"

class ShaderManager
{
private:
	std::map<std::string, std::shared_ptr<ShaderProgram>> shadersMap;
private:
	ShaderManager() {};
	std::shared_ptr<ShaderProgram> CreateShader(std::string name)
	{
		auto shader = std::make_shared<ShaderProgram>();
		shader->SetShader(file::GetShaderPath((name + ".v")).c_str(), file::GetShaderPath((name + ".f")).c_str());
		shadersMap.insert(std::make_pair(name, shader));
		return shader;
	}
public:
	static ShaderManager& GetInstance()
	{
		static ShaderManager instance;
		return instance;
	}
	ShaderManager(ShaderManager&) = delete;


	std::shared_ptr<ShaderProgram> GetShader(std::string name)
	{
		auto it = shadersMap.find(name);
		if (it != shadersMap.end())
			return it->second;
		else
		{
			auto shader = CreateShader(name);
			return shader;
		}
	}
};