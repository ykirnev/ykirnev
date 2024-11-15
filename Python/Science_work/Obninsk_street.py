import osmnx as ox
import matplotlib.pyplot as plt

# Загружаем граф дорог Обнинска с данными для автомобильных дорог
G = ox.graph_from_place("Obninsk, Russia", network_type="drive")

# Настраиваем параметры для увеличенного масштаба
fig, ax = plt.subplots(figsize=(20, 20))  # Увеличиваем размер изображения
ox.plot_graph(G, node_size=5, edge_linewidth=1, edge_color="black", ax=ax, show=False, close=False)

# Сохраняем увеличенный график в файл с высоким разрешением
fig.savefig("obninsk_roads_zoomed.png", dpi=300, bbox_inches="tight")
plt.close(fig)  # Закрываем фигуру для освобождения памяти

print("Увеличенная карта дорог Обнинска сохранена в файл 'obninsk_roads_zoomed.png'")