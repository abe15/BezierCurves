#include "Geode.h"






// Initilaize vertex array
Geode::Geode() {
//	setVCount(count);

	this->is_animation = false;
	shaderId = 0;
	//this->state = new State();
}

/*void Geode::setVCount(const int count)
{
	this->vcount = count;

	//InitializeVerticesVector();

}
/*
void Geode::InitializeVerticesVector()
{
	//Vertex v[this->vcount];this->vertex=v;  
	//this->vertex = (Vertex*)malloc(sizeof(Vertex)*(this->vcount));
}
*/
// Destructor
Geode::~Geode(void)
{
	m_Parent = NULL;
	//setVCount(0);
}


/*

// Get current vertex count
int Geode::getVCount()
{
	return this->vcount;
}

void Geode::addVertexCoordinate(int pos, vr::Vec3 v)
{
	this->vertex[pos].setVertex(v);
}

vr::Vec3 Geode::getVertexCoordinate(int pos)
{
	return this->vertex[pos].getVertex();
}

void Geode::setMaterial(int pos, vr::AC3DLoader::Material m)
{
	this->vertex[pos].setMaterial(m);
}*/
/*
vr::AC3DLoader::Material Geometry::getMaterial(int pos)
{
	return this->vertex[pos].getMaterial();
}
*/
/*
void Geode::setNormal(int pos, const Vec3 n)
{
	this->vertex[pos].setNormal(n);
}
Vec3 Geode::getNormal(int pos)
{
	return this->vertex[pos].getNormal();
}

void Geode::setTextureCoordinate(int pos, const Vec2 tc)
{
	this->vertex[pos].setTextureCoordinate(tc);
}

Vec2 Geode::getTextureCoordinate(int pos)
{
	return this->vertex[pos].getTextureCoordinate();
}
/*
void Geode::setState(State* state)
{
	this->state = state;
}

State Geometry::getState()
{
	return *(this->state);
}

int Geode::getNodeType()
{
	return 3;
}

void Geode::setAnimation(bool flag)
{
	this->is_animation = flag;
}

bool Geode::getAnimation()
{
	return this->is_animation;
}
/*
void Geode::setVertexBuffer()
{

	this->vertices = (GLfloat*)malloc(sizeof(GLfloat)*(this->vcount) * 3);
	this->colors = (GLfloat*)malloc(sizeof(GLfloat)*(this->vcount) * 3);
	this->normals = (GLfloat*)malloc(sizeof(GLfloat)*(this->vcount) * 3);
	this->texturecs = (GLfloat*)malloc(sizeof(GLfloat)*(this->vcount) * 2);

	glm::vec3 vertex;
	glm::vec3 normal;
	glm::vec2 texturec;
	glm::vec4 col;
	int j = 0;int k = 0;
	for (int i = 0;i<this->vcount;i++) {
		vertex = this->vertex[i].getVertex();
		normal = this->getNormal(i);
		texturec = this->getTextureCoordinate(i);
		col = this->getMaterial(i).diffuse;
		this->vertices[j] = (GLfloat)vertex.x;this->colors[j] = (GLfloat)col.x;this->normals[j] = (GLfloat)normal.x;j++;
		this->vertices[j] = (GLfloat)vertex.y;this->colors[j] = (GLfloat)col.y;this->normals[j] = (GLfloat)normal.y;j++;
		this->vertices[j] = (GLfloat)vertex.z;this->colors[j] = (GLfloat)col.z;this->normals[j] = (GLfloat)normal.z;j++;

		this->texturecs[k] = (GLfloat)texturec.x;k++;
		this->texturecs[k] = (GLfloat)texturec.y;k++;



	}
	
}
*/

/*
void Geode::draw(glm::mat4 C)
{

	//this->getState().apply();

	//this->getState().appyTexture();

	//this->getState().appyMaterial();

	//if (this->getAnimation()) {

	//}

	//setVertexBuffer();

//	glVertexPointer(3, GL_FLOAT, 0, this->vertices);
	//glColorPointer(3, GL_FLOAT, 0, this->colors);
//	glNormalPointer(GL_FLOAT, 0, this->normals);
//	glTexCoordPointer(2, GL_FLOAT, 0, this->texturecs);
//	glDrawArrays(GL_TRIANGLES, 0, this->vcount);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glFlush();
	//glFinish();

}*/