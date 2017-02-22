
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;


GLFWwindow *window;
int w, h;
double mouseX, mouseY;


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
	glBegin (GL_LINES); //GL_LINE_STRIP, GL_POINTS, GL_QUADS, etc...
	glColor3f (1.0f, 0.0f, 0.0f);
	glVertex2f (-0.5f, 0.0f);
	glColor3f (0.0f, 1.0f, 0.0f);
	glVertex2f (0.5f, 0.0f);
	glEnd ();
}

void keyboard (GLFWwindow *sender, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouseClick (GLFWwindow *sender, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		cout << mouseX << ' ' << mouseY << '\n';
}

void mousePos (GLFWwindow *sender, double x, double y) {
	mouseX = x;
	mouseY = y;
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

