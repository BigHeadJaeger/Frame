#include "FileInterface.h"

std::string file::GetResPath(std::string path)
{
	return "res/" + path;
}

std::string file::GetShaderPath(std::string path)
{
	return "shader/" + path;
}
