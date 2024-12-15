import networkx as nx
import json
import matplotlib.pyplot as plt
from collections import defaultdict
from networkx.readwrite import json_graph
from shapely.geometry import LineString
import community as mod_community_louvain  # Louvain алгоритм


def load_graph(path):
    with open(path, encoding="utf-8") as f:
        data = json.load(f)
    G = json_graph.node_link_graph(data)
    for u, v, d in G.edges(data=True):
        if 'geometry' in d and isinstance(d['geometry'], list):
            d['geometry'] = LineString(d['geometry'])
    return G


def visualize_clusters_on_map(G, partition, output_path="clustered_supercomputer.png"):
    pos = nx.spring_layout(G)
    cluster_colors = {cluster: plt.cm.tab20(i % 20) for i, cluster in enumerate(set(partition.values()))}

    plt.figure(figsize=(12, 8))
    for node, cluster in partition.items():
        nx.draw_networkx_nodes(G, pos, nodelist=[node], node_color=[cluster_colors[cluster]], node_size=50)

    nx.draw_networkx_edges(G, pos, alpha=0.2, edge_color="gray")

    plt.title("Кластеризация графа суперкомпьютера", fontsize=14)
    plt.axis("off")
    plt.savefig(output_path)
    plt.show()


def main():
    graph_path = "supercomputer_topology.json"
    G = load_graph(graph_path)
    if nx.is_directed(G):
        G = G.to_undirected()
    partition = mod_community_louvain.best_partition(G)
    visualize_clusters_on_map(G, partition)


if __name__ == "__main__":
    main()
