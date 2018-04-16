#include "sphere.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

Sphere::Sphere()
{
	isInited = false;
	m_vao = 0;
	m_vboVertex = 0;
	m_vboIndex = 0;
	model = glm::mat4(1.0f);
	lats = 50;
	longs = 50;
	shaderId = 0;
	float scale = 1/5.0f;
	int i, j;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	int indicator = 0;
	for (i = 0; i <= lats; i++) {
		double lat0 = glm::pi<double>() * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = glm::pi<double>() * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		for (j = 0; j <= longs; j++) {
			double lng = 2 * glm::pi<double>() * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			vertices.push_back(x * zr0 *scale);
			vertices.push_back(y * zr0 *scale);
			vertices.push_back(z0 *scale);
			indices.push_back(indicator);
			indicator++;

			vertices.push_back(x * zr1*scale);
			vertices.push_back(y * zr1 *scale);
			vertices.push_back(z1*scale);
			indices.push_back(indicator);
			indicator++;
		}
		indices.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);
	}


	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vboVertex);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &m_vboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	numsToDraw = indices.size();

	isInited = true;
}

Sphere::~Sphere()
{

}

void Sphere::init(GLuint vertexPositionID)
{
	//Geode::shaderId = vertexPositionID;
}

void Sphere::cleanup()
{
	if (!isInited) {
		return;
	}
	if (m_vboVertex) {
		glDeleteBuffers(1, &m_vboVertex);
	}
	if (m_vboIndex) {
		glDeleteBuffers(1, &m_vboIndex);
	}
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
	}

	isInited = false;
	m_vao = 0;
	m_vboVertex = 0;
	m_vboIndex = 0;
}

void Sphere::draw(glm::mat4 C)
{
	glm::mat4 transformedModel = model*C;
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "model"), 1, GL_FALSE, &transformedModel[0][0]);
	// draw sphere
	glBindVertexArray(m_vao);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(GL_PRIMITIVE_RESTART_FIXED_INDEX);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);		
	glDrawElements(GL_QUAD_STRIP, numsToDraw, GL_UNSIGNED_INT, NULL);
	

	
}
void Sphere::isBoundOn(bool trigger)
{
	this->wireFrameMode = trigger;
	render = trigger;
}
void Sphere::update()
{

}

