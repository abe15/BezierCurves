#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include "materials.h"
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstring>
#include <stdio.h>
#include "Window.h"

#define  SPIN_AMOUNT  2.0f

class OBJObject
{
private:
	//std::vector<unsigned int> indices;



	//std::vector<glm::vec3> original_vertices;

	//std::vector<glm::vec3> original_normals;

public:
	GLuint VBO, VAO, EBO, VBO2;
	glm::vec3 change;
	float pointSize;
	std::vector<glm::vec3> vertices;
	std::vector< GLuint > vertexIndices;
	float maxX = -std::numeric_limits<double>::infinity();
	float minX = std::numeric_limits<double>::infinity();
	float maxY = -std::numeric_limits<double>::infinity();
	float minY = std::numeric_limits<double>::infinity();
	float maxZ = -std::numeric_limits<double>::infinity();
	float minZ = std::numeric_limits<double>::infinity();
	float maxAll = -std::numeric_limits<double>::infinity();
	//Material Properties
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shine;
	const float speed = .00001;

	// These variables are needed for the shader program
	
	GLuint uProjection, uModelview, uModel;
	std::vector<glm::vec3> normals;
	OBJObject(const char* filepath);
	glm::mat4 toWorld;
	void parse(const char* filepath);
	void draw(GLuint);
	void spin(float);
	void update();
	void shift_translate(float, float, float);
	void reset();
	void orbit(float);
	void changePointSize(float);
	void scale(float);
	void rotate(glm::vec3, float);
	void toggle(int i);
	void changeAmbience(glm::vec3);
	void changeDiffuse(glm::vec3);
	void changeSpecular(glm::vec3);
	void changeShine(float);
	void followMouse(float mouseX, float mouseY);
	float minValue(float x, float minVal);
	float maxValue(float x, float maxVal);
	float getMax3(float x, float y, float z);


};

#endif
