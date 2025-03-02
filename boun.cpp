#include <GL/glut.h>
#include <iostream>

#define WIDTH 500
#define HEIGHT 500

float fillColor[3] = {0.0f, 1.0f, 0.0f};  // Green color for fill
float boundaryColors[5][3] = {
    {1.0f, 0.0f, 0.0f},  // Red
    {1.0f, 0.0f, 0.0f},  // red
    {0.0f, 0.0f, 1.0f},  // Blue
    {1.0f, 1.0f, 0.0f},  // Yellow
    {1.0f, 0.0f, 0.0f}   // red
};

void setPixel(int x, int y, float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getPixelColor(int x, int y, float color[3]) {
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    color[0] = pixel[0] / 255.0f;
    color[1] = pixel[1] / 255.0f;
    color[2] = pixel[2] / 255.0f;
}

bool isColorEqual(float color1[3], float color2[3]) {
    return (abs(color1[0] - color2[0]) < 0.01f) && 
           (abs(color1[1] - color2[1]) < 0.01f) && 
           (abs(color1[2] - color2[2]) < 0.01f);
}

bool isBoundaryColor(float color[3]) {
    for (int i = 0; i < 5; ++i) {
        if (isColorEqual(color, boundaryColors[i])) {
            return true;
        }
    }
    return false;
}

void boundaryFill(int x, int y, float fillColor[3], float boundaryColors[5][3]) {
    float pixelColor[3];
    getPixelColor(x, y, pixelColor);

    if (!isBoundaryColor(pixelColor) && !isColorEqual(pixelColor, fillColor)) {
        setPixel(x, y, fillColor);
        boundaryFill(x + 1, y, fillColor, boundaryColors);
        boundaryFill(x - 1, y, fillColor, boundaryColors);
        boundaryFill(x, y + 1, fillColor, boundaryColors);
        boundaryFill(x, y - 1, fillColor, boundaryColors);
    }
}

void drawPolygon() {
    glBegin(GL_LINES);

    // Define the vertices of the polygon
    int vertices[5][2] = { {100, 100}, {400, 100}, {450, 300}, {250, 400}, {50, 300} };

    // Draw the edges with different colors
    for (int i = 0; i < 5; ++i) {
        glColor3fv(boundaryColors[i]);
        glVertex2iv(vertices[i]);
        glVertex2iv(vertices[(i + 1) % 5]);
    }

    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPolygon();

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON or state == GLUT_DOWN) {
        // Convert from window coordinates to OpenGL coordinates
        int windowX = x;
        int windowY = HEIGHT - y;
        boundaryFill(windowX, windowY, fillColor, boundaryColors);
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Boundary Fill Algorithm with Polygon");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

