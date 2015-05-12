#include "Camera.h"

Camera::Camera(){
    setEyeX(0.0);
    setEyeY(0.0);
    setEyeZ(0.0);
    setCenterX(0.0);
    setCenterY(0.0);
    setCenterZ(0.0);
    setUpX(0.0);
    setUpY(0.0);
    setUpZ(0.0);
    setFovy(0.0);
    setAspect(0.0);
    setZNear(0.0);
    setZFar(0.0);

    mouseDirection[0] = 0;
    mouseDirection[1] = 1;
    mouseDirection[2] = 0;

    glMatrixMode(GL_MODELVIEW);

    move[0] = false;
    move[1] = false;
    move[2] = false;
    move[3] = false;
}

Camera::Camera(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX,double upY,double upZ, double fovy, double aspect, double zNear, double  zFar){
    setEyeX(eyeX);
    setEyeY(eyeY);
    setEyeZ(eyeZ);
    setCenterX(centerX);
    setCenterY(centerY);
    setCenterZ(centerZ);
    setUpX(upX);
    setUpY(upY);
    setUpZ(upZ);
    setFovy(fovy);
    setAspect(aspect);
    setZNear(zNear);
    setZFar(zFar);

    mouseDirection[0] = 180;
    mouseDirection[1] = 90;
    mouseDirection[2] = 0;

    glMatrixMode(GL_MODELVIEW);

    move[0] = false;
    move[1] = false;
    move[2] = false;
    move[3] = false;
}

void Camera::setEyeX(double eyeX){
    this->eyeX = eyeX;
}
void Camera::setEyeY(double eyeY){
    this->eyeY = eyeY;
}
void Camera::setEyeZ(double eyeZ){
    this->eyeZ = eyeZ;
}
void Camera::setCenterX(double centerX){
    this->centerX = centerX;
}
void Camera::setCenterY(double centerY){
    this->centerY = centerY;
}
void Camera::setCenterZ(double centerZ){
    this->centerZ = centerZ;
}
void Camera::setUpX(double upX){
    this->upX = upX;
}
void Camera::setUpY(double upY){
    this->upY = upY;
}
void Camera::setUpZ(double upZ){
    this->upZ = upZ;
}
void Camera::setFovy(double fovy){
    this->fovy = fovy;
}
void Camera::setAspect(double aspect){
    this->aspect = aspect;
}
void Camera::setZNear(double zNear){
    this->zNear = zNear;
}
void Camera::setZFar(double zFar){
    this->zFar = zFar;
}


double Camera::getEyeX(){
    return this->eyeX;
}
double Camera::getEyeY(){
    return this->eyeY;
}
double Camera::getEyeZ(){
    return this->eyeZ;
}
double Camera::getCenterX(){
    return this->centerX;
}
double Camera::getCenterY(){
    return this->centerY;
}
double Camera::getCenterZ(){
    return this->centerZ;
}
double Camera::getUpX(){
    return this->upX = upX;
}
double Camera::getUpY(){
    return this->upY;
}
double Camera::getUpZ(){
    return this->upZ;
}
double Camera::getFovy(){
    return this->fovy;
}
double Camera::getAspect(){
    return this->aspect;
}
double Camera::getZNear(){
    return this->zNear;
}
double Camera::getZFar(){
    return this->zFar;
}

void Camera::setPerspective(){
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(getFovy(),getAspect(),getZNear(),getZFar());
    glutSetCursor(GLUT_CURSOR_NONE);
}
void Camera::setPerspective(double fovy,double aspect,double zNear,double zFar){
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);

    glMatrixMode(GL_MODELVIEW);

    setFovy(fovy);
    setAspect(aspect);
    setZNear(zNear);
    setZFar(zFar);
}
void Camera::film(){

    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int timeInterval = 1;//currentTime - previousTime;

    float tmpEyeX, tmpEyeY, tmpEyeZ;
    tmpEyeX = sin(mouseDirection[1]*M_PI/180)*sin(mouseDirection[0]*M_PI/180);
    tmpEyeZ = sin(mouseDirection[1]*M_PI/180)*cos(mouseDirection[0]*M_PI/180);
    tmpEyeY = cos(mouseDirection[1]*M_PI/180);

    if(move[FORWARD]){
        setEyeX(getEyeX() + (timeInterval * tmpEyeX / 6));
    	setEyeY(getEyeY() + (timeInterval * tmpEyeY / 6));
    	setEyeZ(getEyeZ() + (timeInterval * tmpEyeZ / 6));
    }
    if(move[BACKWARD]){
        setEyeZ( getEyeZ() - (timeInterval * tmpEyeZ / 6));
    	setEyeY( getEyeY() - (timeInterval * tmpEyeY / 6));
    	setEyeX( getEyeX() - (timeInterval * tmpEyeX / 6));
    }
    if(move[LEFT]){
        setEyeX( getEyeX() + (timeInterval * sin((mouseDirection[0]+90)*M_PI/180) / 6));
	    setEyeZ( getEyeZ() + (timeInterval * cos((mouseDirection[0]+90)*M_PI/180) / 6));
    }
    if(move[RIGHT]){
        setEyeX( getEyeX() - (timeInterval * sin((mouseDirection[0]+90)*M_PI/180) / 6));
	    setEyeZ( getEyeZ() - (timeInterval * cos((mouseDirection[0]+90)*M_PI/180) / 6));
    }

    glLoadIdentity();

    setCenterX(getEyeX()+tmpEyeX);
    setCenterY(getEyeY()+tmpEyeY);
    setCenterZ(getEyeZ()+tmpEyeZ);

	gluLookAt(
        getEyeX(),getEyeY(),getEyeZ(),
	    getCenterX(),getCenterY(),getCenterZ(),
	    0.0f, 1.0f,  0.0f
    );

    int xc = glutGet(GLUT_WINDOW_WIDTH)/2;
    int yc = glutGet(GLUT_WINDOW_HEIGHT)/2;

    glutWarpPointer(xc,yc);

    move[0] = false;
    move[1] = false;
    move[2] = false;
    move[3] = false;
}


void Camera::mouseMotionListener(int x, int y){
    int xc = glutGet(GLUT_WINDOW_WIDTH)/2;
    int yc = glutGet(GLUT_WINDOW_HEIGHT)/2;

    mouseDirection[0] -= (x - xc) * 0.1;
    mouseDirection[1] += (y - yc) * 0.1;
//    mouseDirection[1] = min(179.9f,max(mouseDirection[1],0.9f));

//    mouseDirection[1] = max(45.f,max(mouseDirection[1],0.9f));
//    mouseDirection[1] = min(135.f,max(mouseDirection[1],0.9f));

}

void Camera::keyboardListener(unsigned char c, int x, int y){
    switch(c){
        case 'w':{
            move[FORWARD] = true;
            break;
        }
        case 's':{
            move[BACKWARD] = true;
            break;
        }
        case 'd':{
            move[RIGHT] = true;
            break;
        }
        case 'a':{
            move[LEFT] = true;
            break;
        }
        //case 'q':{
        //    exit(0);
        //}
    }
}
