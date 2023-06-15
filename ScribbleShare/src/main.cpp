#include "Application.h"

const char* title = "ScribbleShare";
int width = 1280;
int height = 720;

int main(int argc, char* argv[]) {
	Application app(title, width, height);
	app.Run();
	return 0;
}