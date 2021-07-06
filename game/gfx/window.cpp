#include "window.h"

/*
void gfx::glDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer

	display_players_sticks(game->player1, 1);
	display_players_sticks(game->player2, 2);

	display_board();

	glutSwapBuffers();   // Double buffered - swap the front and back buffers


}


void gfx::display_players_sticks(std::list<engine::domino*> sticks, int player_id)
{
	float padding = orthoX * 0.01f;
	//float width = 2 * orthoX / sticks.size() - padding;
	//if (width > orthoX * 0.25f)
	float width = orthoX * 0.15f;
	float height = 2 * width;

	if (orthoX / orthoY > 1.0)
	{
		height = 0.3f;
		width = 0.15f;
	}

	float x0 = -((sticks.size() - 1) * (width + padding) + width) / 2;
	float y0 = orthoY - padding;

	if (player_id == 2)
	{
		y0 = -orthoY + height + padding;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x0, y0, 0.0f);

	for (auto it = sticks.begin(); it != sticks.end(); it++)
	{
		engine::domino* stick = *it;
		int top = stick->top;
		int bottom = stick->bottom;


		float red = 0;
		float green = 0;
		float blue = 0;
		//if (stick->isPlayable == engine::STICK_TURN::left)
		//	red = 1;
		//else if (stick->isPlayable == engine::STICK_TURN::right)
		//	green = 1;
		//else if (stick->isPlayable == engine::STICK_TURN::both)
		//	blue = 1;

		if (player_id == 1)
			red = 1;

		glBegin(GL_LINE_LOOP);
		glColor3f(red, green, blue);

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, -height);
		glVertex2f(width, -height);
		glVertex2f(width, 0.0f);

		glEnd();

		glBegin(GL_LINES);
		glColor3f(red, green, blue);

		glVertex2f(0.0f, -height / 2);
		glVertex2f(width, -height / 2);

		glEnd();

		glEnable(GL_POINT_SMOOTH);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 0.0f);
		display_dotes(0, 0, width, height, top);
		display_dotes(0, -height / 2, width, height, bottom);
		glEnd();
		glTranslatef(width + padding, 0, 0.0f);
	}
	glPopMatrix();
}

void gfx::display_board()
{
	//float padding = 0.002f;
	float padding = 0;
	float width = orthoX * 0.15f;
	float height = 2 * width;

	if (orthoX / orthoY > 1.0)
	{
		height = 0.3f;
		width = 0.15f;
	}

	float x0 = -height / 2;
	float y0 = -width / 2;

	int rowLen = (int)((orthoX - height) / (height + padding)) - 1;

	//printf("%d\n", rowLen);


	// render right side sticks

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x0, y0, 0.0f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);

	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, -height);
	glVertex2f(width, -height);
	glVertex2f(width, 0.0f);

	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);

	glVertex2f(0.0f, -height / 2);
	glVertex2f(width, -height / 2);

	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	display_dotes(0, 0, width, height, game->board_start->top);
	display_dotes(0, -height / 2, width, height, game->board_start->bottom);
	glEnd();
	glPopMatrix();

	// render root stick

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x0 + height, y0, 0.0f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	auto it = game->board_right.begin();
	for (int i = 0, col = 0;
		it != game->board_right.end();
		++it, ++i)
	{
		engine::domino* stick = *it;
		int top = stick->top;
		int bottom = stick->bottom;

		float red = 0;
		float green = 0;
		float blue = 0;
		if ((i + 1) % 2)
			red = 1;

		glBegin(GL_LINE_LOOP);
		glColor3f(red, green, blue);

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, -height);
		glVertex2f(width, -height);
		glVertex2f(width, 0.0f);

		glEnd();

		glBegin(GL_LINES);
		glColor3f(red, green, blue);

		glVertex2f(0.0f, -height / 2);
		glVertex2f(width, -height / 2);

		glEnd();

		glEnable(GL_POINT_SMOOTH);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 0.0f);
		display_dotes(0, 0, width, height, top);
		display_dotes(0, -height / 2, width, height, bottom);
		glEnd();
		glTranslatef(0, -padding - height, 0.0f);
		if (i - rowLen == 2)
		{
			glTranslatef(-padding, padding + width, 0.0f);
			glRotatef(-90, 0.0f, 0.0f, 1.0f);
		}
		else if (i == rowLen)
		{
			glTranslatef(width, 0, 0.0f);
			glRotatef(-90, 0.0f, 0.0f, 1.0f);
		}
		//else if(i > rowLen)

	}
	glPopMatrix();

	// render left side sticks

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x0 - height, y0, 0.0f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	it = game->board_left.begin();
	for (int i = 0, col = 0;
		it != game->board_left.end();
		++it, ++i)
	{
		engine::domino* stick = *it;
		int top = stick->top;
		int bottom = stick->bottom;

		float red = 0;
		float green = 0;
		float blue = 0;
		if ((i + 1) % 2)
			red = 1;

		glBegin(GL_LINE_LOOP);
		glColor3f(red, green, blue);

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, -height);
		glVertex2f(width, -height);
		glVertex2f(width, 0.0f);

		glEnd();

		glBegin(GL_LINES);
		glColor3f(red, green, blue);

		glVertex2f(0.0f, -height / 2);
		glVertex2f(width, -height / 2);

		glEnd();

		glEnable(GL_POINT_SMOOTH);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 0.0f);
		display_dotes(0, 0, width, height, top);
		display_dotes(0, -height / 2, width, height, bottom);
		glEnd();
		glTranslatef(0, padding + height, 0.0f);
		if (i - rowLen == 2)
		{
			glTranslatef(width + height + padding, -padding - height, 0.0f);
			glRotatef(-90, 0.0f, 0.0f, 1.0f);
		}
		else if (i == rowLen)
		{
			glTranslatef(height, -width, 0.0f);
			glRotatef(-90, 0.0f, 0.0f, 1.0f);
		}
		//else if(i > rowLen)

	}
	glPopMatrix();
}

void gfx::display_stick(int row, int col, engine::domino* stick)
{
	int top = stick->top;
	int bottom = stick->bottom;
	const float padding = orthoX * 0.01f;
	float width = 2 * orthoX / MAX_PLAYER_STICKS_COUNT - padding;
	if (width > orthoX * 0.25f) width = orthoX * 0.25f;

	float height = 2 * width;

	//const float x0 = padding + (width + padding) * col - orthoX;
	float x0 = -((MAX_PLAYER_STICKS_COUNT - 1) * (width + padding) + width) / 2 + (width + padding) * col;

	float y0 = orthoY - padding;
	float angle = 0;

	if (row == 2)
	{
		y0 = -orthoY + height + padding;
	}
	else if (row == 0)
	{
		x0 = -height / 2;
		y0 = -width / 2;
		angle = 90;
	}

	float red = 0;
	if (stick->isPlayable)
		red = 1;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(x0, y0, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_LINE_LOOP);
	glColor3f(red, 0.0f, 0.0f);

	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, -height);
	glVertex2f(width, -height);
	glVertex2f(width, 0.0f);

	glEnd();

	glBegin(GL_LINES);
	glColor3f(red, 0.0f, 0.0f);

	glVertex2f(0.0f, -height / 2);
	glVertex2f(width, -height / 2);

	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(5.0f);
	display_dotes(0, 0, width, height, top);
	display_dotes(0, -height / 2, width, height, bottom);

	glPopMatrix();
}

void gfx::display_dotes(float x, float y, float width, float height, int n)
{
	//glBegin(GL_POINTS);
	//glColor3f(0.0f, 0.0f, 0.0f);

	switch (n)
	{
	case 1:
		glVertex2f(x + width / 2, y - height / 4);
		break;
	case 2:
		glVertex2f(x + width / 3, y - height / 4);
		glVertex2f(x + 2 * width / 3, y - height / 4);
		break;
	case 3:
		glVertex2f(x + width / 4, y - height / 8);
		glVertex2f(x + width / 2, y - height / 4);
		glVertex2f(x + 3 * width / 4, y - 3 * height / 8);
		break;
	case 4:
		glVertex2f(x + width / 3, y - height / 6);
		glVertex2f(x + 2 * width / 3, y - height / 6);
		glVertex2f(x + width / 3, y - height / 3);
		glVertex2f(x + 2 * width / 3, y - height / 3);
		break;
	case 5:
		glVertex2f(x + width / 3, y - height / 6);
		glVertex2f(x + 2 * width / 3, y - height / 6);
		glVertex2f(x + width / 2, y - height / 4);
		glVertex2f(x + width / 3, y - height / 3);
		glVertex2f(x + 2 * width / 3, y - height / 3);
		break;
	case 6:
		glVertex2f(x + width / 4, y - height / 6);
		glVertex2f(x + 2 * width / 4, y - height / 6);
		glVertex2f(x + 3 * width / 4, y - height / 6);
		glVertex2f(x + width / 4, y - height / 3);
		glVertex2f(x + 2 * width / 4, y - height / 3);
		glVertex2f(x + 3 * width / 4, y - height / 3);
		break;
	default:
		break;
	}

	//glEnd();
}

void gfx::idle()
{
	glutPostRedisplay();
}

void gfx::onReshapeWindow(int width, int height)
{
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (width >= height) {
		// aspect >= 1, set the height from -1 to 1, with larger width
		orthoX = 1.0 * aspect;
		orthoY = 1.0;
		gluOrtho2D(-orthoX, orthoX, -orthoY, orthoY);
	}
	else {
		// aspect < 1, set the width to -1 to 1, with larger height
		orthoX = 1.0;
		orthoY = 1.0 / aspect;
		gluOrtho2D(-orthoX, orthoX, -orthoY, orthoY);
	}
	printf("New size: (%d, %d)\n", width, height);
}
*/
namespace core
{
	Window::Window()
	{
	}

	Window::Window(int width, int height)
	{
		window_create(width, height);
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	int Window::window_create(int width, int height)
	{
		this->width = width;
		this->height = height;
		this->isWindowShuldClose = true;

		glfwInit();
		glfwWindowHint(GLFW_SAMPLES, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, "OpenGL Dominoes", NULL, NULL);
		if (!window)
		{
			fprintf(stderr, "Creating window failed\n");
			glfwTerminate();
			return 1;
		}
		
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			fprintf(stderr, "Glad load failed\n");
			glfwTerminate();
			return 2;
		}

		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowCloseCallback(window, close_callback);

		this->isWindowShuldClose = false;

		if (height == 0) height = 1;                // To prevent divide by 0
		GLfloat aspect = (GLfloat)width / (GLfloat)height;

		if (width >= height) {
			// aspect >= 1, set the height from -1 to 1, with larger width
			orthoX = 1.0 * aspect;
			orthoY = 1.0;
		}
		else {
			// aspect < 1, set the width to -1 to 1, with larger height
			orthoX = 1.0;
			orthoY = 1.0 / aspect;
		}

		return 0;
	}

	void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		w->width = width;
		w->height = height;


		if (height == 0) height = 1;                // To prevent divide by 0
		GLfloat aspect = (GLfloat)width / (GLfloat)height;

		if (width >= height) {
			// aspect >= 1, set the height from -1 to 1, with larger width
			w->orthoX = 1.0 * aspect;
			w->orthoY = 1.0;
		}
		else {
			// aspect < 1, set the width to -1 to 1, with larger height
			w->orthoX = 1.0;
			w->orthoY = 1.0 / aspect;
		}

		glViewport(0, 0, width, height);
		printf("New window size: %dx%d\n", width, height);
	}

	void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//printf("%d %c %s\n", key, key, (action == GLFW_PRESS) ? "pressed" : "released");
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		if (key == GLFW_KEY_ESCAPE)
		{
			w->isWindowShuldClose = true;
			glfwSetWindowShouldClose(window, true);
		}
	}

	void Window::close_callback(GLFWwindow* window)
	{
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		w->isWindowShuldClose = true;
	}

	void Window::end_scene()
	{
		// TODO: for multiplayer use glfwWaitEvents() with glfwPostEmptyEvent()
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}