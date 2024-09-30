#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
#include<math.h>

using namespace std;
int pntX1=320,pntY1=240,r1=100,r2=200;

void plot(int x,int y){
    glBegin(GL_POINTS);
    glVertex2i(x+pntX1,y+pntY1);
    glEnd();
}

void Init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);
}

void midPointCircleAlgo(int r){
    int x=0;
    int y=r;
    float decision = 1 - r;
    plot(x,y);
    while (y>x){
        if (decision<0){
            x++;
            decision += 2*x + 1;
        }
        else{
            y--;
            x++;
            decision += 2*(x-y)+1;
        }
        plot(x,y);
        plot(x,-y);
        plot(-x,y);
        plot(-x,-y);
        plot(y,x);
        plot(-y,x);
        plot(y,-x);
        plot(-y,-x);
    }
}
void Line(int x1,int y1,int x2,int y2){
    float dy,dx,step,x,y,k,Xinc,Yinc;
    dx = x2-x1;
    dy = y2-y1;
    if (abs(dx)>abs(dy)){
        step = abs(dx);
    }
    else {
        step = abs(dy);
    }
    Xinc = dx/step;
    Yinc = dy/step;
    x = x1;
    y = y1;
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    for (k = 1;k<=step;k++){
        x = x + Xinc;
        y = y + Yinc;
        glBegin(GL_POINTS);
        glVertex2i(x,y);
    }
    glEnd();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0);
    glColor3f(0.0,1.0,0.0);
    Line(pntX1-r2*cos(3.14/6),pntY1-r1,pntX1,pntY1+r2);
    Line(pntX1,pntY1+r2,pntX1+r2*cos(3.14/6),pntY1-r1);
    Line(pntX1+r2*cos(3.14/6),pntY1-r1,pntX1-r2*cos(3.14/6),pntY1-r1);
    glColor3f(0.0,0.0,1.0);
    midPointCircleAlgo(r1);
    glColor3f(1.0,0.0,0.0);
    midPointCircleAlgo(r2);
    glFlush();
}

int main(int argc,char** argv){
    cout<<"Change";
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Pattern");
    glutDisplayFunc(display);
    Init();
    glutMainLoop();
    return 0;
}
