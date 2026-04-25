
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class UnionFind {
private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

public:
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
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
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        UnionFind uf;
        std::vector<std::pair<int, int>> inequalities;

        // Process all constraints
        for (int i = 0; i < n; i++) {
            int a, b, e;
            std::cin >> a >> b >> e;

            if (e == 1) {
                // Equality constraint: a == b
                uf.unite(a, b);
            } else {
                // Inequality constraint: a != b
                inequalities.push_back({a, b});
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

        std::cout << (valid ? "YES" : "NO") << '\n';
    }

    return 0;
}
