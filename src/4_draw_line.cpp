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

void draw_line(GLenum mode, float line_width,
               const std::vector<std::pair<GLfloat, GLfloat>> &position) {
  const auto count = position.size();
  GLfloat *pos = new GLfloat[count * 2];
  for (int i = 0; i < count; i++) {
    const auto &p = position[i];
    pos[2 * i + 0] = p.first;
    pos[2 * i + 1] = p.second;
  }

  glLineWidth(line_width);
  glVertexAttribPointer(extension->attr_pos, 2, GL_FLOAT, GL_FALSE, 0,
                        (GLvoid *)pos);
  glDrawArrays(mode, 0, count);

  delete[] pos;
}

void initialize() {
  const gl_string vertex_shader_source = "attribute vec4 attr_pos;"
                                         "void main() {"
                                         "   gl_Position = attr_pos;"
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

  {
    std::vector<std::pair<GLfloat, GLfloat>> position{
        {-1.f, 0.f}, // v0
        {1.f, 0.f},  // v1
        {0.f, 1.f},  // v2
        {0.f, -1.f}  // v3
    };

    draw_line(GL_LINES, 1.f, position);
  }

  {
    std::vector<std::pair<GLfloat, GLfloat>> position{
        {-0.2f, 0.2f}, // v0
        {0.2f, 0.2f},  // v1
        {0.2f, -0.2f}, // v2
        {-0.2f, -0.2f} // v3
    };

    draw_line(GL_LINE_STRIP, 5.f, position);
  }

  {
    std::vector<std::pair<GLfloat, GLfloat>> position{
        {-0.75f, 0.75f}, // v0
        {0.75f, 0.75f},  // v1
        {0.75f, -0.75f}, // v2
        {-0.75f, -0.75f} // v3
    };

    draw_line(GL_LINE_LOOP, 5.f, position);
  }
}

void destroy() {
  glUseProgram(0);
  glDeleteProgram(extension->shader_program);
}
