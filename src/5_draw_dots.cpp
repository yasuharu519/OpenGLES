#include <memory>
#include <cassert>
#include <vector>
#include <utility>

#include <GLFW/glfw3.h>

#include "shader_helper.hpp"

struct Extension {
  GLuint shader_program;
  GLint attr_pos;
};

static std::shared_ptr<Extension> extension = std::make_shared<Extension>();

void initialize() {
  const gl_string vertex_shader_source = "attribute vec4 attr_pos;"
                                       "void main() {"
                                       "   gl_Position = attr_pos;"
                                       "   gl_PointSize = 10.0;"
                                       "}";
  const gl_string fragment_shader_source =
      "void main() {"
      "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
      "}";
  extension->shader_program = create_program_from_source(vertex_shader_source, fragment_shader_source);

  extension->attr_pos =
      glGetAttribLocation(extension->shader_program, "attr_pos");
  assert(extension->attr_pos >= 0);

  glUseProgram(extension->shader_program);
  assert(glGetError() == GL_NO_ERROR);
}

void render_func()
{
  glClearColor(1.f, 1.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableVertexAttribArray(extension->attr_pos);

  {
    const GLfloat positions[] = {
      0.f, 0.f,
      0.75f, -0.75f,
    };

    glPointSize(10.f);
    glVertexAttribPointer(extension->attr_pos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)positions);
    glDrawArrays(GL_POINTS, 0, 2);
  }
}

void destroy()
{
  glUseProgram(0);
  glDeleteProgram(extension->shader_program);
}
