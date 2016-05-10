/* 
 * File:   main.cpp
 * Author: paulaceccon
 *
 * Created on 10 de Novembro de 2013, 10:43
 */

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include "Node.h"
#include "KdTree.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

// Define o sistema de coordenadas: (-winW, winW) em X
// e (-winH, winH) em Y. 
// Estes valores é sempre calculado na função reshape e valem para o tamanho 
// inicial da janela apenas.
double winW = 25.0, winH = 25.0;

// Define o tamanho do grid desenhado ao fundo. 
// Este valor é usado para calcular o sistema de coordenadas.
const double lenghGrid = 24.0;

// Tamanho da janela em pixeis. Usado para converter do sistema de coordenadas 
// em pixeis para o sistema de coordenadas definido na janela.
int widthWin = 600, heightWin = 600;

// Cor de fundo da janela e do grid. 0.0f para preto e 1.0f para branco.
float colorGrid = 0.0f;

// Pontos de entrada.
std::vector<Point> points;

// Ponto selecionado, se houver.
int selectPoint = -2;

// Modo de interacao
enum InteractionMode
{
    INSERT_POINTS = 0,
    EDIT_POINTS = 1
};
InteractionMode interactionMode = INSERT_POINTS;



/**
 * Funcao que renderiza o grid.
 */
void renderGrid( void )
{
    double i = 0.0, j = 0.0;
    
    // Desenha quadradinhos do grid ao fundo.
    for (i = -winH; i < winH; i++)
    {
        for (j = -winW; j < winW; j++)
        {
            glBegin( GL_POLYGON );
            glColor3f( fabs( colorGrid - 0.94f ), fabs( colorGrid - 0.94f ), fabs( colorGrid - 0.94f ) );
            glVertex2f( i * 2, j * 2 );
            glVertex2f( i * 2 + 1, j * 2 );
            glVertex2f( i * 2 + 1, j * 2 + 1 );
            glVertex2f( i * 2, j * 2 + 1 );
            glEnd( );
        }
    }
    
    // Desenha linhas do grid.
    glBegin( GL_LINES );

    glColor3f( fabs( colorGrid - 0.9f ), fabs( colorGrid - 0.9f ), fabs( colorGrid - 0.9f ) );
    for (i = -winW; i < winW; i++)
    {
        glVertex2f( i, -winH );
        glVertex2f( i, winH );
    }
    for (i = -winH; i < winH; i++)
    {
        glVertex2f( -winW, i );
        glVertex2f( winW, i );
    }
    
    // Desenha linhas para os eixos X e Y.
    glColor3f( fabs( colorGrid - 0.4f ), fabs( colorGrid - 0.4f ), fabs( colorGrid - 0.4f ) );
    glVertex2f( 0.0, -winH );
    glVertex2f( 0.0, winH );
    glVertex2f( -winW, 0.0 );
    glVertex2f( winW, 0.0 );
    glEnd( );
}



/**
 * Funcao que renderiza os pontos de entrada.
 */
void renderPoints( void )
{
    if (points.size( ) == 0)
        return;

    glPointSize( 6.0f );
    glColor3d( 1.0, 0.0, 0.0 );
    glEnable( GL_POINT_SMOOTH );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBegin( GL_POINTS );
    for (unsigned int i = 0; i < points.size( ); i++)
    {
        glVertex2f( points[i].x, points[i].y );
    }
    glEnd( );
    glDisable( GL_POINT_SMOOTH );
    glDisable( GL_BLEND );
}



/**
 * Funcao que renderiza a kdtree.
 */
void renderNode ( Node * node, double min_x, double max_x, double min_y, double max_y, int depth) 
{
    if (node == 0)
    {
        return;
    }
    
    int dimension = Point::PointDimension( );
    int axis = depth % dimension;
    
    if ( axis == 0 ) 
    {
        glBegin( GL_LINES );
        glVertex2d( node->p.x, min_y );
        glVertex2d( node->p.x, max_y );
        glEnd( );
        renderNode( node->left, min_x, node->p.x, min_y, max_y, depth + 1 );
        renderNode( node->right, node->p.x, max_x, min_y, max_y, depth + 1 );
    }
    else 
    {
        glBegin( GL_LINES );
        glVertex2d( min_x, node->p.y );
        glVertex2d( max_x, node->p.y );
        glEnd( );
        renderNode( node->left, min_x, max_x, min_y, node->p.y, depth + 1 );
        renderNode( node->right, min_x, max_x, node->p.y, max_y, depth + 1 );
    }
}



void renderKdTree ( void )
{
    if ( points.size() == 0 )
        return;
    
    KdTree tree (points);
    //tree.PrintKdTree(tree.root);
    
    // Descobrindo a caixa envolvente.
    double min_x = points[0].x, max_x = points[0].x, min_y = points[0].y, max_y = points[0].y;
    for (unsigned int i = 0; i < points.size( ); i++)
    {
        if ( points[i].x < min_x )
            min_x = points[i].x;
        if ( points[i].x > max_x )
            max_x = points[i].x;
        if ( points[i].y < min_y )
            min_y = points[i].y;
        if ( points[i].y > max_y )
            max_y = points[i].y;
    }
    max_x += 2;
    max_y += 2;
    min_x -= 2;
    min_y -= 2;
    glBegin( GL_LINES );
    glColor3f( fabs( colorGrid ), fabs( colorGrid ), fabs( colorGrid ) );
    glVertex2f( min_x, min_y);
    glVertex2f( min_x, max_y);
    
    glVertex2f( min_x, min_y);
    glVertex2f( max_x, min_y);
    
    glVertex2f( max_x, min_y);
    glVertex2f( max_x, max_y);
    
    glVertex2f( min_x, max_y);
    glVertex2f( max_x, max_y);
    glEnd( );
    
    renderNode ( tree.root, min_x, max_x, min_y, max_y, 0);
}



/**
 * Funcao que recebe eventos de redesenho da tela.
 * Esta função deve ser chamada todas as vezes que a tela precisar ser
 * redesenhada.
 */
void display( void )
{
    // Limpa a janela com a cor branca ou preta, dependendo do valor de fundo do grid.
    glClearColor( fabs(colorGrid - 1.0 ), fabs(colorGrid - 1.0 ), fabs(colorGrid - 1.0 ), 0.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Renderiza o grid de referencia que aparece ao fundo da tela.
    renderGrid( );
    
    // Renderiza os pontos de entrada.
    renderPoints( );
    
    // Renderiza a kdtree.
    renderKdTree( );
            
    // Troca os buffers de escrita e desenho.
    glutSwapBuffers( );
}



/**
 * Recebe eventos de redimensionamento da tela.
 * @param width - largura da janela em pixeis.
 * @param heigh - altura da janela em pixeis.
 */
void reshape( int width, int heigh )
{
    // Define qual porção da janela será usada.
    // Os parametros são: coordenadas inferior esquerda (0,0) e a largurda
    // e a altura a partir do ponto.
    glViewport( 0, 0, width, heigh );

    // Salva as dimensoes da janela em pixeis.
    widthWin = width;
    heightWin = heigh;

    // Calcula a variacao do sistema de coordenadas de modo que o (0,0) fique
    // no centro da tela.
    winW = (int) (width / lenghGrid + 0.5);
    winH = (int) (heigh / lenghGrid + 0.5);

    // Define a matriz de projecao como corrente para definir o sistema de
    // coordenadas.
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    // Define o sistema de coordenadas.
    gluOrtho2D( -winW, winW, -winH, winH );

    // Define a matriz de modelview como corrente para realizar o desenho.
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
}



/**
 * Recebe evento de clique do mouse.
 * @param button - botao que envia o evento.
 * @param state - estado do botao.
 * @param x - coordenada x do mouse na tela em pixels.
 * @param y - coordenada y do mouse na tela em pixels.
 */
void mouse( int button, int state, int x, int y )
{
    //converte coordenadas de tela para o mundo
    Point p;
    p.x = ((2.0 * winW * x) / widthWin) - winW;
    p.y = (((2.0 * winH) * (heightWin - y)) / heightWin) - winH;

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {   
            for (unsigned int i = 0; i < points.size( ); i++)
            {
                if (p == points[i])
                {
                    selectPoint = (int) i;
                    break;
                }
            }
            
            if (selectPoint < 0 )
            {
                points.push_back( p );
            }
            
        }
        else if (state == GLUT_UP)
        {
            selectPoint = -2;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            if (interactionMode == INSERT_POINTS)
            {
                interactionMode = EDIT_POINTS;
            }
            else if (interactionMode == EDIT_POINTS)
            {
                interactionMode = INSERT_POINTS;
                points.clear( );
            }
        }
    }
    display( );
}



/**
 * Recebe evento de movimento do mouse.
 * @param x - coordenada x do mouse na tela em pixels.
 * @param y - coordenada y do mouse na tela em pixels.
 */
void mouseMotion( int x, int y )
{
    Point p;
    p.x = ((2.0 * winW * x) / widthWin) - winW;
    p.y = (((2.0 * winH) * (heightWin - y)) / heightWin) - winH;
    if (selectPoint >= 0)
    {
        points[selectPoint] = p;
    }
    display( );
}



/**
 * Função principal.
 * @param argc - número de argumentos do programa.
 * @param argv - lista de argumentos do programa.
 * @return 
 */
int main( int argc, char** argv )
{
    // Inicializa a glut passando os argumentos do programa.
    glutInit( &argc, argv );

    // Inicializa o modo de display. Buffer duplo, RGBA e teste de profundidade.
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    // Inicializa o tamanho da janela inicial. 600x600 pixels.
    glutInitWindowSize( 600, 600 );

    // Inicializa a posicao inicial da janela.
    glutInitWindowPosition( 100, 100 );

    // Cria a janela definindo um titulo.
    glutCreateWindow( "2D KdTree" );

    // Registra a funcao de display. Esta função é chamada toda vez que a tela
    // precisa ser redesenhada.
    glutDisplayFunc( display );

    // Resgistra a funcao de reshape. Esta funcao é chamada toda vez que a janela
    // precisa ser redimensionada. Inclusive em sua criacao (momento em que ela
    // aparece pela primeira vez na tela.
    glutReshapeFunc( reshape );

    // Registra funcao que recebe os eventos de clique do mouse.
    glutMotionFunc( mouseMotion );
    
    // Registra a funcao que recebe os eventos do mouse. Essa funcao e chamada
    // toda vez que um botao e pressionado ou liberado.
    glutMouseFunc( mouse );

    // Inicia o loop da glut, o que faz o programa OpenGL começar a rodar.
    glutMainLoop( );

    return (EXIT_SUCCESS);
}

