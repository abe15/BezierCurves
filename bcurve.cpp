#include "bcurve.h"

BCurve::BCurve(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d)
{
	points[1] = a;
	points[2] = b;
	points[3] = c;
	points[4] = d;
}

BCurve::~BCurve()
{
}

void BCurve::Init()
{
	
}

void BCurve::ComputeBezier(glm::vec3 &dest,const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, const glm::vec3 &d, const float t)
{
	glm::vec3 ab, bc, cd, abbc, bccd;
	Lerp(ab, a, b, t);
	Lerp(bc, b, c, t);
	Lerp(cd, c, d, t);
	Lerp(abbc, ab, bc, t);
	Lerp(bccd, bc, cd, t);
	Lerp(dest, abbc, bccd, t);
}

void BCurve::DrawCPoints()
{
	glColor3f(1.0 , 0, 0);
	glPointSize(10.0);
	glBegin (GL_POINTS);
	for(int i = 1; i < 5; ++i)
	{
		glVertex3f (points[i].x, points[i].y,points[i].z);
	}
	glEnd();
	
}

void BCurve::DrawCurve(float r, float g, float b)
{

	
	
	glBegin(GL_LINE_STRIP);
	glColor3f(r, g, b);
	for (int i=0; i< 1000; ++i)
	{	
		float t  = static_cast<float>(i)/999.0f;


		ComputeBezier(points[0], points[1], points[2], points[3], points[4], t);
		glVertex2f(points[0].x, points[0].y);
	}
	glEnd();
	

}
