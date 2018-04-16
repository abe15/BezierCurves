#ifndef _node_h_
#define _node_h_ 


#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>




class Node
{
public:
	Node(Node* Parent = NULL, const char* Name = "noname");
	~Node(void);
	std::vector<Node*> m_Children;
	//virtual void accept(class NodeVisitor* v) = 0;
	GLint shaderId;
	void setShaderid(GLint);
	virtual void update(void)=0;

	Node* GetParentNode(void) const;
	void SetParentNode(Node* NewParent);

	std::vector<Node*>* getChildNodes();

//	void AddChildNode(Node* ChildNode);
	//void RemoveChildNode(Node* ChildNode);

	void setNodeName(const char* name);
	const char* GetNodeName(void) const;
	const size_t CountChildNodes(const bool& RecursiveCount = false) const;


	//const bool IsRootNode(void) const = 0;

	Node* GetChildNodeByName(const char* SearchName);

	void setColor(int col);
	int getColor();

    virtual void draw(glm::mat4 C)=0;

private:
	Node* m_Parent;
	const char* m_Name;
	
	int* color;
	


}; // class Node

#endif