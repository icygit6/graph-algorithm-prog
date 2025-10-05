#include <iostream>
#include <vector>
using namespace std;
const int n = 1000;
const int MAX = n * n;
vector<int> parent(MAX);
vector<int> rankv(MAX, 0);
vector<bool> land(MAX, false);
int fr(int x)
{
    if (parent[x] == x)
    {
        return x;
    }
    return parent[x] = fr(parent[x]);
}

void unite(int a, int b)
{
    a = fr(a);
    b = fr(b);
    if (a == b)
    {
        return;
    }

    if (rankv[a] < rankv[b])
    {
        parent[a] = b;
    }
    else if (rankv[a] > rankv[b])
    {
        parent[b] = a;
    }
    else
    {
        parent[b] = a;
        rankv[a]++;
    }
}
int id(int x, int y)
{
    return (x - 1) * n + (y - 1);
}

int main()
{
    int q;
    cin >> q;
    for (int i = 0; i < MAX; i++)
    {
        parent[i] = i;
    }
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int x, y;
            cin >> x >> y;
            int id1 = id(x, y);
            land[id1] = true;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= n)
                {
                    int id2 = id(nx, ny);
                    if (land[id2])
                    {
                        unite(id1, id2);
                    }
                }
            }
        }
        else if (type == 2)
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;

            int idA = id(a, b);
            int idC = id(c, d);

            if (!land[idA] || !land[idC])
            {
                cout << "No" << endl;
            }
            else if (fr(idA) == fr(idC))
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}
