#include <GL/glut.h>
#include <math.h>

bool isNight = false;
float cloudX = -400; // بداية من الشمال

void Background() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); //Day
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-450, 450, -300, 300);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'n' || key == 'N') {
        isNight = true;
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f); //Night
    }
    if (key == 'l' || key == 'L') {
        isNight = false;
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f); //Day
    }
    if (key == 27) exit(0);

    glutPostRedisplay();
}

void drawCircle(float cx, float cy, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159f / 180.0f;
        float x = cx + radius * cos(theta);
        float y = cy + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawSquare(float x, float y, float size, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x - size/2, y - size/2);
        glVertex2f(x + size/2, y - size/2);
        glVertex2f(x + size/2, y + size/2);
        glVertex2f(x - size/2, y + size/2);
    glEnd();
}

void drawHouse(float x, float y)
{
    //Main Square
    glColor3f(0.96f, 0.87f, 0.70f);
    glBegin(GL_QUADS);
        glVertex2f(x-60, y);
        glVertex2f(x+60, y);
        glVertex2f(x+60, y+80);
        glVertex2f(x-60, y+80);
    glEnd();

    //Triangle
    glColor3f(0.4f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x-80, y+80);
        glVertex2f(x+80, y+80);
        glVertex2f(x, y+140);
    glEnd();

    //Door
    glColor3f(0.25f, 0.13f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(x-15, y);
        glVertex2f(x+15, y);
        glVertex2f(x+15, y+50);
        glVertex2f(x-15, y+50);

    glEnd();
    if (isNight) {
        glColor3f(1.0f, 1.0f, 0.0f);
    } else {
        glColor3f(0.7f, 0.9f, 1.0f);
    }

    //L window
    glBegin(GL_QUADS);
        glVertex2f(x-45, y+40);
        glVertex2f(x-20, y+40);
        glVertex2f(x-20, y+65);
        glVertex2f(x-45, y+65);
    glEnd();

    //R window
    glBegin(GL_QUADS);
        glVertex2f(x+20, y+40);
        glVertex2f(x+45, y+40);
        glVertex2f(x+45, y+65);
        glVertex2f(x+20, y+65);
    glEnd();
}
void drawCloud(float x, float y) {
    drawCircle(x, y, 20, 1, 1, 1);
    drawCircle(x+20, y+10, 25, 1, 1, 1);
    drawCircle(x+40, y, 20, 1, 1, 1);
}
void update() {
    cloudX += 0.04; // سرعة الحركة

    if (cloudX > 450) {
        cloudX = -450; // ترجع من الأول
    }

    glutPostRedisplay();
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);


    if (!isNight) {
        drawCircle(300, 200, 50, 1.0f, 1.0f, 0.0f);
    } else {
        drawCircle(300, 200, 50, 0.9f, 0.9f, 0.9f);
        drawCircle(320, 200, 50, 0.0f, 0.0f, 0.2f);
    }
    drawCloud(cloudX, 200);
drawCloud(cloudX + 200, 230);

    //Ground
    drawSquare(0, -600, 900, 0, 0.6, 0);


    //Houses
drawHouse(-310, -200); // بيت على الشمال
drawHouse(250, -200);  // بيت على اليمين

    //Tree
  // Tree
glColor3f(0.25f, 0.13f, 0.05f);
glBegin(GL_QUADS);
    glVertex2f(-200, -40);
    glVertex2f(-180, -40);
    glVertex2f(-180, -200);
    glVertex2f(-200, -200);
glEnd();

// leaves فوق الجذع مباشرة
drawCircle(-190, -60, 40, 0, 0.6, 0);


    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Project");

    Background();

    glutDisplayFunc(Draw);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(update);

    glutMainLoop();
    return 0;
}
