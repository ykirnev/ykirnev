import networkx as nx
import matplotlib.pyplot as plt
import random
import numpy as np

# Установка seed для воспроизводимости
random.seed(42)

# Создание гиперкуба
n_dim = 9  # Размерность гиперкуба (2^8 = 256 узлов)
G = nx.hypercube_graph(n_dim)

# Добавление параметров ребер
for u, v, data in G.edges(data=True):
    data['latency'] = random.uniform(1.0, 10.0)  # Задержка, мс
    data['reliability'] = random.uniform(0.5, 1.0)  # Надежность, 0–1
    data['load'] = random.uniform(0.1, 0.8)  # Загруженность, 0–1
    data['bandwidth'] = random.uniform(1.0, 10.0)  # Пропускная способность, Гбит/с
    data['cost'] = data['latency'] * random.uniform(0.5, 1.5)  # Стоимость, усл. ед.
    data['bandwidth_usage'] = data['load'] * data['bandwidth'] * random.uniform(0.5, 1.0)  # Использование полосы
    data['bandwidth_usage_ratio'] = data['bandwidth_usage'] / data['bandwidth']  # Доля использования

# Функция установки весов для стратегий
def set_edge_weights(G, strategy):
    for u, v, data in G.edges(data=True):
        if strategy == 'lowest_latency':
            data['weight'] = data.get('latency', 1.0)
        elif strategy == 'most_reliable':
            data['weight'] = 1.0 / data.get('reliability', 1.0)  # Инверсия, так как минимизируем
        elif strategy == 'cheapest':
            data['weight'] = data.get('cost', 1.0)
        elif strategy == 'least_loaded':
            data['weight'] = data.get('load', 1.0)
        elif strategy == 'min_bandwidth_usage':
            data['weight'] = data.get('bandwidth_usage_ratio', 1.0)

# Стратегии и цвета
strategies = ['lowest_latency', 'most_reliable', 'cheapest', 'least_loaded', 'min_bandwidth_usage', 'Dijkstra']
colors = {
    'lowest_latency': 'blue',
    'most_reliable': 'green',
    'cheapest': 'purple',
    'least_loaded': 'orange',
    'min_bandwidth_usage': 'red',
    'Dijkstra': 'black'
}

# Выбор случайной пары узлов
nodes = list(G.nodes)
origin_node, destination_node = random.choice(nodes), random.choice(nodes)
routes = {}

# Поиск маршрутов для каждой стратегии
for strategy in strategies:
    H = G.copy()
    if strategy != 'Dijkstra':
        set_edge_weights(H, strategy)
    else:
        for u, v, data in H.edges(data=True):
            data['weight'] = data.get('latency', 1.0)  # По умолчанию минимизируем задержку
    try:
        route = nx.shortest_path(H, origin_node, destination_node, weight='weight')
        routes[strategy] = route
    except nx.NetworkXNoPath:
        print(f"No path found for strategy {strategy}")
        continue

# Вывод метрик
print("\nMetrics for each strategy:")
for strategy, route in routes.items():
    latency = sum(G[u][v]['latency'] for u, v in zip(route[:-1], route[1:]))
    reliability = np.mean([G[u][v]['reliability'] for u, v in zip(route[:-1], route[1:])])
    bandwidth_usage_ratio = np.mean([G[u][v]['bandwidth_usage_ratio'] for u, v in zip(route[:-1], route[1:])])
    print(f"{strategy}: latency = {latency:.1f} ms, reliability = {reliability:.3f}, bandwidth_usage_ratio = {bandwidth_usage_ratio:.4f}")

# Визуализация отдельных маршрутов
fig, axes = plt.subplots(2, 3, figsize=(18, 12))
axes = axes.flatten()
pos = nx.spring_layout(G, seed=42)  # Фиксированная раскладка для согласованности

for i, strategy in enumerate(strategies):
    if strategy not in routes:
        continue
    route = routes[strategy]
    edge_colors = ['red' if (u, v) in zip(route[:-1], route[1:]) or (v, u) in zip(route[:-1], route[1:]) else 'gray' for u, v in G.edges()]
    nx.draw(G, pos, ax=axes[i], node_size=10, edge_color=edge_colors, node_color='lightblue')
    axes[i].set_title(f"Strategy: {strategy}", fontsize=12)

for j in range(len(routes), len(axes)):
    fig.delaxes(axes[j])

fig.tight_layout()
plt.savefig('hypercube_routes_subplots.png', dpi=300)
print("Сохранён файл: hypercube_routes_subplots.png")

# Общая визуализация всех маршрутов
fig_all, ax_all = plt.figure(figsize=(8, 8)), plt.gca()
nx.draw(G, pos, node_size=10, edge_color='gray', node_color='lightblue', ax=ax_all)
for strategy, route in routes.items():
    route_edges = [(u, v) for u, v in zip(route[:-1], route[1:])]
    nx.draw_networkx_edges(G, pos, edgelist=route_edges, edge_color=colors[strategy], width=2, ax=ax_all)
    ax_all.plot([], [], color=colors[strategy], label=strategy)
ax_all.legend(title="Strategies", loc="upper right")
plt.title("All strategies comparison on hypercube", fontsize=14)
plt.savefig('hypercube_routes_combined.png', dpi=300)
print("Сохранён файл: hypercube_routes_combined.png")