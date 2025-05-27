#include "PreflowPush.h"

PreflowPush::PreflowPush(int n, int s, int t, const vector<vector<int>>& capacity)
    : n(n), s(s), t(t), capacity(capacity),
    flow(n, vector<int>(n, 0)), height(n, 0), excess(n, 0), adj(n)
{
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (capacity[u][v] > 0 || capacity[v][u] > 0) {
                adj[u].push_back(v);
            }
        }
    }
}

void PreflowPush::initializePreflow()
{
    height[s] = n;
    excess[s] = INT_MAX;
    for (int v : adj[s])
    {
        flow[s][v] = capacity[s][v];
        flow[v][s] = -flow[s][v];
        excess[v] = flow[s][v];
        excess[s] -= flow[s][v];
    }
}

bool PreflowPush::push(int u)
{
    for (int v : adj[u])
    {
        if (excess[u] > 0 && capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1)
        {
            int delta = min(excess[u], capacity[u][v] - flow[u][v]);
            flow[u][v] += delta;
            flow[v][u] -= delta;
            excess[u] -= delta;
            excess[v] += delta;
            return true;
        }
    }
    return false;
}

void PreflowPush::relabel(int u)
{
	int min_height = INT_MAX;
	for (int v : adj[u])
		if (capacity[u][v] - flow[u][v] > 0)
			min_height = min(min_height, height[v]);
	if (min_height < INT_MAX)
		height[u] = min_height + 1;
}

int PreflowPush::maxFlow()
{
	initializePreflow();
	while (true)
	{
		bool pushed = false;
		bool relabeled = false;
		for (int u = 0; u < n; ++u)
		{
			if (u != s && u != t && excess[u] > 0)
			{
				if (push(u))
					pushed = true;
				else
				{
					relabel(u);
					relabeled = true;
				}
			}
		}
		if (!pushed && !relabeled)
			break;
	}
	return excess[t];
}