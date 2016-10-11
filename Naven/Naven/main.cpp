#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

//float zNear = 0.1, zFar = 500;
//float angulo, aspecto;
int largura_janela = 800, altura_janela = 600;

void visualizacao(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(angulo, aspecto, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void teclado(unsigned char key, int x, int y){
	switch(key){
	case 27: 
		exit(0);
		break;

	}
	visualizacao();
	glutPostRedisplay();
}

void tamanhoJanela(int w, int h){
	if (h == 0){
		h = 1;
	}
	glViewport(0, 0, w, h);
	//aspecto = (float)w / (float)h;
	visualizacao();
}

void naven(){
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2i(-10, 0);
	glVertex2i(-10, 10);
	glVertex2i(10,10);
	glVertex2i(10, 0);
	glEnd();
}

void desenha(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	naven();
	glutSwapBuffers();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitWindowSize(largura_janela, altura_janela);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("CG - Navem Espacial");
	glutDisplayFunc(desenha);
	glutReshapeFunc(tamanhoJanela);
	glutKeyboardFunc(teclado);
	glutMainLoop();

}