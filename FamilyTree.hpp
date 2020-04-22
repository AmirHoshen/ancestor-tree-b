/*
*
* Created by miros on 17/04/2020.
*
*/

#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace family
{

    class Node
    {

        Node *father;
        Node *mother;
        string name;
        bool _gender;  /* false = Mother, true = Father  */

    public:

        Node(string name, bool gender)
        {
            this->name = name;
            father = NULL;
            mother = NULL;
            _gender = gender;
        }

        ~Node()
        {
            setFatherToNull();
            setMotherToNull();
        }
        void setFatherToNull()
        {
            this->father = NULL;
        }

        void setMotherToNull()
        {
            this->mother = NULL;
        }
        string getName()
        {
            return this->name;
        }
        Node *getMother()
        {
            return this->mother;
        }
        Node *getFather()
        {
            return this->father;
        }
        bool getGender()
        {
            return this->_gender;
        }

        void setNode(string parent, bool gender) /* false = Mother, true = Father  */
        {
            if (gender == true)
            {
                Node *ans = new Node(parent, gender);
                this->father = ans;
            }
            else
            {
                Node *ans = new Node(parent, gender);
                this->mother = ans;
            }
        }
    };

    class Tree
    {
        Node *_root;

    public:
        Tree(string name)
        {
            this->_root = new Node(name, true);
        }

        Tree &addFather(string name, string father);

        Tree &addMother(string name, string mother);

        string relation(string name);

        string find(string relation);

        void display();

        void remove(string name);

        void deleteSubTree(Node *root);

        void add(Node *root, string name, string parent, bool gender);

        void printTree(Node *root);

        int getLevel(Node *node, string name);

        int getLevelUtil(Node *node, string name, int level);

        Node *findNode(Node *root, string name);

        string nodeNameAtHeight(Node *node, int heightAns, bool gender);

        Node *getNodeByHeight(Node *root, int count, bool gender);

        void findSubTree(Node *root, string name, Node **runNode);

    };
}