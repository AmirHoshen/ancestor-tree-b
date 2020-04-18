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
        cout<<"The tree is empty!!\n"<<endl;
    }
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
