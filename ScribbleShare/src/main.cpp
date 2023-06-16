#include "Application.h"

const char* title = "ScribbleShare";
int width = 320;
int height = 180;

int main(int argc, char* argv[]) {
	Application* app = Application::GetInstance();
	app->Run(title, width, height);
	return 0;
}