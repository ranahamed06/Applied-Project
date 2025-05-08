
#ifndef TREENODE_H
#define TREENODE_H

#include "CustomVector.h"

// Tree structure for storing possible values during solving
template <typename T>
class TreeNode {
private:
    T data;
    TreeNode* parent;
    CustomVector<TreeNode*> children;

public:
    explicit TreeNode(const T& value) : data(value), parent(nullptr) {}

    ~TreeNode() {
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
    }

    void addChild(TreeNode* child) {
        children.push_back(child);
        child->parent = this;
    }

    TreeNode* getChild(int index) {
        if (index < 0 || index >= children.size()) {
            return nullptr;
        }
        return children[index];
    }

    TreeNode* getParent() const {
        return parent;
    }

    const T& getValue() const {
        return data;
    }

    void setValue(const T& value) {
        data = value;
    }

    int getChildCount() const {
        return children.size();
    }

    void removeChild(int index) {
        if (index < 0 || index >= children.size()) {
            return;
        }

        TreeNode* childToRemove = children[index];
        children.remove(index);
        delete childToRemove;
    }

    void clearChildren() {
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
        children.clear();
    }
};

#endif //TREENODE_H
