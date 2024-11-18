import osmnx as ox
import json
from networkx.readwrite import json_graph
from shapely.geometry import LineString

def serialize_geometry(data):
    for edge in data['links']:
        if 'geometry' in edge and isinstance(edge['geometry'], LineString):
            edge['geometry'] = list(edge['geometry'].coords)
    return data

city = "Sochi, Russia"
try:
    graph = ox.graph_from_place(city, network_type="drive")
    #graph = ox.graph_from_place("Russia", network_type="drive", custom_filter='["highway"]')
    graph_data = json_graph.node_link_data(graph)
    graph_data = serialize_geometry(graph_data)
    with open("roads.json", "w") as f:
        json.dump(graph_data, f, ensure_ascii=False, indent=4)

except Exception as e:
    print(f"Ошибка: {e}")
