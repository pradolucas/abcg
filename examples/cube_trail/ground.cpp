#include "ground.hpp"

void Ground::create(GLuint program, GLint modelMatrixLoc, GLint colorLoc,
                    glm::mat4 viewMatrix, float scale,
                    int N) {
  // Unit quad on the xz plane
  m_vertices = {{
    {.position = {+0.5f, 0.0f, -0.5f}}, // V1
    {.position = {-0.5f, 0.0f, -0.5f}}, // V2
    {.position = {+0.5f, 0.0f, +0.5f}}, // V3
    {.position = {-0.5f, 0.0f, +0.5f}}  // V4
  }};

  // VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER,
                     sizeof(m_vertices.at(0)) * m_vertices.size(),
                     m_vertices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Create VAO and bind vertex attributes
  abcg::glGenVertexArrays(1, &m_VAO);
  abcg::glBindVertexArray(m_VAO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  // Bind vertex attributes
  auto const positionAttribute{
      abcg::glGetAttribLocation(program, "inPosition")};
  if (positionAttribute >= 0) {
    abcg::glEnableVertexAttribArray(positionAttribute);
    abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                                sizeof(Vertex), nullptr);
  }

  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);

  // Load location of uniform variables of shader
  m_modelMatrixLoc = modelMatrixLoc;
  m_viewMatrix = viewMatrix;
  m_colorLoc = colorLoc;
  m_scale = scale;
  m_N = N;
}

void Ground::drawTile(float angle, glm::vec3 axis, float xOffset, float yOffset,
                      float zOffset, float factorX, float factorY,
                      float factorZ) {

  for (auto const z : iter::range(-m_N, m_N + 1)) {
    for (auto const x : iter::range(-m_N, m_N + 1)) {
      glm::mat4 model{1.0f};

      model = glm::rotate(model, glm::radians(angle), axis);
      model =
          glm::translate(model, glm::vec3(factorX * (x + xOffset) * m_scale,
                                          factorY * yOffset * m_scale,
                                          factorZ * (z + zOffset) * m_scale));
      model = glm::scale(model, glm::vec3(m_scale, m_scale, m_scale));

      abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

      // Set color (checkerboard pattern)
      auto const gray{(z + x) % 2 == 0 ? 0.5f : 1.0f};
      abcg::glUniform4f(m_colorLoc, gray, gray, gray, 1.0f);
      // abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);
      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }
}

void Ground::paint() {
  abcg::glBindVertexArray(m_VAO);

  // Building a cubic surface
  drawTile(0.0f,   glm::vec3(1, 0, 0), 0.0f, 0.5f, 0.0f, 1.0f, -1.0f, 1.0f);   // x,z, 0
  drawTile(180.0f, glm::vec3(1, 0, 0), 0.0f, 3.5f, 0.0f, 1.0f, 1.0f, 1.0f);  // x,z, +
  drawTile(90.0f,  glm::vec3(0, 0, 1), 1.0f+ m_N, 1.5f, 0.0f, -1.0f, 1.0f, 1.0f);  //  y,z, 0
  drawTile(270.0f, glm::vec3(0, 0, 1), 1.0f+ m_N, 1.5f, 0.0f, 1.0f, 1.0f, 1.0f);  // y,z, +
  drawTile(-90.0f, glm::vec3(1, 0, 0), 0.0f, 1.5f, 1.0f + m_N, 1.0f, 1.0f, -1.0f); // x,y, 0
  drawTile(90.0f,  glm::vec3(1, 0, 0), 0.0f, 1.5f, 1.0f + m_N, 1.0f, 1.0f, 1.0f);   // x,y, +

  abcg::glBindVertexArray(0);
}

void Ground::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}