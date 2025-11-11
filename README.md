# Cub3D

Este repositório contém uma implementação pessoal do projeto Cub3D (raycaster estilo Wolfenstein) construída para o ambiente de 42. O objetivo aqui foi entregar um motor simples de raycasting com parsing do formato `.cub`, carregamento de texturas XPM e algumas melhorias/recursos específicos do meu fork.

![crazy8 gif](assets/gif/crazy8.gif)

## Destaques deste fork

- Validação de parser reforçada
	- Valida mapas como fechados por `1` e recusa mapas não retangulares ou com caracteres inválidos.
	- Detecta conteúdo inválido após o bloco do mapa e checa corretamente definições de textura e RGB.

- Tratamento de texturas e XPM
	- Carrega texturas XPM via MiniLibX e mapeia coordenadas de textura para as paredes.

- Vinheta (vignette)
	- Efeito de vinheta aplicado na renderização (mapa de intensidade `vig_map`) para escurecer as áreas distantes e dar profundidade visual.

- Raycaster funcional
	- Raycasting por coluna com mapeamento de texturas, colisão do jogador, e desenho de paredes.

- Controles / movimento
	- Movimento com WASD, rotação com setas, colisão com paredes implementada.

## Estrutura do repositório

- `srcs/` — código-fonte em C
	- `read/` — parser: `read_map.c`, `after_map.c`, utilitários
	- `parser/` — validações (`map_parse.c`, `texture_parse.c`, `directions.c`)
	- `raycast/` — algoritmo de raycasting e inicialização
	- `player/` — movimento e entrada
	- `texture/` — carregamento XPM e parsing RGB
	- `draw/`, `vignette/`, `free/` — desenho, vinheta e limpeza
- `maps/` — mapas de exemplo (`brick.cub`, `crazy8.cub`, `preda.cub`, `springfield.cub`)
- `assets/texture/` — XPMs usados como texturas
- `libft/`, `minilibx-linux/` — dependências incluídas no repositório

## Como compilar

O projeto usa `Makefile` presente na raiz. No Linux com MiniLibX já configurada (ou usando a `minilibx-linux` que está no repo), faça:

```zsh
make
```

Se preferir limpar objetos:

```zsh
make fclean
```

## Como executar

Depois de compilado, rode o binário passando um arquivo `.cub` como argumento:

```zsh
./cub3d maps/crazy8.cub
```

Troque o arquivo em `maps/` para testar os outros cenários (por exemplo `maps/brick.cub`).

## Erros comuns e solução

- XPM não carregando
	- Verifique caminhos nas diretivas `NO`, `SO`, `WE`, `EA` do `.cub` (são caminhos relativos ao diretório do executável).
	- Se o MLX falhar ao carregar a imagem, o programa imprime uma mensagem e sai.

- Mapa aceito quando não deveria
	- Este repositório valida que todas as linhas do mapa tenham o mesmo comprimento antes de checar as bordas — se você tem linhas com indentação variável, garanta que o arquivo `.cub` esteja formatado para representar a matriz do mapa corretamente (sem deixar gaps que sejam considerados células válidas).

- Vazamentos detectados por Valgrind
	- O projeto libera `game->map` e texturas na saída, mas `get_next_line` tem buffers estáticos que podem ficar como "still reachable" — isso é esperado em algumas implementações do GNL. Use a versão da GNL sem buffers estáticos se quiser saída limpa no Valgrind.

## Mapas incluídos

- `crazy8.cub` — mapa principal
- `brick.cub` — mapa de teste
- `preda.cub`, `springfield.cub` — exemplos adicionais

## Notas de desenvolvimento

- O parser realiza as seguintes etapas: leitura linha a linha, detecção de diretivas (`NO`, `SO`, `WE`, `EA`, `F`, `C`), construção de `char **map` e validação (`is_map_closed`).
- A vinheta é précomputada em `init_vignette` e aplicada no momento do put_pixel para escurecer com base na distância.

## Autores:

- Bruno N de Queiroz
- Rafael Tanaka

---
