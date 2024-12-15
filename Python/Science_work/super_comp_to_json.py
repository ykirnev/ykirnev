import json
import re
from datetime import datetime

def parse_cable_log(file_content):
    nodes = {}
    edges = []
    current_switch = None

    for line in file_content.splitlines():
        switch_match = re.match(r"switchguid=0x([0-9a-f]+)", line, re.IGNORECASE)
        if switch_match:
            switch_id = switch_match.group(1)
            current_switch = switch_id
            nodes[switch_id] = {"id": switch_id, "type": "switch"}
            continue

        connection_match = re.match(r"\[\d+\]\s+\"([^\"]+)\"\[(\d+)\]\(([^)]+)\)", line, re.IGNORECASE)
        if connection_match and current_switch:
            target_name, target_port, target_guid = connection_match.groups()
            target_id = target_guid.lower()
            node_type = "hca" if target_name.startswith("H-") else "switch"
            if target_id not in nodes:
                nodes[target_id] = {"id": target_id, "type": node_type}
            edges.append({
                "source": current_switch,
                "target": target_id,
                "port": target_port
            })

    return {"nodes": list(nodes.values()), "edges": edges}

with open("topo/stor.txt", "r") as file:
    content = file.read()

graph_data = parse_cable_log(content)

graph = {
    "directed": False,
    "multigraph": False,
    "graph": {
        "created_date": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        "description": "Supercomputer topology graph"
    },
    "nodes": graph_data["nodes"],
    "edges": graph_data["edges"]
}

with open("supercomputer_topology.json", "w") as outfile:
    json.dump(graph, outfile, indent=4)
