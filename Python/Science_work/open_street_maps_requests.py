import osmnx as ox
import matplotlib as plt
G = ox.graph_from_place("Moscow, Russia", network_type="drive")
ox.save_graphml(G, filepath="moscow_roads.graphml")
print("Граф дорог Москвы успешно сохранен!")
fig, ax = ox.plot_graph(G, node_size=5, edge_linewidth=0.5)
fig.savefig("moscow_roads.png", dpi=300, bbox_inches="tight")
plt.close(fig)
print("График сохранен в файл 'moscow_roads.png'")
edge_classes = {}
for u, v, key, data in G.edges(keys=True, data=True):
    highway_type = data.get("highway", None)
    if highway_type:

        if highway_type not in edge_classes:
            edge_classes[highway_type] = []
        edge_classes[highway_type].append((u, v))

print("Типы дорог:", edge_classes.keys())
primary_roads = [(u, v) for u, v, data in G.edges(data=True) if data.get("highway") == "primary"]
secondary_roads = [(u, v) for u, v, data in G.edges(data=True) if data.get("highway") == "secondary"]
primary_subgraph = G.edge_subgraph(primary_roads)
secondary_subgraph = G.edge_subgraph(secondary_roads)