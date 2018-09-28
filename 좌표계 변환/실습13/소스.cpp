#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Timerfunction(int);
void InitialShape();

struct Shape {
	bool is_triangle = true;
	bool is_now_morp = false;
	bool morp_bigger = true;
	float size = 150;
	int rotate_shape = 0;
	int position_shape = 0;

	int on_which_line = 0;
	int movestack = 0;
};
struct Line {
	float startX, startY, endX, endY;
	bool is_live = true;
};


int shape_mode = 0;	// 0 원 1 사인 2 회오리 3 지그재그 4 경로그리기
int line_index = -1;
bool drewline_moveswitch = false;

int animation_speed = 1000;

float DeltaX = 0, DeltaY = 0;
float bigTriangle_rotate = 0;
float smallTriangle_rotate = 0;

Shape shape;
Line lines[4];

void main(int argc, char** argv) // 윈도우 출력하고 출력함수 설정 
{
	// 초기화 함수들 
	glutInit(&argc, argv); // glut 초기화 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Tiles"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(DrawScene); // 출력 함수의 지정 
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정 
	glutTimerFunc(animation_speed / 60, Timerfunction, 1);
	glutKeyboardFunc(Keyboard);	// 키보드 입력 받기

	//shape.cx = 0;
	//shape.cy = 200;

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 
	glMatrixMode(GL_MODELVIEW);

	glPointSize(3.0);

	glPushMatrix();
	// 중심선
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 300, 0);
	glVertex3f(0, -300, 0);
	glVertex3f(400, 0, 0);
	glVertex3f(-400, 0, 0);
	glEnd();

	glRotatef(bigTriangle_rotate, 0, 1.0, 0);
	glPushMatrix();

	glBegin(GL_LINE_LOOP);
	glVertex3f(shape.size * cos(90.0 / 180.0 * PI), shape.size * sin(90.0 / 180.0 * PI), 0);
	glVertex3f(shape.size * cos(210.0 / 180.0 * PI), shape.size * sin(210.0 / 180.0 * PI), 0);
	glVertex3f(shape.size * cos(330.0 / 180.0 * PI), shape.size * sin(330.0 / 180.0 * PI), 0);
	glEnd();

	if (shape.movestack<=60) {
		glTranslated(shape.size * cos(90.0 / 180.0 * PI) + ((shape.size * cos(210.0 / 180.0 * PI) - shape.size * cos(90.0 / 180.0 * PI)) / 60.0*(shape.movestack - 0)),
			shape.size * sin(90.0 / 180.0 * PI) + ((shape.size * sin(210.0 / 180.0 * PI) - shape.size * sin(90.0 / 180.0 * PI)) / 60.0*(shape.movestack - 0)), 0);
	}
	else if (shape.movestack <= 120) {
		glTranslated(shape.size * cos(210.0 / 180.0 * PI) + ((shape.size * cos(330.0 / 180.0 * PI) - shape.size * cos(210.0 / 180.0 * PI)) / 60.0*(shape.movestack - 60)),
			shape.size * sin(210.0 / 180.0 * PI) + ((shape.size * sin(330.0 / 180.0 * PI) - shape.size * sin(210.0 / 180.0 * PI)) / 60.0*(shape.movestack - 60)), 0);
	}
	else if (shape.movestack <= 180) {
		glTranslated(shape.size * cos(330.0 / 180.0 * PI) + ((shape.size * cos(90.0 / 180.0 * PI) - shape.size * cos(330.0 / 180.0 * PI)) / 60.0*(shape.movestack - 120)),
			shape.size * sin(330.0 / 180.0 * PI) + ((shape.size * sin(90.0 / 180.0 * PI) - shape.size * sin(330.0 / 180.0 * PI)) / 60.0*(shape.movestack - 120)), 0);
	}

	glColor3f(1.0, 1.0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(20 * cos(90.0 / 180.0 * PI), 20 * sin(90.0 / 180.0 * PI), 0);
	glVertex3f(20 * cos(210.0 / 180.0 * PI), 20 * sin(210.0 / 180.0 * PI), 0);
	glVertex3f(20 * cos(330.0 / 180.0 * PI), 20 * sin(330.0 / 180.0 * PI), 0);
	glEnd();
	glPopMatrix();

	glRotatef(90, 0, 1.0, 0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(shape.size * cos(90.0 / 180.0 * PI), shape.size * sin(90.0 / 180.0 * PI), 0);
	glVertex3f(shape.size * cos(210.0 / 180.0 * PI), shape.size * sin(210.0 / 180.0 * PI), 0);
	glVertex3f(shape.size * cos(330.0 / 180.0 * PI), shape.size * sin(330.0 / 180.0 * PI), 0);
	glEnd();

	if (shape.movestack <= 60) {
		glTranslated(shape.size * cos(90.0 / 180.0 * PI) + ((shape.size * cos(210.0 / 180.0 * PI) - shape.size * cos(90.0 / 180.0 * PI)) / 60.0*(shape.movestack - 0)),
			shape.size * sin(90.0 / 180.0 * PI) + ((shape.size * sin(210.0 / 180.0 * PI) - shape.size * sin(90.0 / 180.0 * PI)) / 60.0*(shape.movestack - 0)), 0);
	}
	else if (shape.movestack <= 120) {
		glTranslated(shape.size * cos(210.0 / 180.0 * PI) + ((shape.size * cos(330.0 / 180.0 * PI) - shape.size * cos(210.0 / 180.0 * PI)) / 60.0*(shape.movestack - 60)),
			shape.size * sin(210.0 / 180.0 * PI) + ((shape.size * sin(330.0 / 180.0 * PI) - shape.size * sin(210.0 / 180.0 * PI)) / 60.0*(shape.movestack - 60)), 0);
	}
	else if (shape.movestack <= 180) {
		glTranslated(shape.size * cos(330.0 / 180.0 * PI) + ((shape.size * cos(90.0 / 180.0 * PI) - shape.size * cos(330.0 / 180.0 * PI)) / 60.0*(shape.movestack - 120)),
			shape.size * sin(330.0 / 180.0 * PI) + ((shape.size * sin(90.0 / 180.0 * PI) - shape.size * sin(330.0 / 180.0 * PI)) / 60.0*(shape.movestack - 120)), 0);
	}

	glColor3f(0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(20 * cos(90.0 / 180.0 * PI), 20 * sin(90.0 / 180.0 * PI), 0);
	glVertex3f(20 * cos(210.0 / 180.0 * PI), 20 * sin(210.0 / 180.0 * PI), 0);
	glVertex3f(20 * cos(330.0 / 180.0 * PI), 20 * sin(330.0 / 180.0 * PI), 0);
	glEnd();

	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h) // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutLeaveMainLoop();
		break;
	case 's':
		shape.size++;
		break;
	case 'S':
		shape.size--;
		break;
	case 'y':
		bigTriangle_rotate += 5;
		smallTriangle_rotate += 1;
		break;
	case 'Y':
		bigTriangle_rotate -= 5;
		smallTriangle_rotate += 1;
		break;
	}
	
}


GLvoid Timerfunction(int value) {
	switch (value)
	{
	case 1:
		shape.movestack = (shape.movestack + 1) % 180;
		glutTimerFunc(animation_speed / 60, Timerfunction, 1);
		glutPostRedisplay();
		break;
	}
}

void InitialShape()
{
	shape.is_triangle = true;
	shape.is_now_morp = false;
	shape.morp_bigger = true;
	shape.size = 20;
	shape.rotate_shape = 0;
	shape.position_shape = 0;
	bigTriangle_rotate = 0;
	line_index = -1;
	shape.on_which_line = 0;
	shape.movestack = 0;
	drewline_moveswitch = false;
}
