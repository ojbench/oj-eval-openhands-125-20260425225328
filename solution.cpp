
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

// Fast input function
inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

// Union-Find with coordinate compression
class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    std::unordered_map<int, int> comp; // Coordinate compression map
    int nextId;

public:
    UnionFind() : nextId(0) {
        // Start with reasonable capacity
        parent.reserve(2000000);
        rank.reserve(2000000);
    }

    // Compress coordinate and return compressed id
    int compress(int x) {
        auto it = comp.find(x);
        if (it != comp.end()) {
            return it->second;
        }
        
        int id = nextId++;
        comp[x] = id;
        
        // Ensure vectors are large enough
        if (id >= (int)parent.size()) {
            parent.resize(id + 1);
            rank.resize(id + 1);
        }
        
        parent[id] = id;
        rank[id] = 0;
        return id;
    }

    int find(int x) {
        int root = x;
        while (parent[root] != root) {
            root = parent[root];
        }
        
        // Path compression
        while (parent[x] != x) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        
        return root;
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int t = readInt();

    while (t--) {
        int n = readInt();

        UnionFind uf;
        std::vector<std::pair<int, int>> inequalities;
        inequalities.reserve(n);

        // Process all constraints
        for (int i = 0; i < n; i++) {
            int a = readInt();
            int b = readInt();
            int e = readInt();

            // Compress coordinates
            int ca = uf.compress(a);
            int cb = uf.compress(b);

            if (e == 1) {
                // Equality constraint: a == b
                uf.unite(ca, cb);
            } else {
                // Inequality constraint: a != b
                inequalities.push_back({ca, cb});
            }
        }

        // Check if any inequality constraint is violated
        bool valid = true;
        for (const auto& p : inequalities) {
            if (uf.connected(p.first, p.second)) {
                valid = false;
                break;
            }
        }

        if (valid) {
            putchar('Y');
            putchar('E');
            putchar('S');
        } else {
            putchar('N');
            putchar('O');
        }
        putchar('\n');
    }

    return 0;
}
