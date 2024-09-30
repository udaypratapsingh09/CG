#include<GL/glut.h>
#include<stdio.h>
#include<iostream>

using namespace std;

void display();
float xmin = -100;
float ymin = -100;
float xmax = 100;
float ymax = 100;
float xd1,yd1,xd2,yd2; // line 1
float xd3,yd3,xd4,yd4; // line 2
float xd5,yd5,xd6,yd6; // line 3

void init(void){
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);
}

int code(float x,float y){
    int c=0;
    if (y>ymax) c=8;
    if (y<ymin) c=4;
    if (x>xmax) c=c|2;
    if (x<xmin) c=c|1;
    return c;
}

void cohenLine(float& x1,float& y1,float& x2,float& y2){
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m = (y2-y1)/(x2-x1);
    while ((c1|c2)>0){
        if ((c1&c2)>0){
            x1 = x2;
            y1 = y2;
            break;
        }
        float xi=x1;
        float yi=y1;
        int c = c1;
        if (c==0){
            c=c2;
            xi=x2;
            yi=y2;
        }
        float x,y;
        if ((c&8)>0) //point is above clip rectangle
        {
            y=ymax;
            x=xi + 1.0/m*(ymax-yi);
        }
        else if ((c&4)>0) // point is below clip rectangle
        {
            y=ymin;
            x=xi+1.0/m*(ymin-yi);
        }
        if ((c&2)>0)//point is to the right of clip rectangle
        {
            x=xmax;
            y=yi+m*(xmax-xi);
        }
        else if ((c&1)>0)//point is to the left of the clip rectangle
        {
            x=xmin;
            y=yi+m*(xmin-xi);
        }
        if (c==c2){
            x2=x;
            y2=y;
            c2=code(x2,y2);
        }
        else{
            x1 = x;
            y1 = y;
            c1 = code(x1,y1);
        }
    }
    display();
}

void mykey(unsigned char key,int x,int y){
    if (key=='c'){
        cohenLine(xd1,yd1,xd2,yd2);
        cohenLine(xd3,yd3,xd4,yd4);
        cohenLine(xd5,yd5,xd6,yd6);
        glFlush();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,1.0,0.0);

    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin,ymin);
    glVertex2i(xmin,ymax);
    glVertex2i(xmax,ymax);
    glVertex2i(xmax,ymin);
    glEnd();

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(xd1,yd1);
    glVertex2i(xd2,yd2);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(xd3,yd3);
    glVertex2i(xd4,yd4);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(xd5,yd5);
    glVertex2i(xd6,yd6);
    glEnd();
    glFlush();
}

int main(int argc,char** argv)
{
//    cout<<"Line 1"<<endl;
//    cin>>xd1>>yd1>>xd2>>yd2;
    xd1 = 130,yd1=100;
    xd2 = 250,yd2=250;
    xd3 = -40,yd3=-60;
    xd4 = 80,yd4=90;
    xd5 = 40,yd5=-120;
    xd6 = 150,yd6=50;
    glutInit(&argc,argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Clipping");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}
