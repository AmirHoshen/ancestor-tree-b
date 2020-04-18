//
// Created by miros on 17/04/2020.
//

#include <iostream>
#include "FamilyTree.hpp"
using namespace family;


Tree& Tree::addFather(string name, string father)
{
    add(this->root, name, father, true);
    return *this;
}

Tree& Tree::addMother(string name, string mother)
{
    add(this->root, name, mother, false);
    return *this;
};

void family::Tree::display()
{
    printTree(root);

}

/**
 * receiving the ancestor tree root and printing the tree.
 * if he is null then the tree is empty
 * @param root of the tree.
 */
void family::Tree::printTree(Node* root)
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
 * source: https://www.youtube.com/watch?v=IJCg_jxOM_Q
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
int Tree::getLevelUtil(Node *node, string name, int level)
{
    if(node == NULL) return 0;
    if(node->getName() == name) return level;
    int downlevel = getLevelUtil(node->getFather(),name, level+1);
    if(downlevel != 0) return downlevel;
    downlevel = getLevelUtil(node->getMother(),name, level+1);
    return downlevel;
}

string family::Tree::relation(string name)
{
    return "";
}

string family::Tree::find(string relation)
{

    return "";
}

void family::Tree::remove(string name)
{
    Node* tmp = findNode(root, name);
    if(tmp == NULL)return;
    deleteSubTree(tmp);

}

void Tree::deleteSubTree(Node* root){
    if(root == NULL) return;

    //deleting all subtree of the node.
    deleteSubTree(root->getFather());
    deleteSubTree(root->getMother());

    //then delete the root node of this subtree.
    cout<<"\n Deleting node: "<<root->getName()<<endl;
    free(root);
}

Node* family::Tree::findNode(Node* root, string name)
{
    if (root == NULL)
        return NULL;

    if (root->getName() == name)
        return root;

    /* then recur on father sutree */
    Node* res1 = findNode(root->getFather(), name);

    if(res1 != NULL) return res1; // node found, no need to look further

    /* node is not found in father, so recur on right subtree */
    Node* res2 = findNode(root->getMother(), name);

    return res2;


}

void family::Tree::add(Node* root ,string name, string parent,bool g){
    if(root != NULL && g == true && root->getName() == name && root->getFather() == NULL){
        root->setNode(parent, g);
        return;
    }
    if(root != NULL && g == false && root->getName() == name && root->getMother() == NULL){
        root->setNode(parent, g);
        return;
    }
    if(root != NULL){
        add(root->getMother(), name, parent, g);
        add(root->getFather(), name, parent, g);
    }
    return;
}
