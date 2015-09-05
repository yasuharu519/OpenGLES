#include <cstdlib>

#include <GLFW/glfw3.h>

void render_func()
{
  glClearColor((GLfloat)(rand() % 256) / 255.f,
	       (GLfloat)(rand() % 256) / 255.f,
	       (GLfloat)(rand() % 256) / 255.f,
	       1.f);
  glClear(GL_COLOR_BUFFER_BIT);
}
