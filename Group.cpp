#include "Group.h"





Group::Group(Node* Parent, const char* Name)
	: m_Name(Name)
{
	m_Parent = Parent;

} // Constructor
void Group::draw(glm::mat4 C) {

	for (size_t i = 0; i < m_Children.size(); ++i)
	{
		m_Children[i]->draw(C);
	}

}

Group::~Group(void)
{
	m_Parent = NULL;
	m_Children.clear();
} // Destructor

void Group::AddChildNode(Node* ChildNode)
{
	if (NULL != ChildNode)
	{
		if (NULL != ChildNode->GetParentNode())
		{
			ChildNode->SetParentNode(this);
		}
		m_Children.push_back(ChildNode);
	}
};

void Group::RemoveChildNode(Node* ChildNode)
{
	if (NULL != ChildNode && !m_Children.empty())
	{
		for (size_t i = 0; i < m_Children.size(); ++i)
		{
			if (m_Children[i] == ChildNode)
			{
				m_Children.erase(m_Children.begin() + i);
				break; // break the for loop
			}
		}
	}
}; 
void Group::update(void)
{
	if (!m_Children.empty())
	{
		for (size_t i = 0; i < m_Children.size(); ++i)
		{
			if (NULL != m_Children[i])
			{
				m_Children[i]->update();
			}
		}
	}
} // Update()
/*
const char* Group::GetGroupName(void) const
{
	return(m_Name);
}; // GetNodeName()


int Group::getNodeType() {
	return 1;
}*/