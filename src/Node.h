#pragma once

#include <NodeType.h>
#include <vector>

class Node
{
public:
    Node(void) : mType(kNodeType_Undefined), mParent(nullptr) {}
    Node(eNodeType inNodeType) : mType(inNodeType), mParent(nullptr) {}
    virtual ~Node(void)
    {
        for(Node*& child : mChildren)
        {
            delete child;
        }
        mChildren.clear();
    }

    inline eNodeType GetType(void) const { return mType; }
    inline Node* GetParent(void) const { return mParent; }
    inline void SetParent(Node* inNode) { mParent = inNode; }
    std::vector<Node*>& GetChildren(void) { return mChildren; }
    void InsertNode(Node* inNode) { mChildren.push_back(inNode); inNode->SetParent(this); }

protected:
    Node(const Node& other) = delete;
    Node& operator=(const Node& other) = delete;

    eNodeType mType;

    std::vector<Node*> mChildren;
    Node* mParent;
};
