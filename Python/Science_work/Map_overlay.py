import networkx as nx
import json
import mod_community_louvain
import matplotlib.pyplot as plt
import osmnx as ox
from collections import defaultdict
from networkx.readwrite import json_graph
from shapely.geometry import LineString


def load_graph(path):
    with open(path, encoding="utf-8") as f:
        data = json.load(f)
    G = json_graph.node_link_graph(data)

    for u, v, d in G.edges(data=True):
        if 'geometry' in d and isinstance(d['geometry'], list):
            d['geometry'] = LineString(d['geometry'])

    return G


def visualize_clusters_on_map(G, partition):
    fig, ax = plt.subplots(figsize=(12, 8))
    ox.plot_graph(G, ax=ax, node_size=0, edge_linewidth=0.2, edge_color="grey", show=False, close=False,
                  bgcolor="white")

    cluster_colors = {cluster: plt.cm.tab20(i % 20) for i, cluster in enumerate(set(partition.values()))}

    cluster_map = defaultdict(list)
    for node, cluster in partition.items():
        cluster_map[cluster].append(node)

    for cluster, nodes in cluster_map.items():
        x = [G.nodes[node]['x'] for node in nodes]
        y = [G.nodes[node]['y'] for node in nodes]
        ax.scatter(x, y, color=cluster_colors[cluster], label=f"Cluster {cluster}", s=10)

    handles, labels = ax.get_legend_handles_labels()
    sorted_labels, sorted_handles = zip(*sorted(zip(labels, handles)))
    plt.title("Москва разбиение по кластерам")
    plt.savefig("clustered_map.png", format="png")
    plt.show()


def main():
    graph_path = ("Clustered_Moscow/Moscow_roads.json")
    G = load_graph(graph_path)

    if nx.is_directed(G):
        G = G.to_undirected()

    partition = mod_community_louvain.best_partition(G)

    visualize_clusters_on_map(G, partition)


if __name__ == "__main__":
    main()