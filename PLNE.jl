using JuMP, CPLEX

#filename = "random-10.col";
#filename = "random-40.col";
#filename = "random-70.col";
#filename = "random-100.col";
#filename = "dsjc125.1.col";
filename = "brock200_2.col";
#filename = "dsjc125.1.col";
#filename = "dsjc250.5.col";
#filename = "dsjc500.1.col";
#filename = "dsjc500.5.col";
# filename = "dsjc500.9.col";
#filename = "dsjc1000.1.col";
# filename = "dsjc1000.5.col";
# filename = "dsjc1000.9.col";
filepath = "C:/Users/gache/Documents/ENPC/3A/Metaheuristic/github/Instances/"

f     = open(string(filepath, filename));
line1 = readline(f);
dummy1, dummy2, n, m = split(line1);
n     = parse(Int, n);
m     = parse(Int, m);
edges = zeros(Int, n,n);

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


function PLNE()
    model = direct_model(CPLEX.Optimizer())
    @variable(model, 0<=x[1:n]<=1, Int)

    @objective(model, Max, sum(x[i] for i in 1:n))
    for i in 1:n
        for j in 1:n
            if(i<j && edges[i,j]!=1)
                @constraint(model, x[i]+x[j] <= 1.5)
            end
        end
    end
    optimize!(model)

    @show objective_value(model);
end

PLNE()
