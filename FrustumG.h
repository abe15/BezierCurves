
#ifndef _FRUSTUMG_
#define _FRUSTUMG_

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include "Plane.h"
class FrustumG {

private:

	enum {
		TOP = 0, BOTTOM, LEFT,
		RIGHT, NEARP, FARP
	};

public:

	static enum { OUTSIDE, INTERSECT, INSIDE };
	Plane pl[6];
	glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
	float nearD, farD, ratio, angle, tang;
	float nw, nh, fw, fh;

	FrustumG::FrustumG();
	FrustumG::~FrustumG();

	void setCamInternals(float angle, float ratio, float nearD, float farD);
	void setCamDef(glm::vec3 &p, glm::vec3 &l, glm::vec3 &u);
	int pointInFrustum(glm::vec3 &p);
	int sphereInFrustum(glm::vec3 &p, float raio);

	void FrustumG::drawPoints();
	void FrustumG::drawLines();
	void FrustumG::drawPlanes();
	void FrustumG::drawNormals();
};


#endif