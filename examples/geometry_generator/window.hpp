#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>

#include "abcgOpenGL.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void setGenerate();
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;
  void generateRandom();

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_VAO{};
  GLuint m_VBOPositions{};
  GLuint m_VBOColors{};
  GLuint m_program{};

  std::default_random_engine m_randomEngine;

  std::array<glm::vec4, 2> m_colors{
      {{0.104f, 0.113f, 0.179f, 1}, {0.67f, 0.30f, 0.254f, 1}}};

  bool generate = false;
  int m_sides = 3;
  float m_scale = 0.125f;

  void setupModel(int sides);
};

#endif