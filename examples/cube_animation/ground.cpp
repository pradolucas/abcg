#include "ground.hpp"

void Ground::create(GLuint program, GLint modelMatrixLoc, GLint colorLoc,
                    GLint normalMatrixLoc, glm::mat4 viewMatrix, float scale,
                    int N) {
  // Unit quad on the xz plane
  m_vertices = {
      {{.position = {+0.5f, 0.0f, -0.5f}, .normal{0.0f, 1.0f, 0.0f}}, // V1
       {.position = {-0.5f, 0.0f, -0.5f}, .normal{0.0f, 1.0f, 0.0f}}, // V2
       {.position = {+0.5f, 0.0f, +0.5f}, .normal{0.0f, 1.0f, 0.0f}}, // V3
       {.position = {-0.5f, 0.0f, +0.5f}, .normal{0.0f, 1.0f, 0.0f}}}}; // V4

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

  auto const normalAttribute{abcg::glGetAttribLocation(program, "inNormal")};
  if (normalAttribute >= 0) {
    abcg::glEnableVertexAttribArray(normalAttribute);
    auto const offset{offsetof(Vertex, normal)};
    abcg::glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE,
                                sizeof(Vertex),
                                reinterpret_cast<void *>(offset));
  }

  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);

  m_KaLoc = abcg::glGetUniformLocation(program, "Ka");
  m_KdLoc = abcg::glGetUniformLocation(program, "Kd");
  m_KsLoc = abcg::glGetUniformLocation(program, "Ks");

  // Load location of uniform variables of shader
  m_modelMatrixLoc = modelMatrixLoc;
  m_normalMatrixLoc = normalMatrixLoc;
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

      auto const modelViewMatrix{glm::mat3(m_viewMatrix * model)};
      auto const normalMatrix{glm::inverseTranspose(modelViewMatrix)};
      abcg::glUniformMatrix3fv(m_normalMatrixLoc, 1, GL_FALSE,
                               &normalMatrix[0][0]);

      // Set color (checkerboard pattern)
      auto const grey{(z + x) % 2 == 0 ? 0.5f : 1.0f};
      abcg::glUniform4f(m_colorLoc, grey, grey, grey, 0.0f);
      // abcg::glUniform4f(m_colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);
      // abcg::glUniform4f(m_colorLoc, 0.36f, 0.26f, 0.56f, 0.8f); // purple

      abcg::glUniform1f(m_KaLoc, m_Ka);
      abcg::glUniform1f(m_KdLoc, m_Kd);
      abcg::glUniform1f(m_KsLoc, m_Ks);

      abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
  }
}

void Ground::paint() {
  abcg::glBindVertexArray(m_VAO);

  // Building a cubic surface
  drawTile(0.0f, glm::vec3(1, 0, 0), 0.0f, 0.5f, 0.0f, 1.0f, -1.0f,
           1.0f); // x,z, 0
  drawTile(180.0f, glm::vec3(1, 0, 0), 0.0f, 3.5f, 0.0f, 1.0f, 1.0f,
           1.0f); // x,z, +
  drawTile(90.0f, glm::vec3(0, 0, 1), 1.0f + m_N, 1.5f, 0.0f, -1.0f, 1.0f,
           1.0f); //  y,z, 0
  drawTile(270.0f, glm::vec3(0, 0, 1), 1.0f + m_N, 1.5f, 0.0f, 1.0f, 1.0f,
           1.0f); // y,z, +
  drawTile(-90.0f, glm::vec3(1, 0, 0), 0.0f, 1.5f, 1.0f + m_N, 1.0f, 1.0f,
           -1.0f); // x,y, 0
  drawTile(90.0f, glm::vec3(1, 0, 0), 0.0f, 1.5f, 1.0f + m_N, 1.0f, 1.0f,
           1.0f); // x,y, +

  abcg::glBindVertexArray(0);
}

void Ground::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}