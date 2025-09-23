#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int parent[MAXN];
int dist[MAXN];
bool visit[MAXN];

int main() 
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    if (m == n - 1) 
    {
        cout << "There is no cycle." << endl;
        return 0;
    }
    queue<int> q;
    q.push(1);
    visit[1] = true;
    parent[1] = -1;
    dist[1] = 0;

    int cycleLength = -1;

    while (!q.empty() && cycleLength == -1) 
    {
        int u = q.front(); q.pop();

        for (int v : adj[u]) 
        {
            if (!visit[v]) 
            {
                visit[v] = true;
                parent[v] = u;
                dist[v] = dist[u] + 1;
                q.push(v);
            } 
            else if (v != parent[u]) 
            {
                cycleLength = dist[u] + dist[v] + 1;
                break;
            }
        }
    }

    if (cycleLength == -1) 
    {
        cout << "There is no cycle." << endl;
    } 
    else 
    {
        cout << cycleLength << endl;
    }
    return 0;
}
