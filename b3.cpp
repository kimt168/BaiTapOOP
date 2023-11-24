#include <bits/stdc++.h>

using namespace std;

class Query {
private:
    int u, v;

public:
    Query(int uu, int vv) : u(uu), v(vv) {}
    int getU() const {
        return u;
    }
    int getV() const {
        return v;
    }
};

class Update {
private:
    int u, v, k;

public:
    Update(int uu, int vv, int kk) : u(uu), v(vv), k(kk) {}
    int getU() const {
        return u;
    }
    int getV() const {
        return v;
    }
    int getK() const {
        return k;
    }
};

class ArrayUpdater {
private:
    vector<int> arr;
    vector<int> tree;

public:
    ArrayUpdater(int n) : arr(n, 0), tree(4 * n, 0) {}

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            arr[idx] += val;
            tree[node] += val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = query(2 * node, start, mid, l, r);
        int p2 = query(2 * node + 1, mid + 1, end, l, r);
        return max(p1, p2);
    }

    void applyUpdate(const Update &update) {
        update(1, 0, arr.size() - 1, update.getU() - 1, update.getK());
        if (update.getV() < arr.size()) {
            update(1, 0, arr.size() - 1, update.getV(), -update.getK());
        }
    }

    void buildSegmentTree() {
        build(1, 0, arr.size() - 1);
    }

    int getMaxValueInRange(int u, int v) const {
        return query(1, 0, arr.size() - 1, u - 1, v - 1);
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    ArrayUpdater arrayUpdater(n);

    for (int i = 0; i < m; ++i) {
        int u, v, k;
        cin >> u >> v >> k;
        Update update(u, v, k);
        arrayUpdater.applyUpdate(update);
    }

    arrayUpdater.buildSegmentTree();

    int p;
    cin >> p;

    for (int i = 0; i < p; ++i) {
        int u, v;
        cin >> u >> v;
        Query query(u, v);
        cout << arrayUpdater.getMaxValueInRange(query.getU(), query.getV()) << endl;
    }

    return 0;
}