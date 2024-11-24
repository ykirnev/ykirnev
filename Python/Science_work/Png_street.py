import osmnx as ox
import matplotlib.pyplot as plt

G = ox.graph_from_place("Новокуйбышевск, Россия", network_type="drive")
fig, ax = plt.subplots(figsize=(20, 20))
ox.plot_graph(G, node_size=5, edge_linewidth=1, edge_color="black", ax=ax, show=False, close=False)
fig.savefig("roads_zoomed.png", dpi=300, bbox_inches="tight")
plt.close(fig)
