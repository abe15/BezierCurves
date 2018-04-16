#include "MatrixTransform.h"




MatrixTransform::MatrixTransform(glm::mat4 M)
{
	this->M = M;
	this->tflag = false;
	this->rflag = false;
	this->sflag = false;
}

MatrixTransform::~MatrixTransform()
{

}

void MatrixTransform::draw(glm::mat4 C) {

	glm::mat4 overall = glm::mat4(1.0f);
	if (this->getScaleFlag())
	{
		overall = glm::scale(glm::mat4(1.0f), this->scale)*overall;

	}
	if (this->getRotateFlag()) {
		//glm::vec3 v(rotate.x, rotate.y, rotate.z);
		//overall = glm::translate(glm::mat4(1.0f), glm::vec3(.15,-.15,0))*overall;
		overall = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(rotate.x, rotate.y, rotate.z))*overall;
		//overall = glm::translate(glm::mait4(1.0f), glm::vec3(-.15, .15, 0))*overall;
	//	overall = glm::rotate(overall, 90.0f, glm::vec3(0,1,0));
	}
	if (this->getTranslateFlag()) { 
		overall = glm::translate(glm::mat4(1.0f), this->translate)*overall;	
	}
	


	for (size_t i = 0; i < m_Children.size(); ++i)
	{
		m_Children[i]->draw(C*overall);
	}

}

/*
void MatrixTransform::accept(class NodeVisitor* v) {
	v->visit(this);
}
*/
void MatrixTransform::setTranslate(glm::vec3 translate)
{
	this->translate = translate;
	this->tflag = true;
}

glm::vec3 MatrixTransform::getTranslate()
{
	return this->translate;
}

bool MatrixTransform::getTranslateFlag()
{
	return this->tflag;
}





void MatrixTransform::setRotate(glm::vec4 rotate)
{
	this->rotate = rotate;
	this->rflag = true;
}

glm::vec4 MatrixTransform::getRotate()
{
	return this->rotate;
}

bool MatrixTransform::getRotateFlag()
{
	return this->rflag;
}

void MatrixTransform::setScale(glm::vec3 scale)
{
	this->scale = scale;
	this->sflag = true;
}

glm::vec3 MatrixTransform::getScale()
{
	return this->scale;
}

bool MatrixTransform::getScaleFlag()
{
	return this->sflag;
}

void MatrixTransform::applyTransform()
{

	if (this->getTranslateFlag()) glTranslatef(this->translate.x, this->translate.y, this->translate.z);
	if (this->getRotateFlag()) glRotatef(this->rotate.x, this->rotate.y, this->rotate.z, this->rotate.w);
	if (this->getScaleFlag()) glScalef(this->scale.x, this->scale.y, this->scale.z);

}

int MatrixTransform::getNodeType() {
	return 2;
}

void MatrixTransform::update()
{








}