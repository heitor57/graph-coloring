# Graph coloring

## Compile

    make

## Clean

    make clean

## Program

    graph-coloring -i <entry file> -o <out file> -d (DEBUG) -c (CHECK SOLUTION) -p <Implementations>\n
    Possible implementations
    -p b(Branch and bound) d(DSatur) r(RLF)
    -p a(All)
    Examples: graph-coloring -i in.txt -o out.txt -d -p d
    graph-coloring -i in.txt -o out.txt
    graph-coloring -i in.txt

As opções prováveis a serem mais utilizadas são o i,o e p
Caso queira passar somente o arquivo de entrada como parâmetro é possível, e isso fará com que a saída seja na saída padrão e o paradigma a ser utilizado irá ser perguntado durante a execução.
Para pular a pergunta de qual paradigma a ser utilizado basta utilizar o parametro p com algum paradigma (b,d,r) ou todos (a).


A entrada do programa deve ter o seguinte padrão:

<vertices>
<vertice x> <vertice y>
<vertice k> <vertice i>
...

Toda linha deve ter um '\n' no final.
