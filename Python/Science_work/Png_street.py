import osmnx as ox
import matplotlib.pyplot as plt

region_name = "Центральный федеральный округ, Россия"
#G = ox.graph_from_place(region_name, network_type="drive")
G = ox.graph_from_place("Москва, Россия", network_type="drive")
fig, ax = plt.subplots(figsize=(20, 20))
ox.plot_graph(G, node_size=5, edge_linewidth=1, edge_color='white', ax=ax, show=False, close=False)
fig.savefig("roads_zoomed.png", dpi=300, bbox_inches="tight")
plt.close(fig)
