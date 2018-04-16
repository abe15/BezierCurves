#include "Cube.h"


Cube::Cube(float w, float h, float d)
{
	Geode::model = glm::mat4(1.0f);

	float verts[] = {
		-0.5*w, 0.5*h, -0.5*d,   1.0 / 3.0, 0.25,
		0.5*w, 0.5*h, -0.5*d,    2.0 / 3.0, 0.25,
		0.5*w, 0.5*h, 0.5*d,     2.0 / 3.0, 0.5,
		-0.5*w, 0.5*h, 0.5*d,    1.0 / 3.0, 0.5,
		-0.5*w, -0.5*h, 0.5*d,   1.0 / 3.0, 0.75,
		0.5*w, -0.5*h, 0.5*d,    2.0 / 3.0, 0.75,
		-0.5*w, -0.5*h, -0.5*d,  1.0 / 3.0, 1.0,
		0.5*w, -0.5*h, -0.5*d,   2.0 / 3.0, 1.0,
		-0.5*w, -0.5*h, -0.5*d,  1.0 / 3.0, 0.0,
		0.5*w, -0.5*h, -0.5*d,   2.0 / 3.0, 0.0,
		-0.5*w, -0.5*h, -0.5*d,  0.0, 0.25,
		-0.5*w, -0.5*h, 0.5*d,   0.0, 0.5,
		0.5*w, -0.5*h, -0.5*d,   1.0, 0.25,
		0.5*w, -0.5*h, 0.5*d,    1.0, 0.5
	};
	int polys[] = {
		0, 3, 1, 1, 3, 2,    // TOP
		3, 4, 2, 2, 4, 5,    // FRONT
		4, 6, 5, 5, 6, 7,    // BOTTOM
		8, 0, 9, 9, 0, 1,    // BACK
		10, 11, 0, 0, 11, 3, // LEFT
		1, 2, 12, 12, 2, 13  // RIGHT
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO2);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(polys), &polys[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Cube::~Cube()
{
//	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
}

void Cube::draw(glm::mat4 C)
{ 
	glm::mat4 transformedModel = C*model;
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "model"), 1, GL_FALSE, &transformedModel[0][0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Cube::update()
{

}

void Cube::spin(float deg)
{
	// If you haven't figured it out from the last project, this is how you fix spin's behavior
	//toWorld = toWorld * glm::rotate(glm::mat4(1.0f), 1.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
}

