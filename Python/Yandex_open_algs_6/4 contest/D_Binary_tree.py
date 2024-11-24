class Node:
    def __init__(self, key, depth=0):
        self.key = key
        self.left = None
        self.right = None
        self.depth = depth

class BinarySearchTree:
    def __init__(self):
        self.root = None

    def add(self, key):
        if not self.root:
            self.root = Node(key)
            return "DONE"
        return self._add_recursive(self.root, key)

    def _add_recursive(self, node, key, depth=0):
        if key == node.key:
            return "ALREADY"
        if key < node.key:
            if node.left:
                return self._add_recursive(node.left, key, depth + 1)
            else:
                node.left = Node(key, depth + 1)
                return "DONE"
        else:
            if node.right:
                return self._add_recursive(node.right, key, depth + 1)
            else:
                node.right = Node(key, depth + 1)
                return "DONE"

    def search(self, key):
        return self._search_recursive(self.root, key)

    def _search_recursive(self, node, key):
        if not node:
            return "NO"
        if key == node.key:
            return "YES"
        if key < node.key:
            return self._search_recursive(node.left, key)
        else:
            return self._search_recursive(node.right, key)

    def print_tree(self):
        result = []
        self._print_tree_recursive(self.root, result)
        return "\n".join(result)

    def _print_tree_recursive(self, node, result):
        if not node:
            return
        self._print_tree_recursive(node.left, result)
        result.append("." * node.depth + str(node.key))
        self._print_tree_recursive(node.right, result)


tree = BinarySearchTree()
while True:
    try:
        query = input().strip()
        if not query:
            break
        if query.startswith("ADD"):
            _, key = query.split()
            print(tree.add(int(key)))
        elif query.startswith("SEARCH"):
            _, key = query.split()
            print(tree.search(int(key)))
        elif query == "PRINTTREE":
            print(tree.print_tree())
    except EOFError:
        break
