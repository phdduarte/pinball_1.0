#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "Camera.h"
#include <iostream>
#include <math.h>
using namespace std;
const float PI = 3.14159;
const float g = -0.98;
float i = 0;
float forcaLancamento = 0;
bool mesaDeitada = false;
bool mostraGrade = true;
bool wireframe = false;


	GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

float teta = 0;
float angGiro = 0.0;
float anda = 0.0;
float gatilho = 0.0;
float movePaletaEsquerda = 45.0;
float movePaletaDireita = 45.0;
bool actionGatilho = false;
bool actionPaletaEsquerda = false;
bool actionPaletaDireita = false;

Camera cam(0,0.0,15.0,
           0.0,0.0,0.0,
           0.0,0.0,0.0,
           0,0,0.0,0.0);
float posXBola = 4.05;
float posYBola = -5.76;
//float posXBola = 0.05;
//float posYBola = 1.76;

float rotacaoXBola = 0;
float rotacaoYBola = 0;

float oldPosX = posXBola;
float oldPosY = posYBola;

bool moveUP = false;
bool moveDown = false;
bool moveLeft = false;
bool moveRight = false;

GLfloat JanelaBranca = 0.0;
GLfloat JanelaVerde = 0.0;
GLfloat PortaRack = 0.0;
GLfloat PortaEstante = 0.0;
GLfloat Porta1 = 0.0;
GLfloat Porta2 = -7.0;

void eixosCoord () {
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 10);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 10, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(10, 0, 0);
    glEnd();
}

void triangulo (float vermelho, float verde, float azul){
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_TRIANGLES);
        glColor3f(vermelho, verde, azul);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(0, 1, 0);
    glEnd();
}
void cubo2D( float vermelho, float verde, float azul)
{
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_POLYGON);
        glColor3f(vermelho, verde, azul);
        glVertex3f(0,0, 0);
        glVertex3f(0,1, 0);
        glVertex3f(1,1, 0);
        glVertex3f(1,0, 0);
    glEnd();
}
void triangulo3D( float vermelho, float verde, float azul)
{
    glPushMatrix();
        triangulo(vermelho, verde, azul);
    glPopMatrix();

//    //Traseira
    glPushMatrix();
        glTranslatef(0,0,-0.25);
        triangulo(vermelho, verde, azul);
    glPopMatrix();
//    //Cateto Adjacente
    glPushMatrix();
        glTranslatef(0,0,-0.25);
        glRotatef(90,1,0,0);
        glScalef(1,0.25,1);
        cubo2D(vermelho, verde, azul);
    glPopMatrix();

    //Cateto Oposto
    glPushMatrix();
        glTranslatef(0,0,-0.25);
        glRotatef(90,1,0,0);
        glRotatef(90,0,1,0);
        glScalef(1,0.25,1);
        cubo2D(vermelho, verde, azul);
    glPopMatrix();
    //Hipotenusa
    glPushMatrix();
        glTranslatef(0,1,-0.25);
        glRotatef(90,1,0,0);
        glRotatef(-45,0,1,0);
        glScalef(1.4,0.25,1);
        cubo2D(vermelho, verde, azul);
    glPopMatrix();
}
void pentagono( float vermelho, float verde, float azul)
{
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_POLYGON);
        glColor3f(vermelho, verde, azul);
        glVertex3f(1, -0.25, 0);
        glVertex3f(-1, -0.25, 0);
        glVertex3f(-1, 0.25, 0);
        glVertex3f(0, 1, 0);
        glVertex3f(1, 0.25, 0);
    glEnd();
}
void pentagono3D( float vermelho, float verde, float azul)
{
    //Frente
    glPushMatrix();
        pentagono(vermelho, verde, azul);
    glPopMatrix();

//    //Traseira
    glPushMatrix();
        glTranslatef(0,0,-0.5);
        pentagono(vermelho, verde, azul);
    glPopMatrix();

    //Lado Esquerdo
    glPushMatrix();
        glTranslatef(-1,-0.25,0);
        glRotatef(90,0,1,0);
        glScalef(0.5,0.5,0.5);
        cubo2D(vermelho, verde, azul);
    glPopMatrix();

    //Lado Direito
    glPushMatrix();
        glTranslatef(1,-0.25,0);
        glRotatef(90,0,1,0);
        glScalef(0.5,0.5,0.5);
        cubo2D(vermelho, verde, azul);
    glPopMatrix();
    //Fundo
    glPushMatrix();
        glTranslatef(-1,-0.25,-0.5);
        glRotatef(90,1,0,0);
        glScalef(2,0.5,0.5);
        cubo2D(vermelho, verde, azul);
    glPopMatrix();
    //Tampa Esquerda
    glPushMatrix();
        glTranslatef(-1,0.25,-0.5);
        glRotatef(90,1,0,0);
        glRotatef(36,0,1,0);
        glScalef(1.25,0.5,0.5);
        cubo2D(vermelho, verde, azul);
    glPopMatrix();
    //Tampa Direita
    glPushMatrix();
        glTranslatef(1,0.25,-0.5);
        glRotatef(90,1,0,0);
        glRotatef(145,0,1,0);
        glScalef(1.25,0.5,0.5);
        cubo2D(vermelho, verde, azul);
    glPopMatrix();
}
void seta ( float vermelho, float verde, float azul){
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_POLYGON);

        glColor3f(vermelho, verde, azul);
        glVertex3f(0.5, 0.5, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);
        glVertex3f(0.5, 1.5, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(1, 0, 0);
    glEnd();
}
void loadDefaultMaterial() {
	GLfloat mat_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.0, 1.0 };
	GLfloat mat_specular[] = { 0.4, 0.4, 0.0, 1.0 };
	GLfloat mat_shininess = { 50.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}
void polygon(int a, int b, int c , int d, float vermelho, float verde, float azul)
{
	glBegin(GL_POLYGON);
        glColor3f(vermelho, verde, azul);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
	glEnd();
}
void cubo(float vermelho, float verde, float azul)
{
    glEnable(GL_COLOR_MATERIAL);

    glNormal3f(0.0,0.0,-1.0);
	polygon(0,3,2,1, vermelho, verde, azul);

	glNormal3f(0.0,1.0,0.0);
	polygon(2,3,7,6, vermelho, verde, azul);

	glNormal3f(-1.0,0.0,0.0);
	polygon(0,4,7,3, vermelho, verde, azul);

	glNormal3f(1.0,0.0,0.0);
	polygon(1,2,6,5, vermelho, verde, azul);

	glNormal3f(0.0,0.0,1.0);
    polygon(4,5,6,7, vermelho, verde, azul);

	glNormal3f(0.0,-1.0,0.0);
    polygon(0,1,5,4, vermelho, verde, azul);

    glDisable(GL_COLOR_MATERIAL);

    loadDefaultMaterial();
}
// modelo de cilindro com eixo em Z
void cilindro(float vermelho, float verde, float azul)
{ // NAO SE PREOCUPE COM ESTA FUNCAO
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(vermelho, verde, azul);

      float raio = 1.0;
      float alt = 1.0;
      static GLUquadric* quad;
      quad = gluNewQuadric();
      gluCylinder(quad, raio, raio, alt, 20, 10);

      // tampa para o cilindro
      glPushMatrix();
      glTranslatef(0.0,0.0,1.0);
      glBegin(GL_POLYGON);
      for(int i = 0; i < 100; i++) {
         float ang = i*2*M_PI/100;
         glVertex2f(cos(ang) * raio, sin(ang) * raio);
      }
      glEnd();
      glPopMatrix();

    glDisable(GL_COLOR_MATERIAL);
	loadDefaultMaterial();
}
void circulo(float raio,float vermelho, float verde, float azul){
    glNormal3f(0,0,1);
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_POLYGON);
        glColor3f(vermelho, verde, azul);
        for(int i = 0; i < 100; i++) {
            float ang = i*2*PI/100;
            glVertex2f(cos(ang) * raio, sin(ang) * raio);
        }
    glEnd();
}
void tuboLateral()
{
    //Parede esquerda
    glPushMatrix();
        glTranslatef(-4.4,3.6,0.4);
        glScalef(0.08,4.7,0.4);
        cubo(0.74,0.74,0.74);
    glPopMatrix();

    //Parede Direita
    glPushMatrix();
        glTranslatef(-3.7,3.6,0.4);
        glScalef(0.08,4.7,0.4);
        cubo(0.74,0.74,0.74);
    glPopMatrix();

    //Curvinha esquerda
    glPushMatrix();
        glTranslatef(-4.1,-1.6,0.4);
        glRotatef(30,0,0,1);
        glScalef(0.08,0.6,0.4);
        cubo(0.74,0.74,0.74);
    glPopMatrix();
    //Curvinha Direita
    glPushMatrix();
        glTranslatef(-3.4,-1.6,0.4);
        glRotatef(30,0,0,1);
        glScalef(0.08,0.6,0.4);
        cubo(0.74,0.74,0.74);
    glPopMatrix();

    //Saida esquerda
    glPushMatrix();
        glTranslatef(-3.8,-3.1,0.4);
        glScalef(0.08,1,0.4);
        cubo(0.74,0.74,0.74);
    glPopMatrix();

    //Saida Direita
    glPushMatrix();
        glTranslatef(-3.1,-3.1,0.4);
        glScalef(0.08,1,0.4);
        cubo(0.74,0.74,0.74);
    glPopMatrix();

}

void cilindroLateral(){
        glPushMatrix();
            glTranslatef(4.5,9.7,0.0);
            glScalef(0.4,0.4,0.91);
            cilindro(1.0,0.0,0.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(4.5,9.7,0.0);
            glScalef(0.1,0.1,0.95);
            cilindro(0.0,0.0,1.0);
        glPopMatrix();
}


void mesaFixaJogo()
{

    // Fundo
    glPushMatrix();
        glScalef(4.5,10,0.1);
        cubo(0.64,0.16,0.16);
    glPopMatrix();

    // Parede Direita
    glPushMatrix();
        glTranslatef(4.7,0,0.4);
        glScalef(0.2,10,0.5);
        cubo(1.0,0.0,0.0);
    glPopMatrix();

    // Parede Direita
    glPushMatrix();
        glTranslatef(-4.9,0,0.4);
        glScalef(0.4,10,0.5);
        cubo(1.0,0.0,0.0);
    glPopMatrix();

    // Parede Superior
    glPushMatrix();
        glTranslatef(-0.2,10,0.4);
        glRotatef(90,0,0,1);
        glScalef(0.2,5.1,0.5);
        cubo(1.0,0.0,0.0);
    glPopMatrix();

    /*--------Pedy tubo nas laterais--------*/
    glPushMatrix();
        cilindroLateral();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-5.0,0.0,0.0);
        cilindroLateral();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-9.0,0.0,0.0);
        cilindroLateral();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0,-10.5,0.0);
        cilindroLateral();
    glPopMatrix();


/*----------------------------------------*/


}
void paleta ()
{
        //Suporte paleta Direita
        /* ------------- INICIO Conjunto paleta Direita ------------- */
    glPushMatrix();
        glTranslatef(2.2,-8,0.1);
        glRotatef(40,0,0,1);
        glScalef(1,0.2,0.5);
        cubo(1.0,0.0,0.0);
    glPopMatrix();
    // PaletaDireita
    glPushMatrix();

        glTranslatef(1.5,-8.6,0.3);
        glRotatef(-90,0,1,0);
        glRotatef(movePaletaDireita,1,0,0);
        glScalef(0.1,0.1,0.25);
        glutSolidCone( 4, 7, 7, 7);
    glPopMatrix();

        /* ------------- FIM  Conjunto paleta Direita ------------- */
    //Paleta Esquerda

        /* ------------- INICIO Conjunto paleta ESQUERDA ------------- */
    glPushMatrix();
        glTranslatef(-0.4,0,0.2);
        glRotatef(180,0,1,0);
        glPushMatrix();
            // Suporte Esquerda
            glPushMatrix();
                glTranslatef(2.4,-7.8,0.1);
                glRotatef(40,0,0,1);
                glScalef(1.3,0.2,0.5);
                cubo(1.0,0.0,0.0);
            glPopMatrix();
        glPopMatrix();
            // Paleta Esquerda
        glPushMatrix();
            glTranslatef(1.5,-8.6,-0.1);
            glRotatef(-90,0,1,0);
            glRotatef(movePaletaEsquerda,1,0,0);
            glScalef(0.1,0.1,0.25);
            glutSolidCone( 4, 7, 7, 7);
        glPopMatrix();
    glPopMatrix();

        /* ------------- FIM  Conjunto paleta ESQUERDA ------------- */
}
void mesaInferior()
{

    // Rota Lançamento Direita
    glPushMatrix();
        glTranslatef(4.4,-7,0.2);
        glScalef(0.1,3,0.5);
        cubo(1.0,0.2,0.0);
    glPopMatrix();
    // Rota Lançamento Esquerda
    glPushMatrix();
        glTranslatef(3.7,-7,0.2);
        glScalef(0.1,3,0.5);
        cubo(1.0,0.2,0.0);
    glPopMatrix();

    //Triangulo inferior esquerdo
    glPushMatrix();
        glTranslatef(-4.5,-10,0.6);
        glScalef(2.5, 1.6, 2);
        triangulo3D(0,1,0);
    glPopMatrix();
//    //Triangulo inferior direito
    glPushMatrix();
        glTranslatef(3.7,-10,0.1);
        glRotatef(180,0,1,0);
        glScalef(2.5, 1.6, 2);
        triangulo3D(0,1,0);
    glPopMatrix();

    glPushMatrix();
        paleta();
    glPopMatrix();
//
    glPushMatrix();
        tuboLateral();
    glPopMatrix();
}
void quadradosPiscantes()
{
       glPushMatrix();
        glTranslatef(-0.2,-8,0.1);
        glScalef(0.35,0.35,0.01);
        cubo(1,0,1);
    glPopMatrix();

    //1-1 = 2
    glPushMatrix();
        glTranslatef(-4,-6,0.1);
        glScalef(0.35,0.35,0.01);
        cubo(0,0.702,0.92);
    glPopMatrix();

    //1-2 =  3
    glPushMatrix();
        glTranslatef(-1.2,-5.8,0.1);
        glScalef(0.35,0.35,0.01);
        cubo(1,0,1);
    glPopMatrix();

    //1-3 =  4
    glPushMatrix();
        glTranslatef(0.8,-5.8,0.1);
        glScalef(0.35,0.35,0.01);
        cubo(0.4,1,0.3);
    glPopMatrix();

    //1-4 = 5
    glPushMatrix();
        glTranslatef(3,-5.8,0.1);
        glScalef(0.38,0.42,0.01);
        cubo(1,0.5,0.6);
    glPopMatrix();

    //2 - 1  = 6
    glPushMatrix();
        glTranslatef(-0.1,-4,0.1);
        glScalef(1,0.7,0.01);
        cubo(1,0.5,0.6);
    glPopMatrix();


    //3 - 1  = 7
    glPushMatrix();
        glTranslatef(-2.4,-2.1,0.1);
        glScalef(0.35,0.35,0.01);
        cubo(0.4,1,0.3);
    glPopMatrix();

    //3 - 2  = 8
    glPushMatrix();
        glTranslatef(0,-1.1,0.1);
        glScalef(0.35,0.35,0.01);
        cubo(0.4,1,0.3);
    glPopMatrix();

    //3 -3  = 9
    glPushMatrix();
        glTranslatef(2.4,-2.1,0.1);
        glScalef(0.35,0.35,0.01);
        cubo(0.4,1,0.3);
    glPopMatrix();
    //4 - 1  = 10
    glPushMatrix();
        glTranslatef(0,4.1,0.1);
        glScalef(0.35,0.35,0.01);
        cubo(0.4,1,0.3);
    glPopMatrix();
    //5 - 1  = 11
    glPushMatrix();
        glTranslatef(2.7,7.6,0.1);
        glScalef(0.35,0.35,0.01);
        cubo(0.4,1,0.3);
    glPopMatrix();

}
void setasPiscantes()
{
        // Setas da barra lateral
    // 1
    glPushMatrix();
        glTranslatef(-3.75,0,0.11);
        glRotatef(180,0,0,1);
        glScalef(0.6,0.6,1);
        seta(1,0,0);
    glPopMatrix();

        // 2
    glPushMatrix();
        glTranslatef(-3.75,2,0.11);
        glRotatef(180,0,0,1);
        glScalef(0.6,0.6,1);
        seta(1,0,0);
    glPopMatrix();
    // 3
    glPushMatrix();
        glTranslatef(-3.75,4,0.11);
        glRotatef(180,0,0,1);
        glScalef(0.6,0.6,1);
        seta(1,0,0);
    glPopMatrix();

        // 4
    glPushMatrix();
        glTranslatef(-3.75,6,0.11);
        glRotatef(180,0,0,1);
        glScalef(0.6,0.6,1);
        seta(1,0,0);
    glPopMatrix();
    // 5
    glPushMatrix();
        glTranslatef(-3.75,8,0.11);
        glRotatef(180,0,0,1);
        glScalef(0.6,0.6,1);
        seta(1,0,0);
    glPopMatrix();

}
void circulosPiscantes()
{
    // 1 -1
    glPushMatrix();
        glTranslatef(-2.6,-0.85,0.11);
        circulo(0.4,1,0,0);
    glPopMatrix();

    // 2 -1
    glPushMatrix();
        glTranslatef(4.0,0.5,0.11);
        circulo(0.4,1,0,0);
    glPopMatrix();
        // 3 -1
    glPushMatrix();
        glTranslatef(-2.9,2.85,0.11);
        circulo(0.4,1,0,0);
    glPopMatrix();
        // 4 -1
    glPushMatrix();
        glTranslatef(-2.9,3.85,0.11);
        circulo(0.4,1,0,0);
    glPopMatrix();
        // 5 -1
    glPushMatrix();
        glTranslatef(4.0,4.5,0.11);
        circulo(0.4,1,0,0);
    glPopMatrix();
        // 6 -1
    glPushMatrix();
        glTranslatef(-2.3,5.4,0.11);
        circulo(0.4,1,0,0);
    glPopMatrix();
        // 7 -1
    glPushMatrix();
        glTranslatef(1.7,8.5,0.11);
        circulo(0.4,1,0,0);
    glPopMatrix();
        // 7 -2
    glPushMatrix();
        glTranslatef(3.7,8.5,0.11);
        circulo(0.4,1,0,0);
    glPopMatrix();


}
void itensDeMesaPisca()
{
    //a contagem é feita de baixo para cima
    // da esquerda para a direita
    // 1
    quadradosPiscantes();

    setasPiscantes();

    circulosPiscantes();
}
void barraDisparo()
{
    glPushMatrix();
        glRotatef(180,0,0,1);
        glTranslatef(-4.05,8-gatilho,0.4);
        glScalef(0.23,2+gatilho,0.4);
        cubo(0,0,0);
    glPopMatrix();
}
void itemBate()
{

    glPushMatrix();
       glScalef(0.6,0.6,0.6);
       glTranslatef(5.6,5.0,0.0);
       cilindro(0.0,1.0,0.0);
    glPopMatrix();

    glPushMatrix();
       glScalef(0.6,0.6,0.6);
        glTranslatef(1.3,1.3,0.0);
       cilindro(0.0,1.0,0.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.7,7.5,0.0);
        glRotatef(40,0,0,1);
        glScalef(0.6,0.6,0.6);
        cubo(1.0,0.0,0.0);
    glPopMatrix();


/*-----------------------------Paleta superior----------------------------------*/
    glPushMatrix();
        glTranslatef(2.7,11.0,0.0);
        glScalef(0.6,0.6,0.6);
        paleta();
    glPopMatrix();


/*----------------------------------------------------------------------------------*/




/*-----------------------------Paleta lateral direita----------------------------------*/
    // Direito
        glPushMatrix();
            glTranslatef(4.3,0.0,0.5);
            glRotatef(-115,0,0,1);
            glScalef(0.8,0.3,1.0);
            pentagono3D(1,0,0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(4.3,0.5,0.5);
            glRotatef(65,0,0,1);
            glScalef(0.5,0.3,1.0);
            pentagono3D(1,0,0);
        glPopMatrix();


        glPushMatrix();
            glTranslatef(4.2,0.0,0.2);
            glRotatef(-90,0,1,0);
            glRotatef(movePaletaDireita,1,0,0);
            glScalef(0.05,0.05,0.25);
            glutSolidCone( 4, 4, 7, 7);
        glPopMatrix();

/*----------------------------------------------------------------------------------*/

/*------------------------PAleta lateral esquerda------------------------------*/
        glPushMatrix();
            glTranslatef(-3.6,0.0,0.8);
            glRotatef(-90,0,0,1);
            glScalef(0.5,0.3,1.4);
            pentagono3D(1,0,0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3.6,0.7,0.8);
            glRotatef(-90,0,0,1);
            glScalef(0.2,0.2,1.4);
            pentagono3D(1,0,0);
        glPopMatrix();


        glPushMatrix();
            glTranslatef(-3.4,0.6,0.5);
            glRotatef(90,0,1,0);
            glRotatef(movePaletaEsquerda,1,0,0);
            glScalef(0.1,0.1,0.25);
            glutSolidCone( 2, 4, 4, 4);
        glPopMatrix();



/*-----------------------------------------------------------------------------*/

/*-----------------------------Pentagonos  inferiores----------------------------------*/

    // Esquerdo
     glPushMatrix();
            glTranslatef(-2.5,-6,0.5);
            glRotatef(115,0,0,1);
            glScalef(0.9,0.4,1);
            pentagono3D(0,0,1);
        glPopMatrix();
        // Direito
        glPushMatrix();
            glTranslatef(2,-6,0.5);
            glRotatef(-115,0,0,1);
            glScalef(1,0.4,1);
            pentagono3D(0,0,1);
        glPopMatrix();
}
void bolinha()
{
    glPushMatrix();
        glTranslatef(posXBola,posYBola,.35);
        glRotatef(rotacaoXBola,1,0,0);
        glRotatef(rotacaoYBola,0,1,0);
        glScalef(0.25,0.25,0.25);
        if(wireframe)
            glutWireSphere(1,15,15);
        else
            glutSolidSphere(1,15,15);
    glPopMatrix();
}
void mesaPinBall()
{

    mesaFixaJogo();
    mesaInferior();
    barraDisparo();
    itensDeMesaPisca();
    itemBate();
    bolinha();

}
void distanciaMesa()
{
    int  i = 0;
    while( i < 11)
    {
         glPushMatrix();
            glTranslatef(6,10.5-i*(2),1);
            glScalef(20,0.1,0);
            cubo(0.0,0.0,0.0);
        glPopMatrix();
        i++;
    }
    i = 0;
    while( i < 6)
    {
         glPushMatrix();
            glTranslatef(-4.78+i*(1.9),-10,1);
            glRotatef(90,0,0,1);
            glScalef(20,0.1,0);
            cubo(0.0,0.0,0.0);
        glPopMatrix();
        i++;
    }
}

void exibe()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cam.film();
    glPushMatrix();

        glTranslatef(0.0, 0.0, anda);
//        glRotatef(anda, 0.0,0.0,1.0);
        eixosCoord();
    glPopMatrix();

    if(mostraGrade)
    {
        glPushMatrix();
            distanciaMesa();
        glPopMatrix();
    }

    glPushMatrix();
        if(mesaDeitada)
        {
            glTranslatef(0,-2,0);
            glRotatef(-90,1,0,0);
        }
        mesaPinBall();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void mouse(int x, int y){
    cam.mouseMotionListener(x, y);
}


void controle (unsigned char tecla, int x, int y) {

    cam.keyboardListener(tecla, x, y);
    switch (tecla) {
        case 27: exit(EXIT_SUCCESS);  // tecla ESC para sair
//        case 'x': angGiro -= 1.0; break;
        case 't': i = 0.0; break;
        case 'f': wireframe = not wireframe; break;
        case 'g': mostraGrade = not mostraGrade; break;
        case 'z': actionPaletaEsquerda = true; break;
        case 'x': actionPaletaDireita = true; break;
        case 'v': actionGatilho = true; break;
        case 'p': mesaDeitada = not mesaDeitada; break;
        case 'q': exit(EXIT_SUCCESS); break;
   }
   glutPostRedisplay();   //exibe();
}

void controleUP (unsigned char tecla, int x, int y) {
    switch (tecla) {

    case 'z': actionPaletaEsquerda = false; break;
    case 'x': actionPaletaDireita =false; break;
    case 'v': actionGatilho = false; break;
    }
}
void movimentosBolinha()
{
    i += 0.0001;
    if(forcaLancamento > 0.00000 and (not actionGatilho) )
        posYBola = oldPosY + forcaLancamento*i + (g*pow(i,2))/2;

    if( posYBola > 9.5)
    {
        posYBola = 9.5;
    }
    if (posXBola > 4.26)
        posXBola = 4.26;
    if( posXBola < - 4.26)
        posXBola = - 4.26;
    if(posXBola < oldPosX)
    {
        moveRight = true;
        moveLeft = false;
    }
    else if(posXBola > oldPosX)
        {
            moveLeft = true;
            moveRight = false;
        }
        else
        {
            moveLeft = false;
            moveRight = false;
    }

    if(posYBola < oldPosY)
    {
        moveDown = true;
        moveUP = false;
    }
    else if(posYBola > oldPosY)
        {
            moveUP = true;
            moveDown = false;
        }
        else
        {
            moveUP = false;
            moveDown = false;
        }

    if(moveUP)
    {
        rotacaoXBola += 5;
        if(rotacaoXBola > 360)
            rotacaoXBola = 0;
    }
    if(moveDown)
    {
        rotacaoXBola -= 5;
        if(rotacaoXBola < -360)
            rotacaoXBola = 0;
    }
    if(moveLeft)
        rotacaoYBola += 0.1;
    if(moveRight)
        rotacaoYBola -= 0.1;
    oldPosX = posXBola;
    oldPosY = posYBola;
}
void gira() {
    movimentosBolinha();
    teta += 3;
      glutPostRedisplay();   //exibe();
    if(actionGatilho)
    {
        gatilho -= 0.005;
        if(posXBola > 4.050 and posXBola <4.051 and gatilho >= -2)
        {
            cout << "HAAA\n";
            forcaLancamento +=0.005;
            if(forcaLancamento >  0.13)
                forcaLancamento =  0.13;
            cout << forcaLancamento;
            posYBola -= 0.01;
        }

            cout << "neh\n";
    }
    else
    {
        gatilho += 0.03;
        if(posXBola > 4.050 and posXBola <4.051  and gatilho <=0)
        {
            posYBola += 0.065;
        }
    }

    if (gatilho >= 0.0)
        gatilho = 0;
    if (gatilho <= -2.0)
        gatilho = -2;

    if(actionPaletaEsquerda)
        movePaletaEsquerda -= 1;
    else
        movePaletaEsquerda += 1.5;

    if (movePaletaEsquerda >= 45.0)
        movePaletaEsquerda = 45;
    if (movePaletaEsquerda <= -20.0)
        movePaletaEsquerda = -20;

    if(actionPaletaDireita)
        movePaletaDireita -= 1;
    else
        movePaletaDireita += 1.5;

    if (movePaletaDireita >= 45.0)
        movePaletaDireita = 45;
    if (movePaletaDireita <= -20.0)
        movePaletaDireita = -20;

}


void windows(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void inicia()
{
    // estabelece parametros de iluminacao

    GLfloat mat_ambient[]={1.0, 1.0, 0.0, 1.0};
    GLfloat mat_diffuse[]={0.6, 0.6, 0.0, 1.0};
    GLfloat mat_specular[]={0.4, 0.4, 0.0, 1.0};
    GLfloat mat_shininess={50.0};
    GLfloat light_ambient[]={0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]={0.8, 0.8, 0.8, 1.0};
    GLfloat light_specular[]={0.6, 0.6, 0.6, 1.0};

    GLfloat light_position[]={-3.0,3.0,0.0,1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glClearColor (0.7, 0.7, 1.0, 1.0);
    cam.setPerspective();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pinball");
    glutReshapeFunc(windows);
    glutDisplayFunc(exibe);
    glutKeyboardFunc(controle);
    glutKeyboardUpFunc(controleUP);
    glutPassiveMotionFunc(mouse);
    glutIdleFunc(gira);
    inicia();
    glutMainLoop();
}
