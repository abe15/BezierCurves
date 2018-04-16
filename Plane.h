#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>


#ifndef _PLANE_
#define _PLANE_


class Plane  
{

public:

	glm::vec3 normal,point;
	float d;


	Plane::Plane( glm::vec3 &v1,  glm::vec3 &v2,  glm::vec3 &v3);
	Plane::Plane(void);
	Plane::~Plane();

	void set3Points( glm::vec3 &v1,  glm::vec3 &v2,  glm::vec3 &v3);
	void setNormalAndPoint(glm::vec3 &normal, glm::vec3 &point);
	void setCoefficients(float a, float b, float c, float d);
	float distance(glm::vec3 &p);

	void print();

};


#endif