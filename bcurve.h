
#ifndef _BCURVE_H_
#define _BCURVE_H_
#define GLFW_INCLUDE_GLEXT

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "Cube.h"

#include <cstdlib>
#include <ctime> 
#include <math.h>

class BCurve
{
public:

	//class constructor
	BCurve(glm::vec3 a, glm::vec3 b, glm::vec3 c,  glm::vec3 d);
	glm::vec3 points[4];
	//class destructor
	~BCurve();

	////////////////////////////////
	//Curve generation functions
	////////////////////////////////
	inline void Lerp(glm::vec3& dest, const glm::vec3 a, const glm::vec3 b, const float t)
	{
		 dest.x = a.x + (b.x-a.x)*t;
		 dest.y = a.y + (b.y-a.y)*t;
		 dest.z = a.z + (b.z - a.z)*t;
	}

	void Init(); //generate point coords here
	void ComputeBezier(glm::vec3 &point,const glm::vec3& a, const glm::vec3 &b, const glm::vec3 &c, const glm::vec3 &d, const float t);
	void DrawCPoints(); //draw the control points
	void DrawCurve(float r, float g, float b); 

	
};

extern BCurve *gBCurve;

#endif