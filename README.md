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

The most likely options to be used are i,o and p.
In case you only want to pass the input file as a parameter, it is possible, and that will make the output be in the standard output and the paradigm to be used will be asked during the execution.
To skip the question of which paradigm to use, just use the parameter p with some paradigm (b,d,r) or all (a).


The program input should have the following pattern:

<vertices>
<vertex x> <vertex y>
<vertex k> <vertex i>
...

Every line must have a '\n' at the end.
