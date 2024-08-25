#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;
int flag=0;
int X_MAX=500,Y_MAX=500,X_MIN=0,Y_MIN=0;

void init()
{
    gluOrtho2D(0, 500, 0, 500);
}

struct Vertex{
    int x,y;
};


class Poly{
private:
    int numSides;
    vector<Vertex> vertices;
    vector<pair<Vertex,Vertex>> edges;
    vector<vector<int>> rowIntersections;
    void getIntersections(){
        for (int y=Y_MIN;y<=Y_MAX;y++){
//          Get intersections
            int f=0;
            vector<int> intersections;
            for (int i=0;i<numSides;i++){
                Vertex v1 = edges[i].first;
                Vertex v2 = edges[i].second;
                int x_intersect;
                if (y==v1.y && y==v2.y) continue;
                if (v2.y<y || v1.y>y) continue;
                else if (i==v1.y) {
                    x_intersect = v1.x;
                    if (f!=1) intersections.emplace_back(x_intersect);
                    f=1;
                    continue;
                }
                else if (i==v2.y) {
                    x_intersect = v2.x;
                    if (f!=-1) intersections.emplace_back(x_intersect);
                    f=-1;
                    continue;
                }
                f=0;
                float slope;
                if (v1.x==v2.x){
                    x_intersect = v1.x;
                    intersections.emplace_back(x_intersect);
                }
                else {
                    slope = (v2.y-v1.y)/(v2.x-v1.x);
                    x_intersect = (y-v1.y)/slope + v1.x;
                    intersections.emplace_back(x_intersect);
                }
            }
            sort(intersections.begin(),intersections.end());
            rowIntersections.emplace_back(intersections);
        }
    }
 public:
    Poly(vector<Vertex> vertices){
        this->vertices = vertices;
        this->numSides=vertices.size();
        for (int i=0;i<numSides;i++){
            Vertex v1 = this->vertices[i];
            Vertex v2 = this->vertices[(i+1)%numSides];
            if (v1.y>v2.y) swap(v1,v2);
            pair<Vertex,Vertex> edge = {v1,v2};
            this->edges.emplace_back(edge);
        }
        getIntersections();
    }

    void draw(){
        glBegin(GL_LINE_LOOP);
        for (auto vertex:vertices){
            glVertex2i(vertex.x,vertex.y);
        }
        glEnd();
    }

    void fillPoly(){
        glPointSize(4.0);
        for (int y=Y_MIN;y<=Y_MAX;y++){
            vector<int> intersections = rowIntersections[y];
            int n = intersections.size();
            for (int i=0;i<n;i+=2){
                glBegin(GL_POINTS);
                for (int x=intersections[i];x<intersections[i+1];x++){
                    glVertex2i(x, y);
                }
                glEnd();
            }
        }
        glFlush();
    }
};

Poly p1 = Poly({{100,200},{100,100},{200,100},{200,200},{150,150} });
void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    p1.draw();
    if (flag==1)
        p1.fillPoly();
    glFlush();
}

void ScanMenu(int id){
    if (id == 1)
        flag = 1;
    else if (id == 2)
        flag = 0;
    else
            exit(0);
    glutPostRedisplay();
}

void createmenu(){
    int s_id = glutCreateMenu(ScanMenu);
    glutAddMenuEntry("ScanLine Algorithm", 1);
    glutAddMenuEntry("Stop", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE || GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Scan line alorithm");
    createmenu();
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
