#include<windows.h>
#include <gl/glu.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#include <iostream>

void cube() {
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.05, 0.05, 0.05);
	glVertex3f(0.05, -0.05, 0.05);
	glVertex3f(0.05, -0.05, -0.05);
	glVertex3f(0.05, 0.05, -0.05);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-0.05, 0.05, 0.05);
	glVertex3f(-0.05, -0.05, 0.05);
	glVertex3f(-0.05, -0.05, -0.05);
	glVertex3f(-0.05, 0.05, -0.05);

	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.05, 0.05, 0.05);
	glVertex3f(-0.05, 0.05, 0.05);
	glVertex3f(-0.05, 0.05, -0.05);
	glVertex3f(0.05, 0.05, -0.05);

	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.05, -0.05, 0.05);
	glVertex3f(-0.05, -0.05, 0.05);
	glVertex3f(-0.05, -0.05, -0.05);
	glVertex3f(0.05, -0.05, -0.05);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.05, 0.05, -0.05);
	glVertex3f(-0.05, 0.05, -0.05);
	glVertex3f(-0.05, -0.05, -0.05);
	glVertex3f(0.05, -0.05, -0.05);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.05, 0.05, 0.05);
	glVertex3f(-0.05, 0.05, 0.05);
	glVertex3f(-0.05, -0.05, 0.05);
	glVertex3f(0.05, -0.05, 0.05);


	glEnd();
}
void plane() {
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-10, -.05, 10);
	glVertex3f(10, -0.05, 10);
	glVertex3f(10, -0.05, -10);
	glVertex3f(-10, -.05, -10);
	glEnd();
}
class Camera {
public:
	Camera(){
		pfov = 90; pratio = 1; pnear = 0.1; pfar = 3000;

		cameraPosX = 0; cameraPosY = 0; cameraPosZ = 0;

		cameraForwardX = 0.5; cameraForwardY = -0.5; cameraForwardZ = -1.5;

		Radius = sqrt(cameraForwardX*cameraForwardX + cameraForwardY*cameraForwardY + cameraForwardZ * cameraForwardZ);
	}
	void moveForward(GLfloat const distance) {
		cameraPosX -= sin(yawAngle*3.14 / 180)*distance;
		cameraPosZ -= cos(yawAngle*3.14 / 180)*distance;
		
	}
	void moveBack(GLfloat const distance) {
		cameraPosX += sin(yawAngle*3.14 / 180)*distance;
		cameraPosZ += cos(yawAngle*3.14 / 180)*distance;
		
	}
	void moveRight(GLfloat const distance) {
		cameraPosZ -= sin(yawAngle*3.14 / 180)*distance;
		cameraPosX += cos(yawAngle*3.14 / 180)*distance;
	}
	void moveLeft(GLfloat const distance) {
		cameraPosZ += sin(yawAngle*3.14 / 180)*distance;
		cameraPosX -= cos(yawAngle*3.14 / 180)*distance;
	}
	void rotate(GLfloat const xoffset, GLfloat const yoffset) {

		pitchAngle += yoffset*0.03;
		yawAngle += xoffset*0.03;
		// 保证角度在合理范围内
		if (pitchAngle > 89)
			pitchAngle = 89;
		if (pitchAngle < -89)
			pitchAngle = -89;
		if (yawAngle < 0.0f)
			yawAngle += 360.0f;

		cameraForwardX = -sin(yawAngle*3.14/180) * cos(pitchAngle*3.14 / 180)*Radius;
		cameraForwardY = sin(pitchAngle*3.14 / 180)*Radius;
		cameraForwardZ = -cos(yawAngle*3.14 / 180) * cos(pitchAngle*3.14 / 180)*Radius;
	}
	GLfloat getCX() {
		return cameraPosX;
	}
	GLfloat getCY() {
		return cameraPosY;
	}
	GLfloat getCZ() {
		return cameraPosZ;
	}
	GLfloat getFX() {
		return cameraForwardX;
	}
	GLfloat getFY() {
		return cameraForwardY;
	}
	GLfloat getFZ() {
		return cameraForwardZ;
	}
private:
	GLfloat pfov, pratio, pnear, pfar;
	GLfloat cameraPosX, cameraPosY, cameraPosZ;
	GLfloat cameraForwardX, cameraForwardY, cameraForwardZ;
	GLfloat Radius;
	GLfloat pitchAngle, yawAngle;
};
Camera camera;

bool keyPressedStatus[1024]; // 按键情况记录
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keyPressedStatus[key] = true;
		else if (action == GLFW_RELEASE)
			keyPressedStatus[key] = false;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE); // 关闭窗口
	}
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	GLfloat xoffset = 500 - xpos;
	GLfloat yoffset = 500 - ypos;
	camera.rotate(xoffset, yoffset);
}

int main() {
	GLFWwindow *window1;
	if (!glfwInit())
		return -1;
	window1 = glfwCreateWindow(500, 500, "Ortho", NULL, NULL);
	if (!window1)//检查是否初始化
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window1);
	while (!glfwWindowShouldClose(window1))
	{
		glEnable(GL_DEPTH_TEST);
		//glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, 0.1f, 3000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.5, -0.5, -1.5);
		cube();


		glfwSwapBuffers(window1);
		glfwPollEvents();
	}
	glfwTerminate();

	GLFWwindow *window2;
	if (!glfwInit())
		return -1;
	window2 = glfwCreateWindow(500, 500, "Perspective", NULL, NULL);
	if (!window2)//检查是否初始化
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window2);
	while (!glfwWindowShouldClose(window2))
	{
		glEnable(GL_DEPTH_TEST);
		//glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (GLfloat)500 / (GLfloat)500, 0.5f, 10.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.5, -0.5, -1.5);
		cube();

		glfwSwapBuffers(window2);
		glfwPollEvents();
	}
	glfwTerminate();

	GLFWwindow *window3;
	if (!glfwInit())
		return -1;
	window3 = glfwCreateWindow(500, 500, "view_change", NULL, NULL);
	if (!window3)//检查是否初始化
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window3);
	while (!glfwWindowShouldClose(window3))
	{
		glEnable(GL_DEPTH_TEST);
		//glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (GLfloat)500 / (GLfloat)500, 0.1f, 3000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		int Radius = 1;
		float camPosX = sin(clock() / 1000.0)*Radius;
		float camPosZ = cos(clock() / 1000.0)*Radius;
		gluLookAt(camPosX+0.5, -0.5, camPosZ-1.5, 0.5, -0.5, -1.5, 0, 1, 0);
		glTranslatef(0.5, -0.5, -1.5);
		cube();

		glfwSwapBuffers(window3);
		glfwPollEvents();
	}
	glfwTerminate();

	GLFWwindow *window4;
	if (!glfwInit())
		return -1;
	window4 = glfwCreateWindow(1000, 1000, "bonus", NULL, NULL);
	if (!window4)//检查是否初始化
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window4);
	while (!glfwWindowShouldClose(window4))
	{
		glEnable(GL_DEPTH_TEST);
		//glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (GLfloat)1000 / (GLfloat)1000, 0.1f, 3000.0f);

		glfwSetKeyCallback(window4, key_callback);
		glfwSetCursorPosCallback(window4, mouse_move_callback);
		double xpos, ypos;
		glfwSetCursorPos(window4, 500, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if (keyPressedStatus[GLFW_KEY_W])
			camera.moveForward(0.03);
		if (keyPressedStatus[GLFW_KEY_S])
			camera.moveBack(0.03);
		if (keyPressedStatus[GLFW_KEY_A])
			camera.moveLeft(0.03);
		if (keyPressedStatus[GLFW_KEY_D])
			camera.moveRight(0.03);
		gluLookAt(camera.getCX(), camera.getCY(), camera.getCZ(),
			camera.getCX()+camera.getFX(), camera.getCY() + camera.getFY(), camera.getCZ() + camera.getFZ(), 0, 1, 0);
		
		glTranslatef(0.5, -0.5, -1.5);
		cube();
		plane();


		glfwSwapBuffers(window4);
		glfwPollEvents();
	}
	glfwTerminate();
}