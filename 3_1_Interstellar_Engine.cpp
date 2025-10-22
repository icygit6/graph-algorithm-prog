#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to;
    int w;
};

struct State
{
    long long time;
    int planet;
    int eff;
    bool operator>(const State &other) const
    {
        return time > other.time;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    const long long inf = 1e18;
    vector<vector<long long>> dist(n + 1, vector<long long>(1001, inf));
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[1][s[1]] = 0;
    pq.push({0, 1, s[1]});
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();

        long long t = cur.time;
        int u = cur.planet;
        int eff = cur.eff;
        if (t != dist[u][eff])
        {
            continue;
        }
        if (u == n)
        {
            cout << t << "\n";
            return 0;
        }
        int neweff = min(eff, s[u]);
        if (neweff < eff && t < dist[u][neweff])
        {
            dist[u][neweff] = t;
            pq.push({t, u, neweff});
        }
        for (auto &e : g[u])
        {
            long long nt = t + 1LL * e.w * eff;
            if (nt < dist[e.to][eff])
            {
                dist[e.to][eff] = nt;
                pq.push({nt, e.to, eff});
            }
        }
    }
    return 0;
}