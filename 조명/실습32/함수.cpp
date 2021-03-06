#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::Draw_Ball()
{
	GLfloat a[] = { 0.2,0.2,0.2,1.0 };
	GLfloat d[] = { 0.8,0.8,0.8,1.0 };
	glPushMatrix();

	glTranslatef(100 * sin(moon_degree / 180.0*PI), 0, -100 * cos(moon_degree / 180.0*PI));

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WhiteLight);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0f);
	glutSolidSphere(50, 30, 30);
	glPopMatrix();
}

GLvoid CRun_time_Framework::Draw_Cone()
{
	//glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(light[0].position[0], light[0].position[1], light[0].position[2]);
	glRotatef(180 - light[0].degree, 0, 1, 0);
	gluCylinder(qobj, 20, 0.0, 20, 20, 8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(light[1].position[0], light[1].position[1], light[1].position[2]);
	glRotatef(180 - light[1].degree, 0, 1, 0);
	gluCylinder(qobj, 20, 0.0, 20, 20, 8);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

GLvoid CRun_time_Framework::Init_Light()
{
	light[0].degree = 90.0;
	light[0].AmbientColor[1] = 0.2;
	light[0].DiffuseColor[1] = 0.8;

	light[1].degree = 270.0;
	light[1].AmbientColor[0] = 0.2;
	light[1].DiffuseColor[0] = 0.8;
	return GLvoid();
}

GLvoid CRun_time_Framework::UpdateLight()
{
	light[0].position[0] = 300.0*sin(light[0].degree / 180.0*PI);
	light[0].position[2] = -300.0*cos(light[0].degree / 180.0*PI);
	light[1].position[0] = 300.0*sin(light[1].degree / 180.0*PI);
	light[1].position[2] = -300.0*cos(light[1].degree / 180.0*PI);
	return GLvoid();
}

GLvoid CRun_time_Framework::Draw_Ground()
{
	glPushMatrix();
	glTranslatef(0, -300, 0);
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) {
			glBegin(GL_QUADS);
			glVertex3f(ground[i][j].left, 0, ground[i][j].top);
			glVertex3f(ground[i][j].right, 0, ground[i][j].top);
			glVertex3f(ground[i][j].right, 0, ground[i][j].bottom);
			glVertex3f(ground[i][j].left, 0, ground[i][j].bottom);
			glEnd();
		}
	}
	glPopMatrix();
}

GLvoid CRun_time_Framework::Draw_Piramid()
{
	GLfloat a[] = { 0.2,0.2,0.2,1.0 };
	GLfloat d[] = { 0.8,0.8,0.8,1.0 };

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WhiteLight);

	glTranslatef(0, -300, 0);
	glColor3f(1, 1, 1);
	//왼쪽위
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-360, 40, -360);
		glVertex3f(ground[4][4].right, 0, ground[4][4].bottom);
		glVertex3f(ground[4][0].left, 0, ground[4][0].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-360, 40, -360);
		glVertex3f(ground[4][0].left, 0, ground[4][0].bottom);
		glVertex3f(ground[0][0].left, 0, ground[0][0].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-360, 40, -360);
		glVertex3f(ground[0][0].left, 0, ground[0][0].top);
		glVertex3f(ground[0][4].right, 0, ground[0][4].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(-360, 40, -360);
		glVertex3f(ground[0][4].right, 0, ground[0][4].top);
		glVertex3f(ground[4][4].right, 0, ground[4][4].bottom);
		glEnd();
	}
	//오른쪽위
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(360, 40, -360);
		glVertex3f(ground[4][49].right, 0, ground[4][49].bottom);
		glVertex3f(ground[4][45].left, 0, ground[4][45].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(360, 40, -360);
		glVertex3f(ground[4][45].left, 0, ground[4][45].bottom);
		glVertex3f(ground[0][45].left, 0, ground[0][45].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(360, 40, -360);
		glVertex3f(ground[0][45].left, 0, ground[0][45].top);
		glVertex3f(ground[0][49].right, 0, ground[0][49].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(360, 40, -360);
		glVertex3f(ground[0][49].right, 0, ground[0][49].top);
		glVertex3f(ground[4][49].right, 0, ground[4][49].bottom);
		glEnd();
	}
	//왼쪽아래
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-360, 40, 360);
		glVertex3f(ground[49][4].right, 0, ground[49][4].bottom);
		glVertex3f(ground[49][0].left, 0, ground[49][0].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-360, 40, 360);
		glVertex3f(ground[49][0].left, 0, ground[49][0].bottom);
		glVertex3f(ground[45][0].left, 0, ground[45][0].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-360, 40, 360);
		glVertex3f(ground[45][0].left, 0, ground[45][0].top);
		glVertex3f(ground[45][4].right, 0, ground[45][4].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(-360, 40, 360);
		glVertex3f(ground[45][4].right, 0, ground[45][4].top);
		glVertex3f(ground[49][4].right, 0, ground[49][4].bottom);
		glEnd();
	}
	//오른쪽아래
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(360, 40, 360);
		glVertex3f(ground[49][49].right, 0, ground[49][49].bottom);
		glVertex3f(ground[49][45].left, 0, ground[49][45].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(360, 40, 360);
		glVertex3f(ground[49][45].left, 0, ground[49][45].bottom);
		glVertex3f(ground[45][45].left, 0, ground[45][45].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(360, 40, 360);
		glVertex3f(ground[45][45].left, 0, ground[45][45].top);
		glVertex3f(ground[45][49].right, 0, ground[45][49].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(360, 40, 360);
		glVertex3f(ground[45][49].right, 0, ground[45][49].top);
		glVertex3f(ground[49][49].right, 0, ground[49][49].bottom);
		glEnd();
	}
	//가운데
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0, 200, 0);
		glVertex3f(ground[29][29].right, 0, ground[29][29].bottom);
		glVertex3f(ground[29][20].left, 0, ground[29][20].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(0, 200, 0);
		glVertex3f(ground[29][20].left, 0, ground[29][20].bottom);
		glVertex3f(ground[20][20].left, 0, ground[20][20].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0, 200, 0);
		glVertex3f(ground[20][20].left, 0, ground[20][20].top);
		glVertex3f(ground[20][29].right, 0, ground[20][29].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0, 200, 0);
		glVertex3f(ground[20][29].right, 0, ground[20][29].top);
		glVertex3f(ground[29][29].right, 0, ground[29][29].bottom);
		glEnd();
	}

	glPopMatrix();
}
