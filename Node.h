/* 
 * File:   Node.h
 * Author: paulaceccon
 *
 * Created on 10 de Novembro de 2013, 10:46
 */

#ifndef NODE_H
#define	NODE_H

#include "Point.h"

class Node
{
public:
    Node * left, * right;
    Point p;
    Node ( Point p );
    virtual ~Node ( );
private:

};

#endif	/* NODE_H */

