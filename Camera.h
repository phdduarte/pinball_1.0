#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

#define FORWARD 0
#define BACKWARD 1
#define RIGHT 2
#define LEFT 3

class Camera{

    private:
        double  eyeX;
        double  eyeY;
        double  eyeZ;

        double  centerX;
        double  centerY;
        double  centerZ;

        double  upX;
        double  upY;
        double  upZ;

        double  fovy;
        double  aspect;
        double  zNear;
        double  zFar;

        float mouseDirection[3];

        bool move[4];

    public:
        Camera();
        Camera(double,double,double,double,double,double,double,double,double,double,double,double,double);

        void setEyeX(double);
        void setEyeY(double);
        void setEyeZ(double);
        void setCenterX(double);
        void setCenterY(double);
        void setCenterZ(double);
        void setUpX(double);
        void setUpY(double);
        void setUpZ(double);
        void setFovy(double);
        void setAspect(double);
        void setZNear(double);
        void setZFar(double);

        double getEyeX();
        double getEyeY();
        double getEyeZ();
        double getCenterX();
        double getCenterY();
        double getCenterZ();
        double getUpX();
        double getUpY();
        double getUpZ();
        double getFovy();
        double getAspect();
        double getZNear();
        double getZFar();

        void setPerspective();
        void setPerspective(double,double,double,double);
        void film();
        void debug();

        void mouseMotionListener(int x, int y);
        void keyboardListener(unsigned char c, int x, int y);
};
