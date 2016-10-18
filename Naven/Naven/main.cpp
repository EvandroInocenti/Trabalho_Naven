#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float angulo, aspecto;			 //gluPerspective
float zNear = 0.1, zFar = 500;   //gluPerspective
int posX = 0, posY = 0, posZ = 300; //Par�metros da gluLookAt
float transladaX = 0, transladaY = 0, transladaZ = 0;
float angRotacaoX;
GLboolean rotate = false;

void visualizacao() {
	glMatrixMode(GL_PROJECTION);	//Matriz de proje��o
	glLoadIdentity();				//Zera transforma��es
	//Configura perspectiva
	gluPerspective(angulo, aspecto, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);		//Muda p/matriz de visualiza��o
	glLoadIdentity();				//Zera transforma��es
	gluLookAt(posX, posY, posZ,		//Configura c�mera
		0, 0, 0,	//Para onde a c�mera aponta na cena
		0, 1, 0);	//Vetor 'up'
}
void teclado(unsigned char key, int x, int y) {

	switch (key) {
	case 27:	//Tecla ESC
		exit(0);
		break;
	case 32:	//espa�o
		if (transladaY < 160){
			transladaY = transladaY + 10;
			printf("\n o valor da translacao e %.2f\n", transladaY);
		}
		else{
			transladaY = 0;
			printf("\n o valor da translacao e %.2f\n", transladaY);
		}
		break;
	default:
		break;
	}
	visualizacao();			//M�todo que aplica os novos par�metros
	glutPostRedisplay();	//For�a redesenho
}

void teclasEspeciais(int tecla, int x, int y){
	switch (tecla){
	case GLUT_KEY_LEFT:
		angRotacaoX = angRotacaoX + 20.0;
		rotate = true;
		transladaY = 0;
		rotate = false;
		break;
	case GLUT_KEY_RIGHT:
		angRotacaoX = angRotacaoX - 20.0;
		rotate = true;
		transladaY = 0;
		rotate = false;
		break;
	default:
		break;
	}
	visualizacao();
	glutPostRedisplay();
}

void tamanhoJanela(int w, int h) { //w: width (comprimento)|h: height (altura)
	if (h == 0) { h = 1; }	//Evita divis�o por zero
	glViewport(0, 0, w, h);	//Redefine o viewport para o tamanho da janela
	aspecto = (float)w / (float)h;	//Calcula o 'aspect ratio'
	visualizacao();			//Aplica os novos par�metros de visualiza��o
}

void disparo(){
	glPushMatrix();
	glTranslatef(transladaX, transladaY - 10, transladaZ);
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2i(0, 0);
	glVertex2i(0, 5);
	glEnd();
	glPopMatrix();
}

void triangulo(){
	glPushMatrix();
	glTranslatef(0, -20, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f); //Vermelho
	glVertex2i(0, 20);
	glVertex2i(-20, 0);
	glVertex2i(20, 0);
	glEnd();
	glPopMatrix();
}

void desenha() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0);//Define cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);		//Limpa tela
	glRotatef(angRotacaoX, 0.0, 0.0, 1.0);
	disparo();
	triangulo();
	glutSwapBuffers();					//Renderiza
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);			//Inicializa biblioteca GLUT
	glutInitWindowSize(600, 600);	//Define tamanho da janela
	glutInitWindowPosition(50, 50);	//Define posi��o inicial da janela
	glutCreateWindow("CG - Nave Espacial");//Cria janela
	angulo = 45;	//Campo de vis�o (eixo y) inicial � de 45 graus
	glutDisplayFunc(desenha);		//Fun��o callback de redesenho
	glutReshapeFunc(tamanhoJanela);	//Callback quando tamanho janela alterado
	glutKeyboardFunc(teclado);		//Callback para tratamento de teclado
	glutSpecialFunc(&teclasEspeciais);
	glutMainLoop();					//Loop do GLUT
}