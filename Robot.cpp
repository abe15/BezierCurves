#include "Robot.h"


Robot::Robot(GLint shaderProgram)
{
	robot = new Group();
	boundSphere = new Sphere();
	MatrixTransform *bodyHolder = new MatrixTransform(glm::mat4(1.0f));
	Cube* body = new Cube(.2, .4, .1);//body
	body->setShaderid(shaderProgram);
	//bodyHolder->setTranslate(glm::vec3(0, .5, 0));
	//bodyHolder->setScale(glm::vec3(5, 5, 5));
	bodyHolder->AddChildNode(body);
	robot->AddChildNode(bodyHolder);


	boundSphere->setShaderid(shaderProgram);
	MatrixTransform *scale1 = new MatrixTransform(glm::mat4(1.0f));
	scale1->setScale(glm::vec3(3.4, 3.4, 3.4));
	scale1->AddChildNode(boundSphere);	
	robot->AddChildNode(scale1);



	MatrixTransform *rotateArmLeft = new MatrixTransform(glm::mat4(1.0f));
	left_Arm = &(*rotateArmLeft);
	Cube* leftArm = new Cube(.1, .1, .3);
	leftArm->setShaderid(shaderProgram);
	rotateArmLeft->setTranslate(glm::vec3(-.15, .15, 0));
	rotateArmLeft->AddChildNode(leftArm);
	bodyHolder->AddChildNode(rotateArmLeft);

	MatrixTransform *rotateArmRight = new MatrixTransform(glm::mat4(1.0f));
	right_Arm = &(*rotateArmRight);
	Cube* rightArm = new Cube(.1, .1, .3);
	rightArm->setShaderid(shaderProgram);
	rotateArmRight->setTranslate(glm::vec3(.15, .15, 0));
	rotateArmRight->AddChildNode(rightArm);
	bodyHolder->AddChildNode(rotateArmRight);

	MatrixTransform *rotateLegLeft = new MatrixTransform(glm::mat4(1.0f));
	left_Leg = &(*rotateLegLeft);
	Cube* leftLeg = new Cube(.1, .1, .3);//
	leftLeg->setShaderid(shaderProgram);
	rotateLegLeft->setTranslate(glm::vec3(-.1, -.2, 0));
	rotateLegLeft->AddChildNode(leftLeg);
	bodyHolder->AddChildNode(rotateLegLeft);

	MatrixTransform *rotateLegRight = new MatrixTransform(glm::mat4(1.0f));
	right_Leg = &(*rotateLegRight);
	Cube* rightLeg = new Cube(.1, .1, .3);//
	rightLeg->setShaderid(shaderProgram);
	rotateLegRight->setTranslate(glm::vec3(.1, -.2, 0));
	rotateLegRight->AddChildNode(rightLeg);
	bodyHolder->AddChildNode(rotateLegRight);

	MatrixTransform *rotateHead = new MatrixTransform(glm::mat4(1.0f));
	Sphere* head = new Sphere();
	head->setShaderid(shaderProgram);
	rotateHead->setTranslate(glm::vec3(0, .2, 0));
	rotateHead->AddChildNode(head);
	bodyHolder->AddChildNode(rotateHead);


	

}


void Robot::draw(glm::mat4 C)
{
	robot->draw(C);
	//robot->draw(glm::mat4(1.0f));

}
void Robot::wireFrameMode(bool trigger)
{
	this->boundSphere->isBoundOn(trigger);

}

void Robot::update(int msec){

	//left_Arm->setTranslate(glm::vec3(.15, -.15, 0));



	left_Arm->setRotate(glm::vec4(0, msec,0,1));
	//left_Arm->setTranslate(glm::vec3(-.15, .15, 0));

}