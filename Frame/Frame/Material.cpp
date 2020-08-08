#include "Material.h"

void PhongMaterial::Transfer(ShaderProgram& shaderProgram)
{
    auto tool = ShaderDataTool::GetInstance();
    tool.SetUniform("isVertexLight", isVertexLight, shaderProgram);
    tool.SetUniform("material.ambient", ambient / vec3(255), shaderProgram);
    tool.SetUniform("material.diffuse", diffuse / vec3(255), shaderProgram);
    tool.SetUniform("material.specular", specular / vec3(255), shaderProgram);
    tool.SetUniform("material.shininess", shininess, shaderProgram);
}
