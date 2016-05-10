/* 
 * File:   Node.cpp
 * Author: paulaceccon
 * 
 * Created on 10 de Novembro de 2013, 10:46
 */

#include "Node.h"



Node::Node( Point p )
{
    this->p = p;
    this->left = 0;
    this->right = 0;
}



Node::~Node( )
{
}

