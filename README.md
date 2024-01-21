<p align="center">
  <img src="https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExOHYwMXJkZHBhcXV6aDI4NHIzMTBqbGFpYjQ0MHYxM2o3bzk0eDljeCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/jBs92nCbLoZpnJkppb/giphy.gif" alt="animated" />
</p>

# Integrantes

|RA|Nome|
|:--:|:--:|
|11201811074|Lucas Prado Santos|
|11201812367|Karine da Silva Sobrinho| 


# Descrição

Projeto tem por base a movimentação animada, utilizando o OpenGL, de um cubo sobre outra superfíce cúbica. O translado pode ser gerado atráves do input do usúario através do teclado, utilizando setas ou WASD. Tem-se como base a animação clássica do console [GameCube](https://www.youtube.com/watch?v=CpmYW-gCSy4).

Mais detalhadamente:

- Shader Programs: A aplicação define dois programas de shader, um para o vertex shader e outro para o fragment shader. Esses shaders são usados para renderizar os polígonos na janela gráfica.
- Configuração Inicial: A função onCreate é chamada quando a janela é criada. Ela carrega os shaders, configura a cor de fundo da janela para preto e semeia o gerador de números aleatórios.
- Renderização de Polígonos: A função onPaint é responsável por renderizar os polígonos na janela. Ela configura os polígonos com um número de lados definido pelo usuário e os desenha na tela. A cor e o tamanho dos polígonos podem ser aleatórios.
- Interface do Usuário (UI): A função onPaintUI desenha a interface do usuário usando a biblioteca ImGui. Ela fornece controles para o usuário interagir com a aplicação, como um controle deslizante para ajustar o número de lados dos polígonos, botões para gerar polígonos aleatórios e limpar a janela.
- Limpeza da Janela: O botão "Clear window" permite ao usuário limpar a janela, removendo todos os polígonos desenhados.
- Geração Aleatória: A aplicação permite ao usuário gerar polígonos regulares com cores aleatórias, ajustando o número de lados e pressionando o botão "Generate Random."
- Reinicialização da Renderização: O botão "Generate" permite ao usuário regerar os polígonos com as configurações atuais.
- Manipulação de Polígonos: A função setupModel é responsável por configurar os polígonos, incluindo a definição de suas posições e cores. Ela é chamada sempre que os polígonos precisam ser renderizados.
- Redimensionamento da Janela: Quando a janela é redimensionada, a função onResize é chamada, atualizando o tamanho da janela e limpando a tela.
- Destruição da Aplicação: A função onDestroy é chamada quando a janela é fechada e é usada para limpar os recursos alocados, como os programas de shader e buffers.
- No geral, a aplicação permite ao usuário criar e manipular polígonos regulares com cores e números de lados personalizáveis em uma janela gráfica interativa. É uma aplicação gráfica simples que demonstra o uso de shaders, geração de números aleatórios e renderização de formas geométricas.

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

- **onEvent**: Trata o input do usuário.
- **onCreate**: Cria o programa para renderizar todo os componentes além de setar variáveis.
- **onUpdate**: Chama a função update de Cube passando `deltaTime` como parâmetro.
- **onPaint**: Chama a função paint de de ambos os cubos (Ground e Cube).
- **onResize**: Redefine a dimensão da janela em `m_viewportSize`.
- **onDestroy**: Realiza a chamada das funções destroy dos objetos das classes Ground e Cube.

- **m_ground**: Instância da classe Ground. Representa a superfície do cubo maior.  
- **m_cube**: Instância da classe Cube.

### Ground

Classe que compõe a superfície onde ocorre o translado do cubo menor.

- **create**: É definido o vértices que definem um quadrado em `m_vertices`, bem como as variáveis... 
- **drawTile**: Função auxiliar que realizar o desenho de um grid planar com baseado no quadrado previamente definido. 
- **paint**: Utilizando a função drawTile são desenhados 6 planos com fim de gerar a superfície de um cubo
- **destroy**: Desassocia VBO e VAO.

### Cube

Classe resposável pela criação e movimentação realizada pelo cubo.

- **loadObj**: Carrega o objeto `assets/box.obj`
- **paint**: Atualiza o valor das variáveis e renderiza o cubo.
- **update**: Atualiza chamando a função move passando o parâmentro `deltatime`.
- **create**: Cria o VAO, VBO e EBO do Cubo, criando toda geometria, além de salvar a localização das variávies uniformes do programa de renderização.
- **destroy**: Destroi VBO, VAO e EBO;
- **moveLeft**, **moveRight**, **moveUp**, **moveDown** : Função de movimentação do cubo, verifica se está sendo moviemntado naquele momento e se não trata para cada face do cubo maior qual movimento adequado e qual a rotação.
- **move**: Define a animação realizada durante o movimento translado de forma a realizar um movimento suave.
- **translate**: Trata do translado alterando o parâmetro de m_position. É levado em conta toda a movimentação nas faces bem como suas transições. 
- **resetAnimation**: Reseta os valores das variáveis utilizadas na movimentação e animação dos cubo.


- m_animationMatrix
- **Orientation**: Classe enumerada representando o sentido de movimentação realizado no translado.
- **PlaneFace**: Classe enumerda representando a face sobre qual o objeto cubo está presente. 


- **m_isMoving**: True durante a animação.
- **m_maxPos**: Variável utilizada para limitar o movimento do cubo menor sobre as superfícies .
- **m_angleVelocity**: Velocidade qual ocorrerá a animação de rotação do cubo.
- **m_border**: Booleano que indica se o objeto cubo está na borda de uma face.

A função move, em especial, merece atenção em sua explicação. Tome como referencial a face superior, a posição inicial do cubo. Ao realizar um _narrow cast_ em uma classe enum recebemos um inteiro correspondente a sua ordem de definição, i.e.: 
  - DOWN::0
  - RIGHT::1
  - UP::180
  - LEFT::270
 
Antes de ocorrer qualquer movimento realizamos uma rotação no eixo y de acordo com o movimento desejado,  0 graus para _Down_, 90 graus caso _Right_ e assim por diante. Esta rotação tem como objetivo o posicionamento correto do eixo x. Observe que caso tenhamos o movimento do cubo para baixo o sentido anti-horário de x aponta na direção correta de rotação. Analogamente, caso haja um movimento para direita, é realizado uma rotação em y de 90 graus resultando em x ser corretamente apontado para essa direção. 
Além disso, é necessário transladar o objeto de forma que a extremidade correta do cubo seja alinhada com o eixo da segunda rotação. 

Para as demais faces, foi utilizado o mesmo principio realizando transformações no referencial.

### Vertex

Classe com caracteristicas que compõem um vértice, i.e., as posições que o compõe e o seu vetor normal, para cálculos de iluminação.
