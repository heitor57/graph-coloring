#names(Data) <- c("Implementacao","Vertices","Arestas","GrauMaximo","CoresMin","Cores","Tempo","Dot")

set grid
set xlabel "Vértices"
set ylabel "Tempo(s)"
f(x)= (a)**(x-b)
fit f(x) "<(grep -P 'rand87' data/data.txt | grep -P '^b' | sort -nk2 | cut -d' ' -f2,7)" via a,b

title_f(a,b) = sprintf('f(x) = %.2f^{(x-%.2f)}', a, b)
plot "<(grep -P 'rand87' data/data.txt | grep -P '^b' | sort -nk2)" using ($2):($7) with lines lc 3 title "Tempo real",\
     f(x) title title_f(a,b)

