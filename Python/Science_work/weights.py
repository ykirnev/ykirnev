import osmnx as ox
import networkx as nx
import matplotlib.pyplot as plt
import random
import numpy as np

ox.config(log_console=True, use_cache=True)
place_name = "Moscow, Russia"
G = ox.graph_from_place(place_name, network_type="drive")
G = ox.project_graph(G)
G_simplified = G

random.seed(42)
for u, v, k, data in G_simplified.edges(keys=True, data=True):
    data['safety_score'] = random.uniform(0.1, 1.0)
    data['traffic'] = random.uniform(0.1, 1.0)
    data['cost'] = data.get('length', 1) * random.uniform(0.5, 1.5)
    data['capacity'] = random.uniform(1.0, 10.0)
    data['usage'] = data['traffic'] * data['length'] / 100
    data['capacity_usage'] = data['usage'] / data['capacity']

def set_edge_weights(G, strategy):
    for u, v, k, data in G.edges(keys=True, data=True):
        if strategy == 'fastest':
            data['weight'] = data.get('length', 1)
        elif strategy == 'safest':
            data['weight'] = data.get('safety_score', 1)
        elif strategy == 'cheapest':
            data['weight'] = data.get('cost', 1)
        elif strategy == 'least_traffic':
            data['weight'] = data.get('traffic', 1)
        elif strategy == 'capacity_usage':
            data['weight'] = data.get('capacity_usage', 1)

strategies = ['fastest', 'safest', 'cheapest', 'least_traffic', 'capacity_usage', 'Dijkstra']
colors = {
    'fastest': 'blue',
    'safest': 'green',
    'cheapest': 'purple',
    'least_traffic': 'orange',
    'capacity_usage': 'red',
    'Dijkstra': 'black'
}

nodes = list(G_simplified.nodes)
pairs = [(random.choice(nodes), random.choice(nodes)) for _ in range(1)]
origin_node, destination_node = pairs[0]
routes = {}
for strategy in strategies:
    H = G_simplified.copy()

    if strategy != 'Dijkstra':
        set_edge_weights(H, strategy)
    else:
        for u, v, k, data in H.edges(keys=True, data=True):
            data['weight'] = data.get('length', 1)

    try:
        route = nx.shortest_path(H, origin_node, destination_node, weight='weight')
        routes[strategy] = route
    except nx.NetworkXNoPath:
        print(f"No path found for strategy {strategy}")
        continue

print("\nMetrics for each strategy:")
for strategy, route in routes.items():
    length = sum(G_simplified[u][v][0]['length'] for u, v in zip(route[:-1], route[1:]))
    safety = np.mean([G_simplified[u][v][0]['safety_score'] for u, v in zip(route[:-1], route[1:])])
    capacity_usage = np.mean([G_simplified[u][v][0]['capacity_usage'] for u, v in zip(route[:-1], route[1:])])
    print(f"{strategy}: length = {length:.1f}, safety = {safety:.3f}, capacity_usage = {capacity_usage:.4f}")


fig, axes = plt.subplots(2, 3, figsize=(18, 12))
axes = axes.flatten()

for i, strategy in enumerate(strategies):
    if strategy not in routes:
        continue
    route = routes[strategy]
    _, ax = ox.plot_graph_route(
        G,
        route,
        route_color=colors[strategy],
        route_linewidth=3,
        node_size=0,
        ax=axes[i],
        show=False,
        close=False
    )
    axes[i].set_title(f"Strategy: {strategy}", fontsize=12)

for j in range(len(routes), len(axes)):
    fig.delaxes(axes[j])

fig.tight_layout()
fig.savefig("routing_strategies_subplots.png", dpi=300)
print("Сохранён файл: routing_strategies_subplots.png")

# Общая визуализация всех маршрутов
fig_all, ax_all = ox.plot_graph_routes(
    G,
    list(routes.values()),
    route_colors=[colors[strategy] for strategy in routes],
    route_linewidth=3,
    node_size=0,
    show=False,
    close=False
)
for strategy in routes:
    ax_all.plot([], [], color=colors[strategy], label=strategy)
ax_all.legend(title="Strategies", loc="upper right")
plt.title("All strategies comparison", fontsize=14)
fig_all.figure.savefig("routing_strategies_combined.png", dpi=300)
print("Сохранён файл: routing_strategies_combined.png")
