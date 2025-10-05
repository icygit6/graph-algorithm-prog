#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int bfs(int start, int tar, const vector<vector<int>>& graph)
{
    int n = graph.size();
    vector<int> dist(n, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        if (curr == tar)
        {
            return dist[curr];
        }
        for (int nei : graph[curr])
        {
            if (dist[nei] == -1)
            {
                dist[nei] = dist[curr] + 1;
                q.push(nei);
            }
        }
    }
    return -1;
}

int main()
{
    int n,m;
    cin >> n >> m;
    int u,v;
    cin >> u >>v;
    vector<vector<int>> graph(n);
    for (int i = 0; i <m; i++)
    {
        int a,b;
        cin >> a>> b;
        graph[a].push_back(b);
    }
    int duv = bfs(u, v, graph);
    int dvu = bfs(v, u, graph);
    
    if (duv == -1 || dvu == -1)
    {
        cout << -1 <<endl;
    }
    else
    {
        cout << duv + dvu << endl;
    }
    return 0;
}