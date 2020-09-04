// 文件路径的引用
#pragma once
#include<string>

namespace file
{
	// 获取res路径下的东西
	std::string GetResPath(std::string path);

	// shader文件
	std::string GetShaderPath(std::string path);
}

