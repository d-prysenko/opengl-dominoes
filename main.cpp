#if 0
#include <iostream>
#include <ctime>
#include <chrono>

#include "Packet.h"
#include "PDAPPacket.h"

#pragma warning(disable:4996)

int main()
{
	setlocale(LC_ALL, "ru");

	//const char buf[] = "   "; int size = sizeof(buf);

	const char buf[] = "GET /ru/post/228181/ HTTP/1.1\r\n"
		"Host: habr.com\r\n"
		"Connection: keep-alive\r\n"
		"Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
		"Cache-Control: max-age=0\r\n"
		"DNT: 1\r\n"
		"Upgrade-Insecure-Requests: 1\r\n"
		"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.141 Safari/537.36\r\n"
		"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n\r\n";

	/*const char buf[] = "GET /ru/post/228181/ HTTP/1.1\r\n"
		"Host:\r\n"
		"Accept: text/html\r\n\r\n";*/
	int size = sizeof(buf);

	//const char kekw[] = { static_cast<char>(PDAPPacket::Type::Disconnection), 14, static_cast<char>(PDAPPacket::Type::Disconnection) };


	//std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	//std::cout << (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - ms).count() << std::endl;




	PacketType type = Packet::GetType(buf, sizeof(buf));

	if (type == PacketType::HTTP)
	{
		HTTPtoWSPacket* p = new HTTPtoWSPacket(buf);

		if (!p->isKeySet)
		{
			std::cout << "It is not HTTPtoWSPacket :D\n";
		}
		else
		{
			char response[256] =
				"HTTP/1.1 101 Switching Protocols\r\n"
				"Upgrade: websocket\r\n"
				"Connection: Upgrade\r\n"
				"Sec-WebSocket-Accept: ";
			strcat(response, p->getWebSocketAccept().c_str());
			strcat(response, "\r\n\r\n");
			std::cout << response << std::endl;
		}

		delete p;
	}
	else if (type == PacketType::PDAP)
	{
		//PDAPPacket* p = new PDAPPacket(kekw, sizeof(kekw));
		std::cout << "123123" << std::endl;
	}


	system("pause");
	return 0;
}
#endif

//#define OPENGL

#ifdef OPENGL

#pragma warning(disable:26451)

#include <Windows.h>
#include <stdio.h>
#include <psapi.h>
#include <wchar.h>
#include <tlhelp32.h>
#include <fstream>
#include <iostream>
#include <GL/glut.h>

typedef unsigned long long LDWORD;
#define SERVERDLL L"server.dll"
#define ENGINEDLL L"engine.dll"

LDWORD server_dll_base = 0;
LDWORD engine_dll_base = 0;
HANDLE hProcess;
HWND hWnd;
DWORD err;

DWORD PlrSz = 0x10;
DWORD oPlrCount = 0xB259E0;
DWORD oPlrList = 0x596780;

DWORD oHealth = 0x230;
DWORD oTeam = 0x314;
DWORD oCoords = 0x1DC;
DWORD oPosName = 0x11F0;
DWORD oPlayerName = 0x1121;

DWORD oMatrix = 0x599868;
// 2E182654

const size_t width = 1024;
const size_t height = 768;

int read_bytes(LPCVOID addr, int num, void* buf);
HANDLE GetProcessHandle();
#pragma warning(disable:4996)




bool WorldToScreen(float* from, float* to, float* view_matrix)
{
	float w = 0.0f;
	//to[0] = view_matrix[0][0] * from[0] + view_matrix[0][1] * from[1] + view_matrix[0][2] * from[2] + view_matrix[0][3];
	//to[1] = view_matrix[1][0] * from[0] + view_matrix[1][1] * from[1] + view_matrix[1][2] * from[2] + view_matrix[1][3];
	//w = view_matrix[3][0] * from[0] + view_matrix[3][1] * from[1] + view_matrix[3][2] * from[2] + view_matrix[3][3];
	to[0] = view_matrix[0] * from[0] + view_matrix[1] * from[1] + view_matrix[2] * from[2] + view_matrix[3];
	to[1] = view_matrix[4] * from[0] + view_matrix[5] * from[1] + view_matrix[6] * from[2] + view_matrix[7];
	w = view_matrix[12] * from[0] + view_matrix[13] * from[1] + view_matrix[14] * from[2] + view_matrix[15];
	if (w < 0.01f)
		return 0;
	float invw = 1.0f / w;
	to[0] *= invw;
	to[1] *= invw;

	float x = width / 2;
	float y = height / 2;
	x += 0.5 * to[0] * width + 0.5;
	y -= 0.5 * to[1] * height + 0.5;
	//to[0] = x + rect.left;
	//to[1] = y + rect.top;
	to[0] = x;
	to[1] = y;
	return 1;
}


void ESP()
{

	int plrCount, hp, team;
	float coords[3];
	DWORD PlrList = 0;
	const DWORD addr = engine_dll_base + oPlrList;

	read_bytes((LPCVOID)(server_dll_base + oPlrCount), 4, &plrCount);

	printf("Players on map: %d\n", plrCount);

	float my_coords[3];

	//read_bytes((LPCVOID)(addr), 4, &PlrList);
	read_bytes((LPCVOID)(addr), 4, &PlrList);
	//read_bytes((LPCVOID)(PlrList + oCoords), 12, &my_coords);


	//float view_matrix[4][4];
	//ReadProcessMemory(hProcess, (LPCVOID)(engine_dll_base + oMatrix), &view_matrix, 64, NULL);


	float matrix[4][4];
	DWORD p1, p2;
	read_bytes((LPCVOID)(engine_dll_base + oMatrix), 4, &p1);
	read_bytes((LPCVOID)(p1 + 0x58), 4, &p2);
	read_bytes((LPCVOID)(p2 + 0xA58), 16 * sizeof(float), matrix);
	for (int i = 0; i < plrCount; i++)
	{
		DWORD PlayerStruct;
		char posName[64];
		char name[64];
		read_bytes((LPCVOID)(PlrList + 0x1C + i * PlrSz), 4, &PlayerStruct);
		read_bytes((LPCVOID)(PlayerStruct + oHealth), 4, &hp);
		if (hp == 0) continue;
		read_bytes((LPCVOID)(PlayerStruct + oCoords), 12, &coords);
		read_bytes((LPCVOID)(PlayerStruct + oTeam), 4, &team);
		read_bytes((LPCVOID)(PlayerStruct + oPosName), 64, posName);
		read_bytes((LPCVOID)(PlayerStruct + oPlayerName), 64, name);

		float ScreenPos[2];

		coords[2] += 45.0f;

		if (i != 0 && WorldToScreen(coords, ScreenPos, (float*)(&matrix)) == 1)
			printf("%.2f%%, %.2f%%\n", ScreenPos[0] * 100 / width, ScreenPos[1] * 100 / height);

		printf("%dHP\t", hp);
		fputs(name, stdout);
		//std::cout << name << '\t';
		printf("\t (%.1f, %.1f, %.1f) ", coords[0], coords[1], coords[2]);
		printf("Team: %s\t %s\n", ((team == 2) ? "T" : "CT"), posName);
	}
	system("cls");
}

HANDLE GetProcessHandle()
{
	HANDLE h = 0;
	DWORD pid = 0;

	hWnd = FindWindow(0, L"Counter-Strike: Global Offensive");

	if (hWnd == 0) {
		//Beep(1000, 2000);
		err = GetLastError();
		return 0;
	}

	GetWindowThreadProcessId(hWnd, &pid);

	h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, pid);

	if (h == 0) {
		//Beep(1000, 2000);
		err = GetLastError();
		return 0;
	}

	HMODULE hMods[1024];

	if (EnumProcessModules(h, hMods, sizeof(hMods), &pid))
	{
		for (int i = 0; i < (pid / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(h, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				if (wcsstr(szModName, SERVERDLL) != NULL)
				{
					server_dll_base = (LDWORD)hMods[i];
				}
				else if (wcsstr(szModName, ENGINEDLL) != NULL)
				{
					engine_dll_base = (LDWORD)hMods[i];
				}
				if (server_dll_base != 0 && engine_dll_base != 0) return h;
			}
		}
	}
	else
	{
		Beep(200, 2000);
		err = GetLastError();
	}

	return h;
}

int read_bytes(LPCVOID addr, int num, void* buf)
{
	DWORD err = GetLastError();
	SIZE_T sz = 0;
	int r = ReadProcessMemory(hProcess, addr, (LPVOID)buf, num, &sz);
	err = GetLastError();
	if (r == 0 || sz == 0)
	{
		//Beep(1000, 2000);
		err = GetLastError();
		return 0;
	}
	return 1;
}

using namespace std;

int main()
{

	SetConsoleOutputCP(CP_UTF8);
	hProcess = GetProcessHandle();
	while (1)
		ESP();


	return 0;
}

#endif

#ifdef OPENGL

#include <GL/glut.h>
#include <stdio.h>

using namespace std;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.4, 0.4);
	glVertex2f(0.4, 0.8);
	//
	glVertex2f(0.4, 0.8);
	glVertex2f(0.8, 0.8);
	//
	glVertex2f(0.8, 0.8);
	glVertex2f(0.8, 0.4);
	//
	glVertex2f(0.4, 0.4);
	glVertex2f(0.8, 0.4);
	glEnd();
	glFlush();


}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(240, 240);
	glutInitWindowPosition(100, 740);
	glutCreateWindow("First window!");
	//glutEstablishOverlay();
	//glutOverlayDisplayFunc(display2);
	//glutShowOverlay();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);


	glutDisplayFunc(display);
	glutMainLoop();


}

#endif


/*
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	size_t N;
	cout << "Введите кол-во строк: ";
	cin >> N;

	size_t min = UINT_MAX, max = 0;
	size_t count_min = 0, count_max = 0;

	for (size_t i = 0; i < N; i++)
	{
		string temp;
		cout << ">> ";

		cin.ignore();
		getline(cin, temp);

		size_t weight_s = 0;
		while (temp[weight_s] < '0' || temp[weight_s] > '9') weight_s++;

		size_t weight_len = 0;
		while (temp[weight_s + weight_len] != ' ') weight_len++;

		size_t weight = stoul(temp.substr(weight_s, weight_len));

		//cout << "Вес одного чемодана: " << weight;

		size_t suitcases_s = temp.length() - 1;
		while (temp[suitcases_s] != ' ') suitcases_s--;
		suitcases_s++;

		size_t suitcases_count = stoul(temp.substr(suitcases_s, suitcases_s - temp.length() - 1));

		//cout << "Всего чемоданов: " << suitcases_count;

		if (suitcases_count * weight > max)
		{
			if (min == UINT_MAX && max != 0)
			{
				min = max;
				count_min = count_max;
			}
			max = suitcases_count * weight;
			count_max = 1;

		}
		else if (suitcases_count * weight == max)
		{
			count_max++;
		}
		else if (suitcases_count * weight < min)
		{
			min = suitcases_count * weight;
			count_min = 1;
		}
		else if (suitcases_count * weight == min)
		{
			count_min++;
		}

	}

	cout << "Пассажиров с минимальным весом: " << count_min << endl;
	cout << "Пассажиров с максимальным весом: " << count_max << endl;

	return 0;
}
*/



// Есть набор костей домино, часть из которых выложена на столе, а остальные находятся у двух игроков.
// Необходимо определить, существует ли последовательность ходов, при которой второй игрок вынужден пропустить ход
// из-за отсутствия необходимых костей.
// игру начинает первый игрок
// игроки ходят по очереди.



#include <stdio.h>
#include "game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


int main(int argc, char** argv)
{
	Game game(Game::Mode::OFFLINE);
	game.window_create(WINDOW_WIDTH, WINDOW_HEIGHT);
	game.loop();

	return 0;
}


/*

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: инициализация и конфигурирование
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // раскомментируйте эту строку, если используете macOS
#endif

	// glfw: создание окна
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL for Ravesli.com", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: загрузка всех указателей на OpenGL-функции
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Цикл рендеринга
	while (!glfwWindowShouldClose(window))
	{
		// Обработка ввода
		processInput(window);

		// Выполнение рендеринга
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: обмен содержимым front- и back- буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
	glfwTerminate();
	return 0;
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Убеждаемся, что окно просмотра соответствует новым размерам окна. 
	// Обратите внимание, что ширина и высота будут значительно больше, чем указано, на Retina-дисплеях
	glViewport(0, 0, width, height);
}

*/