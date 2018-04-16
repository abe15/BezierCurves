#ifndef SPHERE_H
#define SPHERE_H
#include "Geode.h"
#include <GL/glew.h>

class Sphere: public Geode
{
public:
	Sphere();
	~Sphere();
	void init(GLuint vertexPositionID);
	void cleanup();
	void draw(glm::mat4 C);
	void update(void);
	void isBoundOn(bool);
	//void doDraw(bool);
	
private:
	int lats, longs;
	bool isInited;
	GLuint m_vao, m_vboVertex, m_vboIndex;
	int numsToDraw;
	bool wireFrameMode = false;
	bool render = true;
};

#endif // SPHERE_H