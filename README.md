# 🌀 Fract-ol

Um renderizador de fractais de alta performance desenvolvido em C utilizando a biblioteca gráfica **MinilibX**. Este projeto permite explorar visualmente os conjuntos matemáticos de Mandelbrot e Julia com navegação em tempo real.

Recentemente otimizado com **Multithreading** para garantir fluidez máxima durante o zoom e movimentação.

## 🚀 Funcionalidades

*   **Multithreading:** O motor de renderização divide a tela em faixas processadas simultaneamente por múltiplas threads (CPU cores), eliminando o lag.
*   **Zoom Infinito:** Use o scroll do mouse para mergulhar nos detalhes do fractal. O zoom é centralizado onde o mouse aponta.
*   **Cores Psicodélicas:** Algoritmo de coloração baseado em frequência senoidal para transições suaves.
*   **Conjunto de Julia Customizável:** Passe parâmetros diferentes na execução para ver formas completamente novas.

## 🛠️ Compilação

Certifique-se de estar em um ambiente Linux com as dependências da `MinilibX` e `X11` instaladas.

Para compilar, execute:

```bash
make
```

Isso irá gerar o executável `fractol`.

## 🎮 Como Usar

Execute o programa passando o nome do fractal desejado como argumento.

### Mandelbrot

O clássico conjunto de Mandelbrot:

```bash
./fractol mandelbrot
```

### Julia

Para o conjunto de Julia, você deve fornecer dois números (parte real e imaginária) que definem a constante `c` do conjunto:

```bash
./fractol julia -0.8 0.156
```

Outros exemplos interessantes para testar:
```bash
./fractol julia 0.285 0.01
./fractol julia -0.7269 0.1889
./fractol julia -0.4 0.6
```

## 🕹️ Controles

| Entrada | Ação |
| :--- | :--- |
| **Scroll do Mouse** | Zoom In / Zoom Out (focado no cursor) |
| **Setas (↑ ↓ ← →)** | Mover a câmera pelo plano complexo |
| **Numpad +** | Aumentar a frequência das cores (Psychedelic mode +) |
| **Numpad -** | Diminuir a frequência das cores (Psychedelic mode -) |
| **ESC** | Sair do programa |

## ⚡ Detalhes Técnicos

### Otimização com Threads
O cálculo de fractais é uma tarefa computacionalmente intensiva, pois cada pixel requer dezenas ou centenas de iterações matemáticas complexas.

Nesta versão, utilizamos a biblioteca `pthread`. A imagem é fatiada horizontalmente e cada fatia é delegada a uma thread diferente. Isso permite utilizar 100% da capacidade de processamento da CPU, resultando em uma renderização muito mais rápida do que a abordagem single-thread tradicional.

---
*Desenvolvido por clados-s*