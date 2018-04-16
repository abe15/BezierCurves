#define _CRT_SECURE_NO_WARNINGS
#include "OBJObject.h"

#include <cmath>
OBJObject::OBJObject(const char *filepath)
{
	toWorld = glm::mat4(1.0f);

	/**/
	ambient = glm::vec3 (0.0215f, 0.1745f, 0.0215f);
	diffuse = glm::vec3(0.07568f, 0.61424, 0.07568);
	specular = glm::vec3(0.633, 0.727811, 0.633);
	shine = 128 * 0.6;

	parse(filepath);
	change.x = 0;
	change.y = 0;
	change.z = 0;
	pointSize = 5.0f;

	toWorld = glm::mat4(1.0f);
	maxAll = getMax3(maxX, maxY, maxZ);
	scale(1 / maxAll);

	float xVal = ((minX + maxX) / 2) / maxAll;
	float yVal = ((minY + maxY) / 2) / maxAll;
	float zVal = ((minZ + maxZ) / 2) / maxAll;
	shift_translate(-xVal, -yVal, -zVal);

	for (int i = 0; i < vertices.size();i++)
	{
		vertices[0].x = vertices[0].x / maxAll;
		vertices[0].y = vertices[0].y / maxAll;
		vertices[0].z = vertices[0].z / maxAll;

	}


	// Create array object and buffers. Remember to delete your buffers when the object is destroyed!
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO2);

	// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
	// Consider the VAO as a container for all your buffers.
	glBindVertexArray(VAO);

	// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
	// you want to draw, such as vertices, normals, colors, etc.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
	// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer
	//
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);




	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		sizeof(GLfloat) * 3, // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
					 // Enable the usage of layout location 0 (check the vertex shader to see what this is)
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*vertexIndices.size(), &vertexIndices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(1);


	//glDisableVertexAttribArray(0);

	// We've sent the vertex data over to OpenGL, but there's still something missing.
	// In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.


	// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbind the VAO now so we don't accidentally tamper with it.
	// NOTE: You must NEVER unbind the element array buffer associated with a VAO!
	glBindVertexArray(0);
	

}

void OBJObject::parse(const char *filepath)
{
	//TODO parse the OBJ file
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data


	FILE* fp;
	fopen_s(&fp, filepath, "rb");

	if (fp == NULL) { std::cerr << "error loading file" << endl; exit(-1); }  // just in case the file can't be found

	while (1)
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(fp, "%s", lineHeader);
		if (res == EOF)
			break; // End of File quit loop.


		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			float r, g, b;
			fscanf(fp, "%f %f %f %f %f %f\n", &vertex.x, &vertex.y, &vertex.z, &r, &g, &b);
			vertices.push_back(vertex);

			minX = minValue(vertex.x, minX);
			minY = minValue(vertex.y, minY);
			minZ = minValue(vertex.z, minZ);

			maxX = maxValue(vertex.x, maxX);
			maxY = maxValue(vertex.y, maxY);
			maxZ = maxValue(vertex.z, maxZ);


		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normal = glm::normalize(normal);
			normal.x = glm::abs(normal.x);
			normal.y = glm::abs(normal.y);
			normal.z = glm::abs(normal.z);
			normals.push_back(normal);
			//original_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			GLuint vertexIndex[3], normalIndex[3];
			int matches = fscanf(fp, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return;
			}
			vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[1] - 1);
			vertexIndices.push_back(vertexIndex[2] - 1);
			//normalIndices.push_back(normalIndex[0]);
			//normalIndices.push_back(normalIndex[1]);
			//normalIndices.push_back(normalIndex[2]);

		}
	}

	// scale model to 2x2x2 cube





}

void OBJObject::draw(GLuint shaderProgram)
{

	// Calculate the combination of the model and view (camera inverse) matrices
	glm::mat4 modelview = Window::V * toWorld;
	// We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
	// Consequently, we need to forward the projection, view, and model matrices to the shader programs
	// Get the location of the uniform variables "projection" and "modelview"
	uProjection = glGetUniformLocation(shaderProgram, "projection");
	uModelview = glGetUniformLocation(shaderProgram, "modelview");
	uModel = glGetUniformLocation(shaderProgram, "model");

	//GLint objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");
	//GLint lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
	//glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	//glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	/*OBJECT PROPERTIES*/
	GLint matAmbientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(shaderProgram, "material.specular");
	GLint matShineLoc = glGetUniformLocation(shaderProgram, "material.shininess");

	glUniform3f(matAmbientLoc, ambient.x, ambient.y, ambient.z);
	glUniform3f(matDiffuseLoc, diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(matSpecularLoc, specular.x, specular.y, specular.z);
	glUniform1f(matShineLoc, shine);

	/*
	GLfloat timeValue = glfwGetTime();
	GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
	GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	//glUseProgram(shaderProgram);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
	// Now send these values to the shader program
	*/
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
	glUniformMatrix4fv(uModel, 1, GL_FALSE, &toWorld[0][0]);


	// Now draw the cube. We simply need to bind the VAO associated with it.
	glBindVertexArray(VAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
	//vertexIndices.size()-5
	glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
	// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
	glBindVertexArray(0);
}

void OBJObject::spin(float deg)
{
	glm::vec3 orig(change.x, change.y, change.z);
	shift_translate(-change.x, -change.y, -change.z);
	this->toWorld = glm::rotate(this->toWorld, deg / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.f));
	shift_translate(orig.x, orig.y, orig.z);

}


void OBJObject::update()
{

	//this->spin(SPIN_AMOUNT);

}

void OBJObject::shift_translate(float x, float y, float z)
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	this->toWorld = translate*this->toWorld;

	//this->toWorld = glm::translate(this->toWorld, glm::vec3(x, y, z));
	change.x += x;
	change.y += y;
	change.z += z;
}

void OBJObject::followMouse(float mouseX, float mouseY)
{
	float Dx = mouseX - change.x;
	float Dy = mouseY - change.y;

	float Cx = Dx;
	float Cy = Dy;

	//float Cx = change.x + Dx / sqrt(Dx*Dx + Dy*Dy) * speed * .0001;
	///float Cy = change.y + Dy / sqrt(Dx*Dx + Dy*Dy) * speed * .0001;

	shift_translate(Cx, Cy, 0);

}

void OBJObject::reset()
{
	change.x = 0;
	change.y = 0;
	change.z = 0;
	toWorld = glm::mat4(1.0f);
	float xVal = (minX + maxX) / 2;
	float yVal = (minY + maxY) / 2;
	float zVal = (minZ + maxZ) / 2;
	shift_translate(-xVal, -yVal, -zVal);
}


void OBJObject::orbit(float deg)
{
	glm::vec3 orig(change.x, change.y, change.z);
	shift_translate(-change.x, -change.y, -change.z);
	glm::mat4 t = glm::rotate(glm::mat4(1.0f), deg / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.f));
	this->toWorld = t*this->toWorld;
	shift_translate(orig.x, orig.y, orig.z);

}

void OBJObject::rotate(glm::vec3 rotAxis, float rotAngle)
{
	glm::vec3 orig(change.x, change.y, change.z);
	shift_translate(-change.x, -change.y, -change.z);
	glm::mat4 t = glm::rotate(glm::mat4(1.0f), rotAngle / 180.0f * glm::pi<float>(), rotAxis);
	this->toWorld = t*this->toWorld;
	shift_translate(orig.x, orig.y, orig.z);


}

float OBJObject::minValue(float x, float minVal)
{
	return ((x < minVal) ? x : minVal);

}

float OBJObject::maxValue(float x, float maxVal)
{
	return ((x > maxVal) ? x : maxVal);

}





void OBJObject::toggle(int i)
{/*
	if (i == 0) {
		ambient = emerald_amb;
		diffuse = emerald_diff;
		specular = emerald_spec;
		shine = emerald_shine;
	}
	else if (i == 1) {
		ambient = jade_amb;
		diffuse = jade_diff;
		specular = jade_spec;
		shine = jade_shine;
	}
	else if (i == 2) {

		ambient = obsidian_amb;
		diffuse = obsidian_diff;
		specular = obsidian_spec;
		shine = obsidian_shine;

	}
	else if (i == 3)
	{

		ambient = pearl_amb;
		diffuse = pearl_diff;
		specular = pearl_spec;
		shine = pearl_shine;
	}
	else if (i == 4)
	{

		ambient = ruby_amb;
		diffuse = ruby_diff;
		specular = ruby_spec;
		shine = ruby_shine;
	}
	else if (i == 5)
	{

		ambient = turquoise_amb;
		diffuse = turquoise_diff;
		specular = turquoise_spec;
		shine = turquoise_shine;
	}
	else if (i == 6)
	{

		ambient = brass_amb;
		diffuse = brass_diff;
		specular = brass_spec;
		shine = brass_shine;
	}
	else if (i == 7)
	{

		ambient = bronze_amb;
		diffuse = bronze_diff;
		specular = bronze_spec;
		shine = bronze_shine;
	}
	else if (i == 8)
	{

		ambient = chrome_amb;
		diffuse = chrome_diff;
		specular = chrome_spec;
		shine = chrome_shine;
	}
	else if (i == 9)
	{

		ambient = copper_amb;
		diffuse = bronze_diff;
		specular = copper_spec;
		shine = copper_shine;
	}
	else if (i == 10)
	{

		ambient = gold_amb;
		diffuse = gold_diff;
		specular = gold_spec;
		shine = gold_shine;
	}
	else if (i == 11)
	{

		ambient = silver_amb;
		diffuse = silver_diff;
		specular = silver_spec;
		shine = silver_shine;
	}
	else if (i == 12)
	{

		ambient = black_plastic_amb;
		diffuse = black_plastic_diff;
		specular = black_plastic_spec;
		shine = black_plastic_shine;
	}
	else if (i == 13)
	{

		ambient = cyan_plastic_amb;
		diffuse = cyan_plastic_diff;
		specular = cyan_plastic_spec;
		shine = cyan_plastic_shine;
	}
	else if (i == 14)
	{

		ambient = green_plastic_amb;
		diffuse = green_plastic_diff;
		specular = green_plastic_spec;
		shine = green_plastic_shine;
	}
	else if (i == 15)
	{

		ambient = red_plastic_amb;
		diffuse = red_plastic_diff;
		specular = red_plastic_spec;
		shine = red_plastic_shine;
	}
	else if (i == 16)
	{

		ambient = white_plastic_amb;
		diffuse = white_plastic_diff;
		specular = white_plastic_spec;
		shine = white_plastic_shine;
	}
	else if (i == 17)
	{

		ambient = yellow_plastic_amb;
		diffuse = yellow_plastic_diff;
		specular = yellow_plastic_spec;
		shine = yellow_plastic_shine;
	}
	else if (i == 18)
	{

		ambient = black_rubber_amb;
		diffuse = black_rubber_diff;
		specular = black_rubber_spec;
		shine = black_rubber_shine;
	}
	else if (i == 19)
	{

		ambient = cyan_rubber_amb;
		diffuse = cyan_rubber_diff;
		specular = cyan_rubber_spec;
		shine = cyan_rubber_shine;
	}
	else if (i == 20)
	{

		ambient = green_rubber_amb;
		diffuse = green_rubber_diff;
		specular = green_rubber_spec;
		shine = green_rubber_shine;
	}
	else if (i == 21)
	{

		ambient = red_rubber_amb;
		diffuse = red_rubber_diff;
		specular = red_rubber_spec;
		shine = red_rubber_shine;
	}

	*/
}



void OBJObject::changePointSize(float amount)
{
	this->pointSize *= amount;

}

void OBJObject::scale(float amount)
{
	glm::vec3 orig(change.x, change.y, change.z);
	shift_translate(-change.x, -change.y, -change.z);
	glm::mat4 sca = glm::scale(glm::mat4(1.0f), glm::vec3(amount, amount, amount));
	this->toWorld = sca*this->toWorld;
	shift_translate(orig.x, orig.y, orig.z);
}


void OBJObject::changeAmbience(glm::vec3 amb)
{

	this->ambient = amb;

}
void OBJObject::changeDiffuse(glm::vec3 dif)
{
	this->diffuse = dif;
}
void OBJObject::changeSpecular(glm::vec3 spec) {

	this->specular = spec;
}
void OBJObject::changeShine(float shiney) {
	this->shine = shiney;
}

float OBJObject::getMax3(float x, float y, float z)
{
	float max = x;

	if (max < y) {
		max = y;
	}

	if (max < z) {
		max = z;
	}
	return max;



}