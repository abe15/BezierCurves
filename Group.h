#ifndef _GROUP_H
#define	_GROUP_H 

#include "Node.h"


class Group : public Node {
public:
	Group() {};
	Group(Node* Parent, const char* Name);
	~Group();

	//void accept(class NodeVisitor* v);
	void update();
	void draw(glm::mat4 C);
	void SetParentNode(Node* NewParent);
	void AddChildNode(Node* ChildNode);
	//void AddChildNode(Group* ChildNode);
	void RemoveChildNode(Node* ChildNode);

	//const char* GetGroupName(void) const;
	//const size_t CountChildNodes(const bool& RecursiveCount = false) const;
	//void setGroupBackground();

	//int getNodeType();
	std::vector<Node*> m_Children;
private:
	//int nodecount;

	Node* m_Parent;
	const char* m_Name;
	



};


#endif	/* GROUP_H */