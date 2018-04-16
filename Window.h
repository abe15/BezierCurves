#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#define GLFW_INCLUDE_GLEXT

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "Cube.h"
//#include "OBJObject.h"
#include "shader.h"
#include <vector>
#include "Node.h"
#include "Camera.cpp"
#include "Geode.h"
#include "SOIL.h"
#include "Sphere.h"
#include "OBJObject.h"
#include "MatrixTransform.h"
#include "Group.h"
#include "Robot.h"
#include "FrustumG.h"
#include "bcomp.h"
//#include "MatrixTransform.h"


//#include "MatrixTransform.h"

class Window
{


public:
	static int width;
	static int height;
	static glm::mat4 P; // P for projection
	static glm::mat4 V; // V for view
	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback(GLFWwindow* window);
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static  glm::vec3 trackBallMapping(double x, double y);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void scrollback(GLFWwindow* window, double x, double y);
	static bool checkClicked(double x, double y);
	static glm::vec3 reverse(double x, double y);
	static void do_movement();
    static GLuint loadCubemap(std::vector<const GLchar*> faces);
	static GLuint loadTexture(GLchar* path);

};



#endif
