/* 
 * File:   KdTree.cpp
 * Author: paulaceccon
 * 
 * Created on 10 de Novembro de 2013, 11:11
 */

#include "KdTree.h"
#include <algorithm>
#include <cstdio>



bool comp_x( const Point &n1, const Point &n2 )
{
    return n1.x < n2.x;
}



bool comp_y( const Point &n1, const Point &n2 )
{
    return n1.y < n2.y;
}



KdTree::KdTree( std::vector<Point>& points )
{
    BuildKdTree( points, 0, points.size( ), 0 );
}



Node * KdTree::BuildKdTree( std::vector<Point> &points, int begin, int end, int depth )
{

    if (end - begin <= 0)
        return 0;

    int dimension = Point::PointDimension( );
    int axis = depth % dimension;
    if (axis == 0)
    {
        sort( points.begin( ) + begin, points.begin( ) + end, comp_x );
    }
    else
    {
        sort( points.begin( ) + begin, points.begin( ) + end, comp_y );
    }

    int half = (begin + end) / 2;
    Node * median = new Node( points[half] );
    median->left = BuildKdTree( points, begin, half, depth + 1 );
    median->right = BuildKdTree( points, half + 1, end, depth + 1 );
    
    if (depth == 0)
    {
        root = median;
    }
    return median;
}



void KdTree::PrintKdTree( Node * root )
{
    if (root == 0)
    {
        printf( "Nil\n" );
        return;
    }
    printf( "%lf %lf\n", root->p.x, root->p.y );
    PrintKdTree( root->left );
    PrintKdTree( root->right );
}



KdTree::~KdTree( )
{
}

