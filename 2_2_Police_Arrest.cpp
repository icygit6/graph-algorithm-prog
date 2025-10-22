#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> parent, sz;
    vector<long long> mx;

    DSU(int n, const vector<long long> &a)
    {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        mx = a;
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] == x)return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        mx[a] = max(mx[a], mx[b]);
    }

    long long getMax(int x)
    {
        return mx[find(x)];
    }
};

struct query
{
    int type;
    int u, v, c;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    vector<pair<int, int>> edges(m + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> edges[i].first >> edges[i].second;
    }

    vector<query> que(q);
    set<pair<int, int>> cutEdges;

    for (int i = 0; i < q; i++)
    {
        cin >> que[i].type;
        if (que[i].type == 1)
        {
            cin >> que[i].u >> que[i].v;
            if (que[i].u > que[i].v)
                swap(que[i].u, que[i].v);
            cutEdges.insert({que[i].u, que[i].v});
        }
        else
        {
            cin >> que[i].c;
        }
    }

    DSU dsu(n, a);
    for (int i = 1; i <= m; i++)
    {
        auto e = edges[i];
        int u = e.first, v = e.second;
        if (u > v)
            swap(u, v);
        if (!cutEdges.count({u, v}))
        {
            dsu.unite(u, v);
        }
    }

    vector<long long> ans;
    for (int i = q - 1; i >= 0; i--)
    {
        if (que[i].type == 2)
        {
            ans.push_back(dsu.getMax(que[i].c));
        }
        else
        {
            int u = que[i].u, v = que[i].v;
            if (u > v)
                swap(u, v);
            dsu.unite(u, v);
        }
    }

    reverse(ans.begin(), ans.end());

    for (auto x : ans)
    {
        cout << x << "\n";
    }

    return 0;
}
