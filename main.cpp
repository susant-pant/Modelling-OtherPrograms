
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>
using namespace std;
using namespace glm;

GLFWwindow *window;
int w, h;
double mouseX, mouseY;

vector<vec2> control;
float cRadius = 0.01f;
int selected = -1;

void render () {
	glEnable (GL_DEPTH_TEST);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Functions for changing transformation matrix
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glTranslatef (0.f, 0.f, 0.f);
	glRotatef (0.f, 0.f, 0.f, 1.f);
	glScalef (1.f, 1.f, 1.f);

	//Functions for changing projection matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (-1, 1, -1, 1, -1, 1);
	//gluPerspective (fov, aspect ratio, near plane, far plane)
	//glFrustum

	//We draw a line on the screen, which gets transformed by the modelview matrix
	glBegin (GL_QUADS); //GL_LINE_STRIP, GL_POINTS, GL_QUADS, etc...
	for (int i = 0; i < control.size(); i++){
		glVertex2f( control[i].x + cRadius, control[i].y + cRadius);
		glVertex2f( control[i].x + cRadius, control[i].y - cRadius);
		glVertex2f( control[i].x - cRadius, control[i].y - cRadius);
		glVertex2f( control[i].x - cRadius, control[i].y + cRadius);
	}
	glEnd ();
}


void keyboard (GLFWwindow *sender, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool canMove = false;

void mouseClick (GLFWwindow *sender, int button, int action, int mods) {
	selected = -1;
	canMove = false;
	if (action == GLFW_PRESS){
		for (int i = 0; i < control.size(); i++){
			if ((abs(control[i].x - mouseX) <= cRadius) && (abs(control[i].y - mouseY) <= cRadius)){
				selected = i;
			}
		}
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (selected == -1)
				control.push_back(vec2(mouseX, mouseY));
			canMove = true;
			cout << selected << endl;
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT){
			if (selected != -1)
				control.erase(control.begin() + selected);
			cout << selected << endl;
		}
	}
}

void mousePos (GLFWwindow *sender, double x, double y) {
	mouseX = (2 * x / w) - 1;
	mouseY = -((2 * y / h) - 1);
	if (selected != -1 && canMove){
		control[selected].x = mouseX;
		control[selected].y = mouseY;
	}
}


int main () {
	if (!glfwInit())
		return 1;

	window = glfwCreateWindow (640, 480, "My Window", NULL, NULL);
	if (!window)
		return 1;

	glfwMakeContextCurrent (window);
	glfwSetKeyCallback (window, keyboard);
	glfwSetMouseButtonCallback (window, mouseClick);
	glfwSetCursorPosCallback (window, mousePos);
	while (!glfwWindowShouldClose (window)) {
		glfwGetFramebufferSize (window, &w, &h);
		glViewport (0, 0, w, h);

		render ();

		glfwSwapBuffers (window);
		glfwPollEvents();
	}

	glfwDestroyWindow (window);
	glfwTerminate();
	return 0;
}

