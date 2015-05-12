#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "Camera.h"

	GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

float teta = 0;
float angGiro = 0.0;
float anda = 0.0;

Camera cam(0,0.0,15.0,
           0.0,0.0,0.0,
           0.0,0.0,0.0,
           0,0,0.0,0.0);

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

void triangulo (){
    glBegin(GL_TRIANGLES);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(0, 1, 0);
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


void mesaFixaJogo()
{

    // Fundo
    glPushMatrix();
        glScalef(4.5,10,0.1);
        cubo(1.0,0.64,0.0);
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
}
void paleta()
{
    //Suporte Paleta Direita
    glPushMatrix();
        glTranslatef(2.2,-8,0.1);
        glRotatef(40,0,0,1);
        glScalef(1,0.2,0.1);
        cubo(1.0,0.0,0.0);
    glPopMatrix();
    // PaletaDireita
    glPushMatrix();
        glTranslatef(1.5,-8.6,0.1);
        glRotatef(-90,0,1,0);
        glRotatef(45,1,0,0);
        glScalef(0.05,0.1,0.25);
        glutSolidCone( 4, 7, 7, 7);
    glPopMatrix();

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
        glTranslatef(-4.5,-10,0.3);
        glScalef(2.5, 1.6, 2);
        triangulo();
    glPopMatrix();
    //Triangulo inferior direito
    glPushMatrix();
        glTranslatef(3.7,-10,0.3);
        glRotatef(180,0,1,0);
        glScalef(2.5, 1.6, 2);
        triangulo();
    glPopMatrix();

    //PaletaDireita
    glPushMatrix();
        paleta();
    glPopMatrix();
    //Paleta Esquerda
    glPushMatrix();
        glTranslatef(-0.2,0,0.2);
        glRotatef(180,0,1,0);
        paleta();
    glPopMatrix();
}


void mesaPaintBall()
{
    mesaFixaJogo();
    mesaInferior();
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

    glPushMatrix();
        distanciaMesa();
    glPopMatrix();

    glPushMatrix();
        mesaPaintBall();
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
//        case 'z': angGiro += 1.0; break;
//        case 's': anda -= 0.05; break;
//        case 'w': anda += 0.05; break;
        case 'p': if (Porta2>=-8.6) Porta2 -= 0.05; break;
        case 'o': if (Porta2<-7.0) Porta2 += 0.05; break;
        case 'm': if (Porta1>=-90.0) Porta1 -= 1; break;
        case 'n': if (Porta1<=0.0) Porta1 += 1; break;
        case 'k': if (PortaRack>0) PortaRack -= 0.1; break;
        case 'l': if (PortaRack<=1.8) PortaRack += 0.1; break;
        case 'u': if (JanelaVerde>0) JanelaVerde -= 1.5; break; // 0
        case 'i': if (JanelaVerde<=160) JanelaVerde += 1.5; break;
        case 'h': if (JanelaBranca>0) JanelaBranca -= 0.1; break;
        case 'j': if (JanelaBranca<=1.6) JanelaBranca += 0.1; break;
        case 'v': if (PortaEstante>0) PortaEstante -= 1; break;
        case 'b': if (PortaEstante<=87) PortaEstante += 1; break;
        case 'q': exit(EXIT_SUCCESS); break;
   }
   glutPostRedisplay();   //exibe();
}

void gira() {
   teta += 3;
   glutPostRedisplay();   //exibe();
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
    glutPassiveMotionFunc(mouse);
    glutIdleFunc(gira);
    inicia();
    glutMainLoop();
}
