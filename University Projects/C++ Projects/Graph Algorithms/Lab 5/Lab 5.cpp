#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include "PreflowPush.h"

using namespace std;

bool BFS(vector<vector<int>>& mat_ad, int source, int destination, vector<int>& parent, int V)
{
	vector<bool> visited(V, false);
	queue<int> queue;
	queue.push(source);
	visited[source] = true;

	while (!queue.empty())
	{
		int u = queue.front();
		queue.pop();
		for (int v = 0; v < V; v++)
		{
			if (!visited[v] && mat_ad[u][v] > 0)
			{
				queue.push(v);
				visited[v] = true;
				parent[v] = u;
				if (v == destination)
					return true;
			}
		}
	}
	return false;
}

int EdmondsKarp(vector<vector<int>>& mat_ad, int source, int destination, int V)
{
	vector<int> parent(V);
	int max_flow = 0;
	while (BFS(mat_ad, source, destination, parent, V))
	{
		int path_flow = INT_MAX;
		for (int v = destination; v != source; v = parent[v])
		{
			int u = parent[v];
			path_flow = min(path_flow, mat_ad[u][v]);
		}
		for (int v = destination; v != source; v = parent[v])
		{
			int u = parent[v];
			mat_ad[u][v] -= path_flow;
			mat_ad[v][u] += path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;
}

void Euler(vector<vector<int>>& mat_ad, int source, int V, vector<int>& ciclu)
{
	for (int i = 0; i < V; i++)
		if (mat_ad[source][i] == 1)
		{
			mat_ad[source][i] = mat_ad[i][source] = 0;
			Euler(mat_ad, i, V, ciclu);
		}
	ciclu.push_back(source);
}

int main(int argc, char** argv)
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

	//ifstream fin("input.txt");
	//ofstream fout("output.txt");


	// 1. Flux maxim (Edmons-Karp)
    int V, E;
    fin >> V >> E;

    vector<vector<int>> mat_ad(V);
	for (int i = 0; i < V; i++)
		mat_ad[i].resize(V, 0);

    for (int i = 0; i < E; i++)
    {
        int x, y, c;
        fin >> x >> y >> c;
        mat_ad[x][y] = c;
    }

	int source = 0, destination = V - 1;
	int max_flow = EdmondsKarp(mat_ad, source, destination, V);
	fout << max_flow << endl;

	// 2. Flux maxim (pompare preflux)
    fin.clear();
    fin.seekg(0);

	fin >> V >> E;
    for (int i = 0; i < V; i++)
        mat_ad[i].assign(V, 0);

    for (int i = 0; i < E; i++)
    {
        int x, y, c;
        fin >> x >> y >> c;
        mat_ad[x][y] = c;
    }

	PreflowPush pomparePreflux(V, source, destination, mat_ad);
	int max_flow_preflux = pomparePreflux.maxFlow();
    fout << max_flow_preflux << endl;

	// 3. Ciclu eulerian
	fin.clear();
	fin.seekg(0);

	fin >> V >> E;
	for (int i = 0; i < V; i++)
		mat_ad[i].assign(V, 0);

	for (int i = 0; i < E; i++)
	{
		int x, y, c;
		fin >> x >> y >> c;
		mat_ad[x][y] = 1;
		mat_ad[y][x] = 1;
	}

	vector<int> ciclu;
	Euler(mat_ad, 0, V, ciclu);
	for (auto nod : ciclu)
		fout << nod << " ";
}
