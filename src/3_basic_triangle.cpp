#include <memory>
#include <cassert>

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
                                         "    gl_Position = attr_pos;"
                                         "}";
  const gl_string fragment_shader_source =
      "void main() {"
      "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
      "}";
  extension->shader_program =
      create_program_from_source(vertex_shader_source, fragment_shader_source);

  extension->attr_pos =
      glGetAttribLocation(extension->shader_program, "attr_pos");
  assert(extension->attr_pos >= 0);

  glUseProgram(extension->shader_program);
  assert(glGetError() == GL_NO_ERROR);
}

void render_func() {
  glClearColor(0.f, 1.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableVertexAttribArray(extension->attr_pos);

  const GLfloat position[] = {// v0 上
                              0.f,  1.f,
                              // v1 右
                              1.f,  -1.f,
                              // v2 左
                              -1.f, -1.f};

  glVertexAttribPointer(extension->attr_pos, 2, GL_FLOAT, GL_FALSE, 0,
                        (GLvoid *)position);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void destroy() {
  glUseProgram(0);
  assert(glGetError() == GL_NO_ERROR);

  glDeleteProgram(extension->shader_program);
  assert(glGetError() == GL_NO_ERROR);
  assert(glIsProgram(extension->shader_program) == GL_FALSE);
}
