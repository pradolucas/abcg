# Integrantes

|RA|Nome|
|:--:|:--:|
|11201811074|Lucas Prado Santos|
|11201812367|Karine da Silva Sobrinho| 


# Descrição
Projeto para a geração de formas personalizadas pelo usuário, as quais podem ser parametrizadas em relação ao tamanho, cores internas e externas, incluindo a opção de criar gradientes. Além disso, o projeto permite a escolha do número de triângulos que compõem a forma e também oferece a funcionalidade de geração aleatória.

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
