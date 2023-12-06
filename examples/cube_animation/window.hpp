#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"
#include "cube.hpp"
#include "ground.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onUpdate() override;
  void onPaint() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  std::array<glm::vec3, 36> const m_skyPositions{{
      // Front
      {-2, -2, +2}, {+2, -2, +2}, {+2, +2, +2},
      {-2, -2, +2}, {+2, +2, +2}, {-2, +2, +2},
      // Back
      {+2, -2, -2}, {-2, -2, -2}, {-2, +2, -2},
      {+2, -2, -2}, {-2, +2, -2}, {+2, +2, -2},
      // Right
      {+2, -2, -2}, {+2, +2, -2}, {+2, +2, +2},
      {+2, -2, -2}, {+2, +2, +2}, {+2, -2, +2},
      // Left
      {-2, -2, +2}, {-2, +2, +2}, {-2, +2, -2},
      {-2, -2, +2}, {-2, +2, -2}, {-2, -2, -2},
      // Top
      {-2, +2, +2}, {+2, +2, +2}, {+2, +2, -2},
      {-2, +2, +2}, {+2, +2, -2}, {-2, +2, -2},
      // Bottom
      {-2, -2, -2}, {+2, -2, -2}, {+2, -2, +2},
      {-2, -2, -2}, {+2, -2, +2}, {-2, -2, +2}}};

  std::string const m_skyShaderName{"skybox"};
  GLuint m_skyVAO{};
  GLuint m_skyVBO{};
  GLuint m_skyProgram{};
  GLuint m_skyTexture{};
  void createSkybox();
  void renderSkybox();
  void loadSkyTexture(std::string const &path);
  void destroySkybox() const;

  
  glm::ivec2 m_viewportSize{600, 600};
  float m_scale{0.2f};
  int m_N{1}; // Número de tiles do chão, 2N+1 x 2N+1

  GLint m_modelMatrixLoc{};
  glm::mat4 m_viewMatrix{1.0f};
  GLint m_viewMatrixLoc{};
  glm::mat4 m_projMatrix{1.0f};
  GLint m_projMatrixLoc{};
  GLint m_colorLoc{};


  Ground m_ground;
  Cube m_cube;
  GLuint m_program{};

  // Light Properties
  glm::vec3 m_lightPos{0.0f, 1.0f, 0.0f};

  GLint m_IaLoc{};
  GLint m_IdLoc{};
  GLint m_IsLoc{};

  float m_Ia{1.0};
  float m_Id{1.0};
  float m_Is{1.0};

  GLint m_normalMatrixLoc{};
  GLint m_lightPositionLoc{};
};

#endif