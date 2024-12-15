import re
import json
from collections import defaultdict
from pyvis.network import Network
import community as mod_community_louvain  # Louvain алгоритм
import networkx as nx
import matplotlib.pyplot as plt
from networkx.readwrite import json_graph


def visualize_3d_graph_with_clustering(json_path, output_html):
    with open(json_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    G = nx.Graph()
    for node in data["nodes"]:
        G.add_node(node["id"], label=node["id"], title=f"Type: {node['type']}")

    for link in data["links"]:
        G.add_edge(link["source"], link["target"], title=f"{link['source_port']} -> {link['target_port']}")
    partition = mod_community_louvain.best_partition(G)
    net = Network(height="750px", width="100%", directed=False, notebook=True, bgcolor="#222222", font_color="white")
    cluster_colors = {cluster: f"#{''.join([format(int(c*255), '02x') for c in plt.cm.tab20(i % 20)[:3]])}"
                      for i, cluster in enumerate(set(partition.values()))}
    for node, cluster in partition.items():
        net.add_node(node, label=str(node), color=cluster_colors[cluster], title=f"Cluster: {cluster}")
    for link in data["links"]:
        net.add_edge(link["source"], link["target"], title=f"{link['source_port']} -> {link['target_port']}")
    net.show(output_html)


def parse_cable_log(file_path):
    nodes = {}
    edges = []
    switch_pattern = r'switchguid=0x([0-9a-f]+)'
    connection_pattern = r'\[(\d+)]\s+"([SH]-[0-9a-f]+)"\[(\d+)\]'

    with open(file_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    current_switch = None

    for line in lines:
        switch_match = re.search(switch_pattern, line)
        if switch_match:
            current_switch = switch_match.group(1)
            nodes[current_switch] = {"type": "switch", "guid": current_switch}
            continue

        connection_match = re.search(connection_pattern, line)
        if connection_match and current_switch:
            port, target, target_port = connection_match.groups()
            edges.append({
                "source": current_switch,
                "target": target,
                "source_port": port,
                "target_port": target_port
            })
            if target not in nodes:
                nodes[target] = {"type": "host" if target.startswith("H-") else "switch", "guid": target}

    return nodes, edges


def build_graph_json(nodes, edges, output_path):
    graph = {
        "directed": False,
        "multigraph": False,
        "nodes": [
            {"id": guid, "type": data["type"]} for guid, data in nodes.items()
        ],
        "links": [
            {"source": edge["source"], "target": edge["target"],
             "source_port": edge["source_port"], "target_port": edge["target_port"]}
            for edge in edges
        ]
    }

    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(graph, f, indent=4)


def main():
    input_file = "topo/mpi-net.txt"
    output_file = "supercomputer_topology.json"

    nodes, edges = parse_cable_log(input_file)
    build_graph_json(nodes, edges, output_file)
    print(f"Graph JSON saved to {output_file}")
    graph_path = "supercomputer_topology.json"
    output_html = "supercomputer_graph.html"

    visualize_3d_graph_with_clustering(graph_path, output_html)


if __name__ == "__main__":
    main()
