#include "Group.h"
#include "MatrixTransform.h"
#include "Sphere.h"
#include "Cube.h"
#include "group.h"

class Robot : public Group{

public:
	Robot(GLint);
	~Robot();
	void draw(glm::mat4);
	void update(int msec);
	void wireFrameMode(bool);
	Sphere* boundSphere;
	Group * robot;
	MatrixTransform * left_Arm;
	MatrixTransform * right_Arm;
	MatrixTransform * left_Leg;
	MatrixTransform * right_Leg;









};