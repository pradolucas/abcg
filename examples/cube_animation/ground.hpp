#ifndef GROUND_HPP_
#define GROUND_HPP_

#include "abcgOpenGL.hpp"
#include "vertex.hpp"

class Ground {
public:
  void create(GLuint program, GLint modelMatrixLoc, GLint colorLoc, glm::mat4 viewMatrix, float scale, int N);
  void drawTile(float, glm::vec3, float, float, float, float, float,float);
  void paint();
  void destroy();

private:
  std::vector<Vertex> m_vertices;
  float m_scale;
  int m_N; //Configure number of tiles on the grid of 2N+1 x 2N+1 tiles
  GLuint m_VAO{};
  GLuint m_VBO{};
  
  GLint m_modelMatrixLoc{};
  glm::mat4 m_viewMatrix;

  GLint m_colorLoc{};

};

#endif