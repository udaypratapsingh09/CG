#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;
// Traffic light state constants
#define RED 0
#define YELLOW 1
#define GREEN 2

int stateCycle[4] = {0,1,1,2};
// red, yellow, yellow ,green

void drawCircle(float cx, float cy, float r) {
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 360; i++) {
            float theta = i * 3.1415926f / 180.0f;
            float x = r * cosf(theta);
            float y = r * sinf(theta);
            glVertex2f(x + cx, y + cy);
        }
        glEnd();
}

class Car{
public:
    float x,y;
    char direction;// n-> north,e->east,w->west,s->south
    float width = 0.08;
    float length = 0.15;
    float speed = 0.01;
//public:
    Car(char direction){
        this->direction = direction;
        if (direction == 'n') {
            this->y = 0.8;
            this->x = 0.01;
        }
        else if (direction == 's'){
            this->y = -0.8;
            this->x = -0.01;
        }
        else if (direction == 'w'){
            this->y = 0.01;
            this->x = -0.8;
        }
        else if (direction == 'e'){
            this->y = -0.01;
            this->x = 0.8;
        }
    }
    void draw(){
        if (direction=='n') {
            glColor3f(0.4,0.9,0.3);
            glRectd(this->x,this->y,this->x+this->width,this->y+this->length);
        }
        else if (direction=='s'){
            glColor3f(0.8,0.9,0.3);
            glRectd(this->x,this->y,this->x-this->width,this->y-this->length);
        }
        else if (direction=='w'){
            glColor3f(0.4,0.9,0.7);
            glRectd(this->x,this->y,this->x+this->length,this->y+this->width);
        }
        else if (direction=='e') {
            glColor3f(0.7,0.1,0.6);
            glRectd(this->x,this->y,this->x-this->length,this->y-this->width);
        }
    }
    void moveCar(int signal){
        if (direction=='n'){
            if (this->y > 0.20 || this->y < 0 || signal==GREEN){
                this->y -= this->speed;
            }
            if (this->y+this->length < -1.0)
                this->y = 1.8;
        }
        else if (direction=='s') {
            if (this->y < -0.20 || this->y > 0 || signal==GREEN){
                this->y += this->speed;
            }
            if (this->y-this->length > 1.0)
                this->y = -1.8;
        }
        else if (direction=='w') {
            if (this->x+this->length < -0.20 || this->x+this->length > 0 || signal==GREEN){
                this->x += this->speed;
            }
            if (this->x > 1.0)
                this->x = -1.8;
        }
        else if (direction=='e') {
            if (this->x-this->length > 0.20 || this->x-this->length < 0 || signal==GREEN){
                this->x -= this->speed;
            }
            if (this->x < -1.0)
                this->x = 1.8;
        }
    }
};

Car cars[4] = {
Car('n'),
Car('s'),
Car('e'),
Car('w')
};

class TrafficSignal {
private:
    // Utility to draw a circle (for traffic signal lights)
public:
    int id;         // Identifier for the signal (e.g., North, South, East, West)
    int state,stateOffset;      // Current state of the signal (RED, YELLOW, GREEN)
    float x, y; // Position of the signal on the screen
    bool isHorizontal;

    // Constructor
    TrafficSignal(int signalId = 0, float posX = 0.0f, float posY = 0.0f,int stateOffset=0,bool isHorizontal=false) {
        this->id = signalId;
        this->x = posX;
        this->y = posY;
        this->stateOffset = stateOffset;  // All signals start with Red light
        this->state = stateCycle[stateOffset];
        this->isHorizontal = isHorizontal;
    }

    // Method to draw the signal
        void drawSignal() {
        // Draw the dark rectangle (signal background)
        glColor3f(0.1f, 0.1f, 0.1f); // Dark color

        if (isHorizontal) {
            // Horizontal rectangle for east and west signals
            glRectf(x - 0.2f, y - 0.05f, x + 0.2f, y + 0.05f);
        } else {
            // Vertical rectangle for north and south signals
            glRectf(x - 0.05f, y - 0.2f, x + 0.05f, y + 0.2f);
        }

        // Draw the lights
        if (isHorizontal) {
            // For horizontal signals, draw lights horizontally
            // Red light
            if (state == RED) {
                glColor3f(1.0f, 0.0f, 0.0f); // Red
            } else {
                glColor3f(0.3f, 0.0f, 0.0f); // Dim red
            }
            drawCircle(x - 0.1f, y, 0.03f);

            // Yellow light
            if (state == YELLOW) {
                glColor3f(1.0f, 1.0f, 0.0f); // Yellow
            } else {
                glColor3f(0.3f, 0.3f, 0.0f); // Dim yellow
            }
            drawCircle(x, y, 0.03f);

            // Green light
            if (state == GREEN) {
                glColor3f(0.0f, 1.0f, 0.0f); // Green
            } else {
                glColor3f(0.0f, 0.3f, 0.0f); // Dim green
            }
            drawCircle(x + 0.1f, y, 0.03f);
        } else {
            // For vertical signals, draw lights vertically
            // Red light
            if (state == RED) {
                glColor3f(1.0f, 0.0f, 0.0f); // Red
            } else {
                glColor3f(0.3f, 0.0f, 0.0f); // Dim red
            }
            drawCircle(x, y + 0.1f, 0.03f);

            // Yellow light
            if (state == YELLOW) {
                glColor3f(1.0f, 1.0f, 0.0f); // Yellow
            } else {
                glColor3f(0.3f, 0.3f, 0.0f); // Dim yellow
            }
            drawCircle(x, y, 0.03f);

            // Green light
            if (state == GREEN) {
                glColor3f(0.0f, 1.0f, 0.0f); // Green
            } else {
                glColor3f(0.0f, 0.3f, 0.0f); // Dim green
            }
            drawCircle(x, y - 0.1f, 0.03f);
        }
    }
    // Method to change the signal's state
    void changeSignalStates(TrafficSignal signals[4]){
            // Change state for each signal
            this->stateOffset += 1;
            if (this->stateOffset==4) this->stateOffset=0;
            this->state = stateCycle[this->stateOffset];
    }
};

// Now define the global signals array with initialized positions
TrafficSignal signals[4] = {
    TrafficSignal(0, 0.20f, -0.40f,0),  // North
    TrafficSignal(1, -0.20f, 0.40f,1), // South
    TrafficSignal(2, -0.40f, -0.20f,2,true),  // East
    TrafficSignal(3, 0.40f, 0.20f,3,true)  // West
};
// Timer function to change the signals
void signalChange(int) {
    for (int i = 0; i < 4; i++) {
        signals[i].changeSignalStates(signals);  // Change state for each signal
    }
    glutPostRedisplay();                 // Redraw the scene
    glutTimerFunc(5000, signalChange, 0);       // Trigger state change after 5 seconds
}

void moveCars(int){
    for (int i = 0; i < 4; i++) {
        cars[i].moveCar(signals[i].state);
    }
    glutPostRedisplay();
    glutTimerFunc(50,moveCars,0);
}

void renderBitmapString(float x, float y, void *font, const char *string) {
    const char *c;
    glRasterPos2f(x, y);  // Set the position for the text
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);  // Draw each character
    }
}

void drawLegend() {
    // Red light with "STOP"
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    drawCircle(-0.93,0.87,0.03); // Red light
    renderBitmapString(-0.85,0.85,GLUT_BITMAP_HELVETICA_18, "STOP");

    // Green light with "GO"
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    drawCircle(-0.93,0.77,0.03);// Green light
    renderBitmapString(-0.85,0.75,GLUT_BITMAP_HELVETICA_18, "GO");

    // Yellow light with "WAIT"
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    drawCircle(-0.93,0.67,0.03); // Yellow light
    renderBitmapString(-0.85,0.65,GLUT_BITMAP_HELVETICA_18, "WAIT");

    // Rectangle with "CAR"
    glColor3f(0.7,0.1,0.6); // Car color
    glRectf(-0.95f, 0.55f, -0.85f, 0.6f); // Car
    renderBitmapString(-0.80,0.55,GLUT_BITMAP_HELVETICA_18, "CAR");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);        // Clear the screen
    glColor3f(0.7f,0.7f,0.7f);
    glRectd(-1.0,-0.1,0.0,0.1);
    glRectd(0.0,-0.1,1.0,0.1);
    glRectd(-0.1,-1.0,0.1,0.0);
    glRectd(-0.1,1.0,0.1,0.0);
    drawLegend();
    for (int i = 0; i < 4; i++) {
        signals[i].drawSignal();         // Draw each traffic signal
    }
    for (int i = 0; i < 4; i++) {
        cars[i].draw();         // Draw each traffic signal
    }
    glFlush();                           // Render the scene
}

void init() {
    glClearColor(0.59, 0.97, 1.0, 1.0);    // Set background color to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);    // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Traffic Signal Example");
    glutDisplayFunc(display);
    glutTimerFunc(5000, signalChange, 0);// Start the timer for signal state change
    glutTimerFunc(50,moveCars,0);
    init();
    glutMainLoop();
    return 0;
}
