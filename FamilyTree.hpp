//
// Created by miros on 17/04/2020.
//



#pragma once
#include<string>
#include <iostream>
using namespace std;

namespace family{

    class Node{

        Node* father;
        Node* mother;
        string name;

    public:
        Node()
        {
            string name = "";
            Node* father = NULL;
            Node* mother = NULL;
        }
        Node(string name)
        {
            this->name = name;
            father = NULL;
            mother = NULL;
        }
        ~Node();
        string getName(){
            return this->name;
        }
        Node* getMother(){
            return this->mother;
        }
        Node* getFather(){
            return this->father;
        }
        void setNode(string parent, bool g) //false = mother, true = father
        {
            if(g == true)
            {
                Node* ans = new Node(parent);
                this->father = ans;
            }
            else
            {
                Node* ans = new Node(parent);
                this->mother = ans;
            }
        }
    };


    class Tree{
        Node* root;
    public:

        Tree(string name)
        {
            this->root = new Node(name);
        }
        Tree& addFather(string name, string father);
        Tree& addMother(string name, string mother);
        string relation(string name);
        string find(string relation);
        void display();
        void remove(string name);
        void deleteSubTree(Node* root);
        void add(Node* root ,string name, string parent,bool g);
        void printTree(Node* root);
        Node* findNode(Node* root, string name);

    };
}

