/* 
 * File:   Point.cpp
 * Author: paulaceccon
 * 
 * Created on 10 de Novembro de 2013, 10:55
 */

#include "Point.h"



int Point::PointDimension( )
{
    return DIM;
}



Point::Point( )
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}



Point::Point( const Point& orig )
{
    this->x = orig.x;
    this->y = orig.y;
    this->z = orig.z;
}



Point::Point( double x, double y, double z )
{
    this->x = x;
    this->y = y;
    this->z = z;
}



const Point& Point::operator = ( const Point& p )
{
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
    return * this;
}



Point::~Point( )
{
}

