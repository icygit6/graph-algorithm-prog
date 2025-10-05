#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n +1);
    
    for (int i= 0; i <m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> color(n + 1, -1);
    

    for (int i = 1; i <=n; i++)
    {
        if (color[i] ==-1)
        {
            queue<int> q;
            q.push(i);
            color[i] = 0;
            while (!q.empty())
            {
                int curr = q.front();
                q.pop();
                for (int nei : graph[curr])
                {
                    if (color[nei] == -1)
                    {
                        color[nei] = 1 - color[curr];
                        q.push(nei);
                    }
                    else if (color[nei] == color[curr])
                    {
                        cout << "IMPOSSIBLE"<< endl;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "YES" << endl;
    return 0;
}