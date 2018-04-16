#ifndef _BCOMP_H_
#define _BCOMP_H_
#define GLFW_INCLUDE_GLEXT

//#include "bcurve.h"
#include <vector>
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


class BComp {

	
private:
	
	int curveCount;  //how many bezier curves in this path?
	int num = 10;
public:
	BComp();
    const int SEGMENTS_PER_CURVE = 150;
	const int SEGMENT_COUNT = 10;
	void  GetDrawingPoints0();
	const float MINIMUM_SQR_DISTANCE = 0.01f;
	glm::vec3 CalculateBezierPoint(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	// This corresponds to about 172 degrees, 8 degrees from a traight line
	const float DIVISION_THRESHOLD = -0.99f;
	void Draw2();
	GLuint VAO, VBO;
	std::vector < glm::vec3 > * controlPoints;
	std::vector < glm::vec3 > * control_Points;
	std::vector<glm::vec3>* segmentPoints;
	std::vector<glm::vec3> *drawingPoints;
	void Interpolate(float);
	void setUp();
	void Draw();
	void Draw3();
	int getMax();
	int r, g, k;


};
#endif