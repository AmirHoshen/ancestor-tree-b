//
// Created by miros on 17/04/2020.
//

#include <iostream>
#include "FamilyTree.hpp"
using namespace family;

/**
 * add a father for the given name node if exists if not throw an exception.
 * @param name the node we look for in the tree.
 * @param father the father of name(node) we want to add.
 * @return the father into the tree.
 */
Tree& Tree::addFather(string name, string father)
{
    Node* tmp = findNode(_root,name);
    if(tmp == NULL)throw runtime_error("This name is not a member of this ancestor tree\n");
    add(this->_root, name, father, true);
    return *this;
}

/**
 * add a mother for the given name node if exists if not throw an exception.
 * @param name the node we look for in the tree.
 * @param mother the mother of the name(node) we want to add.
 * @return the mother into the tree.
 */
Tree& Tree::addMother(string name, string mother)
{
    Node* tmp = findNode(_root,name);
    if(tmp == NULL)throw runtime_error("This name is not a member of this ancestor tree\n");
    add(this->_root, name, mother, false);
    return *this;
};

/**
 * print the tree using a help method printTree.
 */
void Tree::display()
{
    printTree(_root);
}

/**
 * receiving the ancestor tree root and printing the tree.
 * if he is null then the tree is empty
 * @param root of the tree.
 */
void Tree::printTree(Node* root)
{
    if(root != NULL){
        if(root->getFather()!= NULL)
        {
            printTree(root->getFather());
        }
        cout<< root->getName()<< " ";
        if(root->getMother()!= NULL)
        {
            printTree(root->getMother());
        }

    }else{
        throw runtime_error("The tree is empty!!\n");
    }
}

/*Return the level of a given string value in the tree*/
/**
 * source code from: https://www.youtube.com/watch?v=IJCg_jxOM_Q
 * level of the root start from 1.
 * using this method finds out what depth of the node we look for.
 * @param node start looking from this given node.
 * @param name the node we are looking for in the tree.
 * @return the depth of the node who's name we looked for in the tree.
 */
int Tree::getLevel(Node *node, string name)
{
    Node* tmp = findNode(node, name);
    if(tmp == NULL)throw runtime_error("This name is not a memeber of the ancestor tree\n");
    return getLevelUtil(node, name,1);
}

/*Help method for getLevel*/
/**
 * gets the level of the name we look for in the tree.
 * @param node the root node.
 * @param name the node depth we look for.
 * @param level the level of that name node we looked for.
 * @return the level he's at.
 */
int Tree::getLevelUtil(Node *node, string name, int level)
{
    if(node == NULL) return 0;
    if(node->getName() == name) return level;
    int downlevel = getLevelUtil(node->getFather(),name, level+1);
    if(downlevel != 0) return downlevel;
    downlevel = getLevelUtil(node->getMother(),name, level+1);
    return downlevel;
}

/**
 *given a name this method should return the relation of this node to the root.
 * @param name the node name relation to the root we are looking for.
 * @return (father/mother, grandfather/grandmother, great-grandfather/great-grandmother, ..etc.)
 */
string Tree::relation(string name)
{
    //omer code here..
    return "";
}

/**
 * given a relation string method should return the name of the node who's in this relation.
 * @param relation - father/mother , grandfather/grandmother , great-grandfather/great-grandmother, ..etc.
 * @return string the name of this node who's associated with this given relation.
 */
string Tree::find(string relation)
{

    return "";
}

/**
 * remove a tree(if root is given, except for the root) or a subtree from the tree.
 * @param name
 */
void Tree::remove(string name)
{
    if(_root->getName() == name){
        if(_root->getFather() != NULL){

        }else if (_root->getMother() != NULL){

        }else throw runtime_error("The root: "+_root->getName()+" cannot be deleted\n");
    }
    Node* tmp = findNode(_root, name);
    if(tmp == NULL)return;
    deleteSubTree(tmp);

}

/**
 * Help method for remove method deleting a subtree from ancestor tree.
 * @param root the ancestor tree root.
 */
void Tree::deleteSubTree(Node* root){
    if(root == NULL) return;
    //deleting all subtree of the node.
    deleteSubTree(root->getFather());
    deleteSubTree(root->getMother());

    //then delete the root node of this subtree.
    cout<<"\n Deleting node: "<<root->getName()<<endl;
    free(root);
}

/**
 * Given a name to look for in the tree and a root node to start from,
 * the method returns the name(node) we look for.
 * @param root the node we start looking from.
 * @param name to look for in the tree.
 * @return the name(node) if exists.
 */
Node* Tree::findNode(Node* root, string name)
{
    if(this->_root == NULL)throw runtime_error("The tree is empty!!\n");
    if (root == NULL)
        return NULL;

    if (root->getName() == name)
        return root;

    /* then recur on father sutree */
    Node* res1 = findNode(root->getFather(), name);

    if(res1 != NULL) return res1; // node found, no need to look further

    /* node is not found in father, so recur on right subtree */
    Node* res2 = findNode(root->getMother(), name);
    if(res2 != NULL)return res2;
    else throw runtime_error("This name is not a member of the ancestor tree\n");
}

/**
 * add a node to the tree for the given name node by gender.
 * @param root of the tree to add the father or mother.
 * @param name node to add the parent.
 * @param parent is the parent name.
 * @param gender is the parent gender.
 */
void Tree::add(Node* root ,string name, string parent,bool gender){
    if(root != NULL && gender == true && root->getName() == name && root->getFather() == NULL){
        root->setNode(parent, gender);
        return;
    }
    if(root != NULL && gender == false && root->getName() == name && root->getMother() == NULL){
        root->setNode(parent, gender);
        return;
    }
    if(root != NULL){
        add(root->getMother(), name, parent, gender);
        add(root->getFather(), name, parent, gender);
    }
    return;
}
