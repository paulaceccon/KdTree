/* 
 * File:   KdTree.h
 * Author: paulaceccon
 *
 * Created on 10 de Novembro de 2013, 11:11
 */

#ifndef KDTREE_H
#define	KDTREE_H

#include <vector>
#include "Node.h"

class KdTree
{
public:
    Node * root;
    KdTree ( std::vector<Point> &points );
    Node * BuildKdTree ( std::vector<Point> &points, int begin, int end, int depth );
    void PrintKdTree ( Node * root );
    virtual ~KdTree ( );
private:

};

#endif	/* KDTREE_H */

