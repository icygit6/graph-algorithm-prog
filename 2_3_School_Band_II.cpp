#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> parent, sz, parity;
    vector<tuple<int, int, int, int>> history;
    bool ok;

    DSU(int n)
    {
        parent.resize(n);
        sz.assign(n, 1);
        parity.assign(n, 0);
        ok = true;
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    pair<int, int> find(int x)
    {
        int p = 0;
        if (parent[x] == x)
        {
            return {x, 0};
        }
        auto res = find(parent[x]);
        res.second ^= parity[x];
        return {res.first, res.second};
    }

    void unite(int a, int b)
    {
        auto pa = find(a);
        auto pb = find(b);
        int ra = pa.first;
        int rb = pb.first;
        int xa = pa.second;
        int xb = pb.second;

        if (ra == rb)
        {
            if ((xa ^ xb) != 1)
            {
                ok = false;
            }
            history.push_back({-1, -1, -1, -1});
            return;
        }

        if (sz[ra] < sz[rb])
        {
            swap(ra, rb);
            swap(xa, xb);
        }

        history.push_back({rb, parent[rb], parity[rb], sz[ra]});
        parent[rb] = ra;
        parity[rb] = xa ^ xb ^ 1;
        sz[ra] += sz[rb];
    }

    int snapshot()
    {
        return (int)history.size();
    }

    void rollback(int snap)
    {
        while ((int)history.size() > snap)
        {
            auto [rb, oldpar, oldparity, oldsize] = history.back();
            history.pop_back();
            if (rb == -1)
            {
                continue;
            }
            int ra = parent[rb];
            parent[rb] = oldpar;
            parity[rb] = oldparity;
            sz[ra] = oldsize;
        }
        ok = true;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> basepair(m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        basepair[i] = {a, b};
    }

    int p, k;
    cin >> p >> k;

    vector<vector<pair<int, int>>> report(p);
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int a, b;
            cin >> a >> b;
            report[i].push_back({a, b});
        }
    }

    DSU dsu(n);

    for (auto &pr : basepair)
    {
        dsu.unite(pr.first, pr.second);
        if (!dsu.ok)
        {
            // principal data guaranteed valid, so this shouldn't happen
            cout << "ERROR\n";
            return 0;
        }
    }

    vector<int> liar;

    for (int i = 0; i < p; i++)
    {
        int snap = dsu.snapshot();

        for (auto &pr : report[i])
        {
            dsu.unite(pr.first, pr.second);
            if (!dsu.ok)
            {
                liar.push_back(i + 1);
                break;
            }
        }

        dsu.rollback(snap);
    }

    for (int x : liar)
    {
        cout << x << "\n";
    }

    return 0;
}
