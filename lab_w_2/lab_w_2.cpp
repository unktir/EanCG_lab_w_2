#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <cmath>

GLuint VBO;
float Scale = 0.0f;

/*	Объявление функций	*/
static void CreateVertexBuffer(glm::mat4& m, glm::mat4& r, glm::mat4& c);
glm::mat4 moving(glm::mat4& m);
glm::mat4 rotation(glm::mat4& m);
glm::mat4 conversion(glm::mat4& mtrx);

/*	Функция рендера сцены	*/
static void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	Scale += 0.001f;

	glm::mat4 mov_mtrx = moving(mov_mtrx);
	glm::mat4 rot_mtrx = rotation(rot_mtrx);
	glm::mat4 con_mtrx = conversion(con_mtrx);

	CreateVertexBuffer(mov_mtrx, rot_mtrx, con_mtrx);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

/*	Функция создания буфера вершин	*/
static void CreateVertexBuffer(glm::mat4& m, glm::mat4& r, glm::mat4& c)
{
	/*	Задаём начальные координаты	*/
	glm::vec3 Vertices[3];
	Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
	Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

	/*	Задаёт координаты перемещения	*/
	Vertices[0] = glm::vec4(Vertices[0], 1.0f) * m * r * c;
	Vertices[1] = glm::vec4(Vertices[1], 1.0f) * m * r * c;
	Vertices[2] = glm::vec4(Vertices[2], 1.0f) * m * r * c;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

/*	Функция передвижения	*/
glm::mat4 moving(glm::mat4& mtrx)
{
	mtrx[0][0] = 1.0f; mtrx[0][1] = 0.0f; mtrx[0][2] = 0.0f; mtrx[0][3] = sinf(Scale);
	mtrx[1][0] = 0.0f; mtrx[1][1] = 1.0f; mtrx[1][2] = 0.0f; mtrx[1][3] = 0.0f;
	mtrx[2][0] = 0.0f; mtrx[2][1] = 0.0f; mtrx[2][2] = 1.0f; mtrx[2][3] = 0.0f;
	mtrx[3][0] = 0.0f; mtrx[3][1] = 0.0f; mtrx[3][2] = 0.0f; mtrx[3][3] = 1.0f;

	return mtrx;
}

/*	Функция вращения	*/
glm::mat4 rotation(glm::mat4& mtrx)
{
	mtrx[0][0] = cosf(Scale); mtrx[0][1] = -sinf(Scale); mtrx[0][2] = 0.0f; mtrx[0][3] = 0.0f;
	mtrx[1][0] = sinf(Scale); mtrx[1][1] = cosf(Scale);  mtrx[1][2] = 0.0f; mtrx[1][3] = 0.0f;
	mtrx[2][0] = 0.0f;        mtrx[2][1] = 0.0f;         mtrx[2][2] = 1.0f; mtrx[2][3] = 0.0f;
	mtrx[3][0] = 0.0f;        mtrx[3][1] = 0.0f;         mtrx[3][2] = 0.0f; mtrx[3][3] = 1.0f;

	return mtrx;
}

/*	Функция маштабирования	*/
glm::mat4 conversion(glm::mat4& mtrx)
{
	mtrx[0][0] = sinf(Scale); mtrx[0][1] = 0.0f;        mtrx[0][2] = 0.0f;        mtrx[0][3] = 0.0f;
	mtrx[1][0] = 0.0f;        mtrx[1][1] = cosf(Scale); mtrx[1][2] = 0.0f;        mtrx[1][3] = 0.0f;
	mtrx[2][0] = 0.0f;        mtrx[2][1] = 0.0f;        mtrx[2][2] = sinf(Scale); mtrx[2][3] = 0.0f;
	mtrx[3][0] = 0.0f;        mtrx[3][1] = 0.0f;        mtrx[3][2] = 0.0f;        mtrx[3][3] = 1.0f;

	return mtrx;
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