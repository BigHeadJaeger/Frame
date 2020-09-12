#pragma once
#include<glad\glad.h>
#include<GLFW\glfw3.h>

#include"Scene.h"
#include"Const.h"
#include"RenderFrameModel.h"

//const GLuint WIDTH = 1200, HEIGHT = 1000;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//MyScene scene;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
//��������
GLFWwindow* window;

int main(void)
{
	//��ʼ��glfw
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "RenderFrame", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* �ú���ָ���ڵ�ǰ�����߳��ϵĴ�����Ⱦ����ΪOpenGL��OpenGL ES���� */
	glfwMakeContextCurrent(window);

	//ָ���¼�
	glfwSetKeyCallback(window, key_callback);			//�����¼�
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	glfwSetMouseButtonCallback(window, mouse_button_callback);		//��갴���¼�

	glfwSetCursorPosCallback(window, cursor_position_callback);		//���ָ���¼�

	glfwSetScrollCallback(window, mouse_scroll_callback);			// �������¼�
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	


	//��������
	shared_ptr<MyScene> scene = make_shared<MyScene>();
	RenderFrameModel::GetInstance().SetCurrentScene(scene);

	scene->Init();


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//����һ֡�ļ��
		auto currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		//�������ºͻ���
		scene->Update(deltaTime);
		scene->Draw();

		//����˫����
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		//glfwWaitEvents();
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto scene = RenderFrameModel::GetInstance().GetCurrentScene();
	//��keep�¼���һ��Ҫ��up�¼�
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		scene->keys[BTNW].BindKeepEvent([&]() {
		auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
		mainCamera->Walk(mainCamera->cameraSpeed * deltaTime);
			});
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		scene->keys[BTNW].BindUpEvent([]() {
			});

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		scene->keys[BTNS].BindKeepEvent([]() {
		auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
		mainCamera->Walk(-mainCamera->cameraSpeed * deltaTime);
			});
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		scene->keys[BTNS].BindUpEvent([]() {
			});

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		scene->keys[BTNA].BindKeepEvent([]() {
		auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
		mainCamera->LRMove(mainCamera->cameraSpeed * deltaTime);
			});
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		scene->keys[BTNA].BindUpEvent([]() {
			});

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		scene->keys[BTND].BindKeepEvent([]() {
		auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
		mainCamera->LRMove(-mainCamera->cameraSpeed * deltaTime);
			});
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		scene->keys[BTND].BindUpEvent([]() {
			});

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		scene->keys[BTN1].BindDownEvent([&]() {
		auto scene = RenderFrameModel::GetInstance().GetCurrentScene();
		scene->drawMode.isLine = !scene->drawMode.isLine;
			});

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		scene->screenRender.isOpen = !scene->screenRender.isOpen;
		scene->screenRender.SetScreenType(SCREEN_RENDER_TYPE::INVERSE_COLOR);
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		scene->screenRender.isOpen = !scene->screenRender.isOpen;
		scene->screenRender.SetScreenType(SCREEN_RENDER_TYPE::KERNEL);
		scene->screenRender.SetSharpenKernel();
	}

	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		scene->screenRender.isOpen = !scene->screenRender.isOpen;
		scene->screenRender.SetScreenType(SCREEN_RENDER_TYPE::KERNEL);
		scene->screenRender.SetBlurKernel();
	}

	if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		scene->screenRender.isOpen = false;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
		mainCamera->fov = INITFOV;
	}

}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	auto scene = RenderFrameModel::GetInstance().GetCurrentScene();
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		scene->mouse.mouseRightDown = true;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		scene->mouse.mouseRightDown = false;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	auto scene = RenderFrameModel::GetInstance().GetCurrentScene();
	auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
	//cout << xpos << "  " << ypos << endl;
	if (scene->mouse.mouseRightDown)
	{
		auto disx = scene->mouse.cursorPrePos.x - xpos;
		auto disy = scene->mouse.cursorPrePos.y - ypos;
		mainCamera->LRRotate(disx * deltaTime * 0.5);
		mainCamera->UDRotate(-disy * deltaTime * 0.5);
	}

	/*if (scene->mouse.isCatchPoint && scene->mouse.mouseLeftDown)
	{
		float disx = scene->mouse.cursorPrePos.x - xpos;
		float disy = scene->mouse.cursorPrePos.y - ypos;

		float temp = deltaTime * 2;
		translate(scene->ObjArray()[scene->mouse.catchObjIndex].World, vec3(disx * temp, disy * temp, 0.0));
	}*/

	scene->mouse.cursorNowPos = scene->mouse.cursorPrePos - vec2(xpos, ypos);

	scene->mouse.cursorPrePos.x = xpos;
	scene->mouse.cursorPrePos.y = ypos;
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
	auto num = (mainCamera->fov - yoffset * deltaTime);
	if (num >= MINFOV && num <= MAXFOV)
	{
		mainCamera->fov -= yoffset;
	}
	else if (num < MINFOV)
	{
		mainCamera->fov = MINFOV;
	}
	else if (num > MAXFOV)
	{
		mainCamera->fov = MAXFOV;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
