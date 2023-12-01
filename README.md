# Integrantes

|RA|Nome|
|:--:|:--:|
|11201811074|Lucas Prado Santos|
|11201812367|Karine da Silva Sobrinho| 


# Descrição

Projeto tem por base a movimentação animada, utilizando o OpenGL, de um cubo sobre outra superfíce cúbica. O translado pode ser gerado atráves do input do usúario através do teclado, utilizando setas ou WASD. Tem-se como base a animação clássica do console [GameCube](https://www.youtube.com/watch?v=CpmYW-gCSy4).

# Build e configurações de ambiente 
Disponível em: https://hbatagelo.github.io/cg/config.html

# Página Web

Disponível em: https://pradolucas.github.io/abcg/geometry_generator/

## Folders

```sh
cube_trail/
├── CMakeLists.txt
├── assets
│   ├── box.obj
│   ├── cube_trail.frag
│   └── cube_trail.vert
├── cube.cpp
├── cube.hpp
├── ground.cpp
├── ground.hpp
├── main.cpp
├── vertex.hpp
├── window.cpp
└── window.hpp
```

### Window

Classe principal onde são definidas as funções para criação e atualização dos objetos em tela. Bem como lidar como o input do usuário.

- onEvent: Trata o input do usuário.
- onCreate
- onUpdate
- onPaint
- onResize
- onDestroy: Realiza a chamada das funções destroy dos objetos das classes Ground e Cube.

- m_ground: Instância da classe Ground. Representa a superfície do cubo maior.  
- m_cube: Instância da classe Cube.

### Ground

Classe que compões a superfície onde ocorreo translado do cubo menor.

- create: É definido o vértices que definem um quadrado em `m_vertices`, bem como as variáveis... 
- drawTile: Função auxiliar que realizar o desenho de um grid planar com baseado no quadrado previamente definido. 
- paint: Utilizando a função drawTile são desenhados 6 planos com fim de gerar a superfície de um cubo
- destroy: Desassocia VBO e VAO.

### Cube

Classe resposável pela criação e movimentação realizada pelo cubo.

- loadObj: Carrega o objeto `assets/box.obj`
- paint
- update
- create
- destroy
- moveLeft
- moveRight
- moveUp
- moveDown
- move: Define a animação realizada durante o movimento translado de forma a realizar um movimento suave.
- translate: Trata do translado alterando o parâmetro de m_position. É levado em conta toda a movimentação nas faces bem como suas transições. 
- resetAnimation: Reseta os valores das variáveis utilizadas na movimentação e animação dos cubo.

- m_animationMatrix
- Orientation: Classe enumerada representando o sentido de movimentação realizado no translado.
- PlaneFace: Classe enumerda representando a face sobre qual o objeto cubo está presente. 

- m_isMoving
- m_maxPos
- m_angleVelocity
- m_border: Booleano que indica se o objeto cubo está na borda de uma face.

### Vertex

Classe com caracteristicas que compõem um vértice.

### Shaders
