import time
import networkx as nx


def read_graph(path):
    with open(path, 'r', encoding="utf-8") as f:
        lines = [line.strip() for line in f if line.strip()]
    n = int(lines[0])
    edges = []
    for line in lines[1:]:
        a, b = map(int, line.split())
        edges.append((a, b))
    G = nx.Graph()
    G.add_nodes_from(range(1, n + 1))
    G.add_edges_from(edges)
    return G


filenames = ["graph1.txt", "graph2.txt", "graph3.txt"]

for filename in filenames:
    print(f"File: {filename}")

    G = read_graph(filename)

    start = time.perf_counter()
    max_clique = []
    for clique in nx.find_cliques(G):
        if len(clique) > len(max_clique):
            max_clique = clique
    end = time.perf_counter()

    print("Library max clique:", max_clique)
    print("Size:", len(max_clique))
    print("Library time:", (end - start) * 1000, "ms")
    print()
