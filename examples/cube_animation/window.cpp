#include "window.hpp"

#include <filesystem>

void Window::onEvent(SDL_Event const &event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
      m_cube.moveUp();
    if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
      m_cube.moveDown();
    if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
      m_cube.moveLeft();
    if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
      m_cube.moveRight();
  }
}

void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  abcg::glClearColor(0, 0, 0, 1);
  abcg::glEnable(GL_DEPTH_TEST);

  m_viewMatrix =
      glm::lookAt(glm::vec3(1.9f, 1.9f, 1.9f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));

  m_program =
      abcg::createOpenGLProgram({{.source = assetsPath + "cube_trail.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "cube_trail.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  m_viewMatrixLoc = abcg::glGetUniformLocation(m_program, "viewMatrix");
  m_projMatrixLoc = abcg::glGetUniformLocation(m_program, "projMatrix");
  m_modelMatrixLoc = abcg::glGetUniformLocation(m_program, "modelMatrix");
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_normalMatrixLoc = abcg::glGetUniformLocation(m_program, "normalMatrix");
  m_lightPositionLoc = abcg::glGetUniformLocation(m_program, "lightPosition");
  m_IaLoc = abcg::glGetUniformLocation(m_program, "Ia");
  m_IdLoc = abcg::glGetUniformLocation(m_program, "Id");
  m_IsLoc = abcg::glGetUniformLocation(m_program, "Is");

  m_ground.create(m_program, m_modelMatrixLoc, m_colorLoc, m_normalMatrixLoc,
                  m_viewMatrix, m_scale, m_N);
  m_cube.loadObj(assetsPath + "box.obj");
  m_cube.create(m_program, m_modelMatrixLoc, m_colorLoc, m_normalMatrixLoc,
                m_viewMatrix, m_scale, m_N);
}

void Window::onUpdate() {
  m_cube.update(gsl::narrow_cast<float>(getDeltaTime()));
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  abcg::glUseProgram(m_program);

  // Set uniform variables that have the same value for every model
  auto const aspect{gsl::narrow<float>(m_viewportSize.x) /
                    gsl::narrow<float>(m_viewportSize.y)};

  m_projMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 5.0f);

  abcg::glUniformMatrix4fv(m_viewMatrixLoc, 1, GL_FALSE, &m_viewMatrix[0][0]);
  abcg::glUniformMatrix4fv(m_projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
  abcg::glUniform3f(m_lightPositionLoc, m_lightPos.x, m_lightPos.y,
                    m_lightPos.z);
  abcg::glUniform1f(m_IaLoc, m_Ia);
  abcg::glUniform1f(m_IdLoc, m_Id);
  abcg::glUniform1f(m_IsLoc, m_Is);

  m_cube.paint();
  m_ground.paint();

  abcg::glUseProgram(0);
}

void Window::onResize(glm::ivec2 const &size) { m_viewportSize = size; }

void Window::onDestroy() {
  m_ground.destroy();
  m_cube.destroy();
  abcg::glDeleteProgram(m_program);
}