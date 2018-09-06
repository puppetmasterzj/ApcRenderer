/*!
 * \file Main.cpp
 *
 * \author zhangjian
 * \date 2017.5.14
 *
 * \ ѧϰOpenGL��ش��룬main�������
 */
#include "Common/ApcUtility.h"
#include "RenderEngine/NativeGLDevice.h"

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
void ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
void MouseCallBack(GLFWwindow* window, double xpos, double ypos);
GLfloat deltaTime = 0.0f;
GLfloat lastFrameTime = 0.0f;

class NativeGLDevice;

int main(int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cout << "Init GLFW Library Failed!" << std::endl;
		return -1;
	}

	//��ʼ��glfw����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	int width = NativeGLDevice::GetWindowWidth();
	int height = NativeGLDevice::GetWindowHeight();

	//��������
	GLFWwindow* window = glfwCreateWindow(width, height, "SunnyAlpaca", NULL, NULL);
	if (!window)
	{
		std::cout << "Init Window Failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	//����context
	glfwMakeContextCurrent(window);
	
	//��ʼ��glew����
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cout << "Init GLEW Library Failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	//���ü������ص�
	glfwSetKeyCallback(window, KeyCallBack);
	glfwSetCursorPosCallback(window, MouseCallBack);
	glfwSetScrollCallback(window, ScrollCallBack);

	glViewport(0, 0, width, height);
	//��ʼ��GL��
	NativeGLDevice::GetInstance()->Init();
	//��ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//֡ʱ�䴦��
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
		
		//���������¼�
		glfwPollEvents();
		//����
		NativeGLDevice::GetInstance()->Draw(window);
	}
	glfwTerminate();
	return 0;
}



bool keys[1024];
bool firstMouse = true;
GLfloat lastX = 400;
GLfloat lastY = 300;


// Is called whenever a key is pressed/released via GLFW
void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	Camera* camera = NativeGLDevice::GetInstance()->GetCurrentCamera();
	if (camera == NULL)
		return;
	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyBoard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyBoard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyBoard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyBoard(RIGHT, deltaTime);
}

void MouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;
	Camera* cam = NativeGLDevice::GetInstance()->GetCurrentCamera();
	if (cam != NULL)
	{
		cam->ProcessMouseMove(xoffset, yoffset);
	}
}


void ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera* cam = NativeGLDevice::GetInstance()->GetCurrentCamera();
	if (cam != NULL)
	{
		cam->ProcessMouseScroll(yoffset);
	}
}