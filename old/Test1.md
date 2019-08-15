## Questão 1
### Uma malha de triângulos geralmente é armazenada em duas estruturas de dados. Que informação encontramos em cada? Dê um motivo para que não tenhamos somente uma e explique como seria a descrição da malha dessa forma.
- uma estrutura armazena os vértices e noutra as arestas
- pra fazer em uma unica basta que cada "linha" seja os três pontos de um triangulo
- porque as informações de alguns vértices ficam duplicadas
  * e.g. um quadrado formado por 2 triangulos teria a aresta em comum seria descrita duas vezes
  * tendo as duas estruturas teriamos apenar uma vez os pontos em comum e a informação da aresta noutra estrutura
- outro motivo é que fazer algoritmos pra remoção de pontos fica mais simples, basta remover a aresta

## Questão 2
### O processo de render é semelhante a tirarmos uma foto. Cada pixel possui somente uma cor. O que essa cor representa? Qual seria a melhor cor? Qual a cor que o rasterizador usa?
- tudo que está vendo em uma determinada região
  * todas as cores que se enxergam através do pixel
- mas como a imagem digital é discretizada então cada cor é um "resumo" daquelas cores
  * o rasterizador pode fazer uma interpolação das cores da região, ou usar a cor de predominância
  * o que __se usa de fato__ é usar a cor do meio da região
    + note que se tivermos mais resolução esse algoritmo melhora, ficando mais proximo do real

## Questão 3
### Explique para que serve e como funciona a interpolação bilinear usada na interpolação dos atributos dos vértices feita durante a rasterização.
- interpolação é utilizado pra preencher espaços sobre os quais não se tem informação
  * mas se tem informação sobre pontos/regiões próximas a região de interesse
- o fato de ser bilinear é porque usasse duas interpolações, a segunda usa o resultado da anterior
