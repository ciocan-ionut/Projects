#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int INFINIT = INT_MAX;

// Returneaza nodul cu distanta cea mai mica
int Distanta_Minima(const vector<int>& dist, const vector<bool>& vizitat) {
    int min = INFINIT, min_index = 0;
    for (int v = 0; v < dist.size(); ++v) {
        if (!vizitat[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Algoritmul lui Dijkstra
void Dijkstra1(const vector<vector<int>>& graf, const vector<vector<int>>& altered_graf, int source, ofstream& fout)
{
    int V = (int)graf.size();
    vector<int> dist(V, INFINIT);
    vector<bool> vizitat(V, false);

    dist[source] = 0;

    for (int count = 0; count < V - 1; ++count)
    {
        int u = Distanta_Minima(dist, vizitat);
        vizitat[u] = true;

        for (int v = 0; v < V; ++v)
        {
            if (!vizitat[v] && graf[u][v] != 0 && dist[u] != INFINIT && dist[u] + altered_graf[u][v] < dist[v])
                dist[v] = dist[u] + altered_graf[u][v];
        }
    }
    
    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INFINIT)
            fout << "INF ";
        else
            fout << dist[i] << ' ';
    }
}

void Dijkstra2(const vector<vector<int>>& graf, const vector<vector<int>>& altered_graf, vector<int>& altered_weights, int source, ofstream& fout, vector<vector<int>>& dist)
{
    int V = (int)graf.size();
    vector<int> local_dist(V, INFINIT);
    vector<bool> vizitat(V, false);

    local_dist[source] = 0;

    for (int count = 0; count < V - 1; ++count)
    {
        int u = Distanta_Minima(local_dist, vizitat);
        vizitat[u] = true;

        for (int v = 0; v < V; ++v)
        {
            if (!vizitat[v] && graf[u][v] != 0 && local_dist[u] != INFINIT && local_dist[u] + altered_graf[u][v] < local_dist[v])
                local_dist[v] = local_dist[u] + altered_graf[u][v];
        }
    }

    for (int i = 0; i < V; i++)
    {
        if (local_dist[i] != INFINIT)
            dist[source][i] = local_dist[i] - altered_weights[source] + altered_weights[i];
        else
            dist[source][i] = INFINIT;
    }
}

// Algoritmul lui Bellman - Ford
vector<int> BellmanFord(const vector<vector<int>>& edges, int V) {
    vector<int> dist(V + 1, INFINIT);
    dist[V] = 0;

    vector<vector<int>> edges_with_extra(edges);
    for (int i = 0; i < V; ++i)
        edges_with_extra.push_back({ V, i, 0 });

    for (int i = 0; i < V; ++i)
        for (const auto& edge : edges_with_extra)
            if (dist[edge[0]] != INFINIT && dist[edge[0]] + edge[2] < dist[edge[1]])
                dist[edge[1]] = dist[edge[0]] + edge[2];

    for (const auto& edge : edges_with_extra)
        if (dist[edge[0]] != INFINIT && dist[edge[0]] + edge[2] < dist[edge[1]])
            return {};

    return vector<int>(dist.begin(), dist.begin() + V);
}

// Algoritmul lui Johnson
void Johnson(const vector<vector<int>>& graph, ofstream& fout) 
{
    int V = (int)graph.size();
    vector<vector<int>> edges;

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (graph[i][j] != 0)
                edges.push_back({ i, j, graph[i][j] });

    vector<int> altered_weights = BellmanFord(edges, V);
    vector<vector<int>> altered_graph(V, vector<int>(V, 0));

    if (altered_weights.empty())
    {
        fout << "-1";
        return;
    }

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (graph[i][j] != 0)
                altered_graph[i][j] = graph[i][j] + altered_weights[i] - altered_weights[j];

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (graph[i][j] != 0)
                fout << i << ' ' << j << ' ' << altered_graph[i][j] << endl;

    vector<vector<int>> dist(V, vector<int>(V, 0));
    for (int source = 0; source < V; ++source)
        Dijkstra2(graph, altered_graph, altered_weights, source, fout, dist);
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            if (dist[i][j] == INFINIT)
                fout << "INF ";
            else
                fout << dist[i][j] << ' ';
        fout << endl;
    }
}

int main(int argc, char* argv[])
{
    //Problema 1
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	int V, E, S;
	fin >> V >> E >> S;

    vector<vector<int>> graf(V, vector<int>(V));

    for (int i = 0; i < E; i++) 
    {
        int x, y, w;
        fin >> x >> y >> w;
        graf[x][y] = w;
    }

    Dijkstra1(graf, graf, S, fout);  

    fin.close();
    fout.close();

    //Problema 2
    ifstream fi(argv[3]);
    ofstream fo(argv[4]);

    fi >> V >> E;

    vector<vector<int>> graf2(V, vector<int>(V));

    for (int i = 0; i < E; i++)
    {
        int x, y, w;
        fi >> x >> y >> w;
        graf2[x][y] = w;
    }

    Johnson(graf2, fo);

	fi.close();
	fo.close();
	return 0;
}