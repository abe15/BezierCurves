#ifndef __MATRIXTRANSFORM_H_INCLUDED__
#define	__MATRIXTRANSFORM_H_INCLUDED__

#include "Group.h"


class MatrixTransform : public Group {
public:
	MatrixTransform(glm::mat4 M);
	~MatrixTransform();
	void draw(glm::mat4 C); 
	void update();
	//void accept(class NodeVisitor* v);

	void setTranslate(glm::vec3 translate);
	glm::vec3 getTranslate();
	bool getTranslateFlag();

	void setRotate(glm::vec4 rotate);
	glm::vec4 getRotate();
	bool getRotateFlag();

	void setScale(glm::vec3 scale);
	glm::vec3 getScale();
	bool getScaleFlag();

	void applyTransform();

	int getNodeType();

private:
	glm::mat4 M;
	glm::vec3 translate;bool tflag;
	glm::vec4 rotate;bool rflag;
	glm::vec3 scale;bool sflag;
};


#endif	/* TRANSFORM_H */