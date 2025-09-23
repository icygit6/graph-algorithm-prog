#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;

struct StateHash 
{
    size_t operator()(const array<int, 6>& state) const 
    {
        size_t hash = 0;
        for (int i = 0; i < 6; i++) 
        {
            hash = hash * 31 + state[i];
        }
        return hash;
    }
};

int main() 
{
    int t,k;
    cin >> t >> k;
    vector<int> cap(6);
    for (int i = 0; i < 6; i++) 
    {
        cin >> cap[i];
    }
    int totalCap = 0;
    for (int i = 0; i < 6; i++) 
    {
        totalCap +=cap[i];
    }
    if (t >totalCap) 
    {
        cout << "False\n";
        return 0;
    }
    queue<pair<array<int, 6>, int>> q;
    unordered_map<array<int, 6>, int, StateHash> visit;

    array<int, 6> start = {0, 0, 0, 0, 0, 0};
    q.push({start, 0});
    visit[start] = 0;
    
    bool found = false;
    
    while (!q.empty()) 
    {
        auto [state, ops] = q.front();
        q.pop();
        int total = 0;
        for (int i = 0; i < 6; i++)
        {
            total += state[i];
        }
        if (total == t) 
        {
            found = true;
            break;
        }
        
        if (ops >= k) 
        {
            continue;
        }
        for (int i = 0; i < 6; i++) 
        {
            if (state[i] < cap[i]) 
            {
                array<int, 6> ns = state;
                ns[i] = cap[i];
                if (visit.find(ns) == visit.end() || visit[ns] > ops + 1) 
                {
                    visit[ns] = ops + 1;
                    q.push({ns, ops + 1});
                }
            }
        }
        for (int i = 0; i < 6; i++) 
        {
            if (state[i] > 0) 
            {
                array<int, 6> ns = state;
                ns[i] = 0;
                if (visit.find(ns) == visit.end() || visit[ns] > ops + 1) 
                {
                    visit[ns] = ops + 1;
                    q.push({ns, ops + 1});
                }
            }
        }
        for (int i = 0; i < 6; i++) 
        {
            for (int j = 0; j < 6; j++) 
            {
                if (i != j && state[i] > 0 && state[j] < cap[j]) 
                {
                    array<int, 6> ns = state;
                    int pour = min(state[i], cap[j] - state[j]);
                    ns[i] -= pour;
                    ns[j] += pour;
                    if (visit.find(ns) == visit.end() || visit[ns] > ops + 1) 
                    {
                        visit[ns] = ops + 1;
                        q.push({ns, ops + 1});
                    }
                }
            }
        }
    }
    
    if (found) 
    {
        cout << "True\n";
    } 
    else 
    {
        cout << "False\n";
    }
    return 0;
}