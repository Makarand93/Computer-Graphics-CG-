#include <GL/glut.h>
#include <iostream>
#include <cmath>


void drawDottedLineDDA(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        
        if (i % 4 == 0) {
            glVertex2i(round(x), round(y));
        }
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
    glFlush();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

   
    int x1 = 50, y1 = 100, x2 = 300, y2 = 400;
    drawDottedLineDDA(x1, y1, x2, y2);
}

// Initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glColor3f(1.0, 1.0, 1.0);          // Set drawing color to white
    glPointSize(2.0);                  // Set point size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Dotted Line Drawing Algorithm");
    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
