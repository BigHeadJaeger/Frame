#version 460

layout(location = 0) in vec3 positionL;

out vec3 texcoordF;

// 天空盒不需要world矩阵，且要将view矩阵中的位移去掉（4x4的矩阵第四列中包含位移信息，也可通过将位置第四个分量设为0来清除位移）
// 这样绘制的物体位置始终在相机中点
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos = projection * view * vec4(positionL, 1.0);
	//pos.w = 1.0;
	//pos = projection * pos;
	gl_Position = pos.xyww;			// 让天空盒的深度始终为1（透视除法在顶点着色器之后进行）
	//gl_Position = vec4(0.5, 0, 0, 1.0);
	texcoordF = positionL;			// 顶点位置直接作为三维的纹理坐标
}