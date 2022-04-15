#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <cmath>

GLuint VBO;
float Scale = 0.0f;

/*	Объявление функций	*/
static void CreateVertexBuffer(glm::mat4& m);
glm::mat4 moving(glm::mat4& m);

/*	Функция рендера сцены	*/
static void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	Scale += 0.001f;

	glm::mat4 mov_mtrx = moving(mov_mtrx);

	CreateVertexBuffer(mov_mtrx);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

/*	Функция создания буфера вершин	*/
static void CreateVertexBuffer(glm::mat4& m)
{
	glm::vec3 Vertices[3];
	Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
	Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

	Vertices[0] = glm::vec4(Vertices[0], 1.0f) * m;
	Vertices[1] = glm::vec4(Vertices[1], 1.0f) * m;
	Vertices[2] = glm::vec4(Vertices[2], 1.0f) * m;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

/*	Функция передвижения	*/
glm::mat4 moving(glm::mat4& m)
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = sinf(Scale);
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

	return m;
}

/*	Главная функция	*/
int main(int argc, char** argv)
{
	/*	Инициализация первоначального состояния GLUT	*/
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInit(&argc, argv);

	/*	Создаём окно	*/
	glutCreateWindow("Lab work №1");

	/*	Регистрация вызываемой функции	*/
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);

	/*	Инициализация GLEW	*/
	GLenum res = glewInit();

	/*	Проверка GLEW на ошибки	*/
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/*	Запуск механизма обработки событий	*/
	glutMainLoop();

	return 0;
}