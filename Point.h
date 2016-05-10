/* 
 * File:   Point.h
 * Author: paulaceccon
 *
 * Created on 10 de Novembro de 2013, 10:55
 */

#ifndef POINT_H
#define	POINT_H

#define DIM 2
#define EPS 10E-1

#include <cmath>

class Point
{
public:
    double x;
    double y;
    double z;
    static int PointDimension ( );
    
    /**
     * Construtor default.
     */
    Point ( );
    
    /**
     * Construtor de copia.
     * @param orig
     */
    Point ( const Point& orig );
    
    /**
     * 
     * @param x
     * @param y
     * @param z
     */
    Point ( double x, double y, double z );
    
    /**
     * 
     * @param p
     * @return 
     */
    const Point& operator = ( const Point& p );
    
    /**
     * Sobrecarga do operador == entre dois pontos.
     * @param p1 - primeiro ponto.
     * @param p2 - segundo ponto.
     * @return - booleando informando igualdade ou nao entre os pontos.
     */
    inline friend bool operator == ( const Point& p1, const Point& p2 ) 
    {
        return ( fabs ( p1.x - p2.x ) < EPS ) && ( fabs ( p1.y - p2.y ) < EPS )
                && ( fabs ( p1.z - p2.z ) < EPS );
    }
    
    /**
     * Destrutor.
     */
    virtual ~Point ( );
private:
};

#endif	/* POINT_H */

