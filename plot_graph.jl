
using Colors
import Cairo, Fontconfig
using Plots, IJulia
pyplot()

#filename = "random-10.col";
#filename = "random-40.col";
#filename = "random-70.col";
#filename = "random-100.col";
#filename = "brock200_2.col";
#filename = "dsjc125.1.col";
#filename = "dsjc250.5.col";
#filename = "dsjc500.1.col";
#filename = "dsjc500.5.col";
filename = "dsjc500.9.col";
#filename = "dsjc1000.1.col";
# filename = "dsjc1000.5.col";
#filename = "dsjc1000.9.col";
filename_sol = string("Sol 5min/",filename[1:length(filename)-4],"_sol.txt")
filepath = "C:/Users/gache/Documents/ENPC/3A/Metaheuristic/git/Instances/"


function build_graph()
    f     = open(string(filepath, filename));
    line1 = readline(f);
    dummy1, dummy2, n, m = split(line1);
    n     = parse(Int, n);
    m     = parse(Int, m);
    edges = zeros(Int, n,n);
    print("vertices : ", n, " edges : ",m)
    for i in 1:m
        line = readline(f);
        useless_e, v1, v2 = split(line);
        #println("edge ", v1, ",", v2);
        v1 = parse(Int, v1);
        v2 = parse(Int, v2);
        edges[v1,v2] = 1;
        edges[v2,v1] = 1;
    end
    #println(edges);

    iter  = []
    solution  = []#zeros(Int,10,10)
    for (i,line) in enumerate(eachline(string(filepath, filename_sol)))
        table = split(line);
        push!(iter,parse(Int64, table[2]))
        push!(solution,[])
        for j in 1:length(table)-3;
            push!(solution[i], parse(Int64, table[3+j]))
        end
    end

    p_graphe, x, y = plot_graphe(n, edges)
    Anim = Plots.Animation()
    for improve in 1:length(iter)
        p = plot_clique(solution[improve],n, edges)|> IJulia.display
        Plots.frame(Anim)
    end
    gif(Anim, string(filepath,"Sol 5min/", filename[1:length(filename)-4],"_anim.gif"), fps = 1)
end

function plot_graphe(n, edges)
    R = 50/n
    x = [R*cos((i-1)*2*pi/n) for i in 1:n]
    y = [R*sin((i-1)*2*pi/n) for i in 1:n]
    pl_new = Plots.plot(xaxis=false, yaxis=false,
    right_margin = 12Plots.mm, left_margin = 12Plots.mm,
    top_margin = 12Plots.mm, bottom_margin=12Plots.mm)
    scatter!(
         pl_new, x, y,
         marker = (:circle, 10*10/n, 0.5, "grey"),
         legend=false#:outertopleft
     )
     for i in 1:n
         annotate!(1.1*x[i], 1.1*y[i], string(i), 5)
         # for j in i+1:n
         #     if edges[i,j]==1
         #         plot!([x[i],x[j]],[y[i],y[j]], color = "grey")
         #     end
         # end
     end
     return pl_new, x, y
end

function plot_clique(sol, n, edges)
    R = 50/n
    pl_new,x,y = plot_graphe(n, edges)
    scatter!(
      pl_new, [x[i] for i in sol], [y[i] for i in sol],
      marker = (:circle, 10*10/n, 0.5, "red"),
      legend=false#:outertopleft
    )
    for i in 1:length(x)
        for j in i+1:length(x)
            if i in sol && j in sol
                plot!([x[i],x[j]],[y[i],y[j]], color = "red")
            end
        end
    end

    annotate!(0,0, string("Taille : ",length(sol)), 10)
    return pl_new
end


    # nodecolors = []
    # for i in 1:n
    #     if i in solution[1]
    #         push!(nodecolors, colorant"#CB3C33")
    #     else
    #         push!(nodecolors, colorant"lightgrey")
    #     end
    # end
    # edgecolors = [colorant"lightgray" for i in  1:m]
    # edge_i = 1
    # for i in 1:n
    #     for j in i+1:n
    #         if i in solution[improve] && j in solution[improve]
    #             edgecolors[edge_i] = colorant"#CB3C33"
    #         end
    #         edge_i += edges[i,j]
    #     end
    # end
    #compose(context(), gplot(g))



build_graph()
