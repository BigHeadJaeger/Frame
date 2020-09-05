#version 460

layout(location = 0) in vec3 positionL;

out vec3 texcoordF;

// ��պв���Ҫworld������Ҫ��view�����е�λ��ȥ����4x4�ľ���������а���λ����Ϣ��Ҳ��ͨ����λ�õ��ĸ�������Ϊ0�����λ�ƣ�
// �������Ƶ�����λ��ʼ��������е�
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos = projection * view * vec4(positionL, 1.0);
	//pos.w = 1.0;
	//pos = projection * pos;
	gl_Position = pos.xyww;			// ����պе����ʼ��Ϊ1��͸�ӳ����ڶ�����ɫ��֮����У�
	//gl_Position = vec4(0.5, 0, 0, 1.0);
	texcoordF = positionL;			// ����λ��ֱ����Ϊ��ά����������
}