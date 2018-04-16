#ifndef _GEODE_H_
#define	_GEODE_H_ 

#include "Node.h"

class Geode : public Node {
public:
	
	Geode();
	~Geode();

	//int getVCount();

	virtual void update(void) = 0;
	virtual void draw(glm::mat4 C)=0;
	
	//int getNodeType();
	
	//void setAnimation(bool flag);
	//bool getAnimation();
	glm::mat4 model;

private:
	//void setVCount(const int count);
	//void InitializeVerticesVector();

	Geode* m_Parent;
	//State* state;
	const char* m_Name;

	unsigned int vcount;
	unsigned int ccount;
	

	//Vertex* vertex;

	//GLfloat* vertices;
	//GLfloat* colors;
	//GLfloat* normals;
	//GLfloat* texturecs;

	bool is_animation;



};


#endif	/* GEODE_H */