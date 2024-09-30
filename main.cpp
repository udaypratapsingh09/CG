#include <GL/glut.h>
#include <bits/stdc++.h>

#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

int pntX1,pntY1,choice = 0,edges;
vector<int> pntX;
vector<int> pntY;
int tx=100,ty=100;
double sx=1.5,sy=1.8;
double angle=45.0;
double theta;

double round(double d){
    return floor(d+0.5);
}

void drawPolygon(){
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    for (int i=0;i<edges;i++){
        glVertex2i(pntX[i],pntY[i]);
    }
    glEnd();
}

void drawPolygonTrans(int x,int y){
    glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.0);
    for (int i=0;i<edges;i++){
        glVertex2i(pntX[i]+x,pntY[i]+y);
    }
    glEnd();
}

void drawPolygonScale(double x,double y){
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,1.0);
    for (int i=0;i<edges;i++){
        glVertex2i(round(pntX[i]*x),round(pntY[i]*y));
    }
    glEnd();
}

void drawPolygonRotation(double angle){
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.3,0.5);
    theta = angle*3.14159/180;
    for (int i=0;i<edges;i++){
        glVertex2i(round((pntX[i]*cos(theta))-(pntY[i]*sin(theta))),round((pntX[i]*sin(theta))+(pntY[i]*cos(theta))));
    }
    glEnd();
}

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0,0.0,0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-640.0,640.0,-480.0,480.0);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);

    drawPolygon();
    if (choice==1){
        drawPolygonTrans(tx,ty);
    }
    else if (choice==2){
        drawPolygonScale(sx,sy);
    }
    else if (choice==3){
        drawPolygonRotation(angle);
    }
    glFlush();
}

void transformMenu(int id){
    choice = id;
    if (choice==1){
        cout<<"Enter the translation factor for X and Y: ";
        cin>>tx>>ty;
    }
    else if (choice==2){
        cout<<"Enter the scaling factor for X and Y: ";
        cin>>sx>>sy;
    }
    else if (choice==3){
        cout<<"Enter the angle for rotation: ";
        cin>>angle;
        theta = angle*3.1416/180;
    }

    if (choice==6) exit(0);
    glutPostRedisplay();
}

void createMenu(){
    int s_id = glutCreateMenu(transformMenu);
    glutAddMenuEntry("Translate",1);
    glutAddMenuEntry("Scale",2);
    glutAddMenuEntry("Rotate",3);
    glutAddMenuEntry("Exit",6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc,char** argv){
    cout<<"\n\nFor Polygon\n";
    cout<<"Enter the number of edges: "<<endl;
    cin>>edges;

    for (int i=0;i<edges;i++){
        cout<<"Enter co-ordinates for vertex "<<i+1<<" : ";
        cin>>pntX1>>pntY1;
        pntX.push_back(pntX1);
        pntY.push_back(pntY1);
    }
//    cout<<"Enter your choice:\n\n";
//    cout<<"1. Translation"<<endl;
//    cout<<"2. Scaling"<<endl;
//    cout<<"3. Rotation"<<endl;
//    cout<<"6. Exit"<<endl;
//    cin>>choice;
//    if (choice==6) return 0;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Extended Basic Transformations");
    glutDisplayFunc(display);
    init();
    createMenu();
    glutMainLoop();
}
