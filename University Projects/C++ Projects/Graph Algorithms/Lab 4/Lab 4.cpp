#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Codarea si decodarea Pruefer
vector<vector<int>> list_ad;

vector<int> pruefer_code()
{
	int n = (int)list_ad.size();
	set<int> leafs;
	vector<int> degree(n);
	vector<bool> killed(n, false);

	for (int i = 0; i < n; i++)
	{
		degree[i] = (int)list_ad[i].size();
		if (degree[i] == 1)
			leafs.insert(i);
	}

	vector<int> code(n - 2);
	for (int i = 0; i < n - 2; i++)
	{
		int leaf = *leafs.begin();
		leafs.erase(leaf);
		killed[leaf] = true;

		int v;
		for (int u : list_ad[leaf]) 
		{
			if (!killed[u])
				v = u;
		}

		code[i] = v;
		if (--degree[v] == 1)
			leafs.insert(v);
	}
	return code;
}

vector<pair<int, int>> pruefer_decode(vector<int> const& code)
{
	int n = (int)code.size() + 2;
	vector<int> degree(n, 1);
	for(int i : code)
		degree[i]++;

	set<int> leafs;
	for (int i = 0; i < n; i++) 
		if (degree[i] == 1)
			leafs.insert(i);

	vector<pair<int, int>> edges;
	for (int v : code)
	{
		int leaf = *leafs.begin();
		leafs.erase(leafs.begin());

		edges.push_back({ leaf, v });
		if (--degree[v] == 1)
			leafs.insert(v);
	}
	edges.push_back({ *leafs.begin(), n-1 });

	return edges;
}

vector<int> build_parent_list(int n, const vector<pair<int, int>>& edges, int root) {

	vector<vector<int>> adj(n);
	for (auto& e : edges) {
		int u = e.first, v = e.second;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<int> parent(n, -1), visited(n, 0);
	queue<int> q;

	q.push(root);
	visited[root] = 1;
	parent[root] = -1;

	while (!q.empty()) 
	{
		int u = q.front(); q.pop();
		for (int v : adj[u])
			if (!visited[v]) 
			{
				visited[v] = 1;
				parent[v] = u;
				q.push(v);
			}
	}

	return parent;
}

// Codarea si decodarea Huffman
struct HuffmanNode 
{
	char ch;
	int freq;
	HuffmanNode* left;
	HuffmanNode* right;

	HuffmanNode(char ch, int freq, HuffmanNode* left = nullptr, HuffmanNode* right = nullptr)
		: ch(ch), freq(freq), left(left), right(right) {}
};

struct Compare 
{
	bool operator()(HuffmanNode* a, HuffmanNode* b)
	{
		return a->freq > b->freq;
	}
};

void buildCodes(HuffmanNode* root, const string& str, unordered_map<char, string>& huffmanCodes) 
{
	if (!root) 
		return;

	if (!root->left && !root->right)
		huffmanCodes[root->ch] = str;

	buildCodes(root->left, str + "0", huffmanCodes);
	buildCodes(root->right, str + "1", huffmanCodes);
}

void freeTree(HuffmanNode* root) 
{
	if (!root) 
		return;
	freeTree(root->left);
	freeTree(root->right);
	delete root;
}

string encode(const string& text, unordered_map<char, string>& huffmanCodes) 
{
	string encodedStr;
	for (char ch : text)
		encodedStr += huffmanCodes[ch];
	return encodedStr;
}

string decode(const string& encodedStr, HuffmanNode* root) 
{
	string decodedStr;
	HuffmanNode* current = root;
	for (char bit : encodedStr) {
		if (bit == '0')
			current = current->left;
		else
			current = current->right;

		if (!current->left && !current->right) 
		{
			decodedStr += current->ch;
			current = root;
		}
	}
	return decodedStr;
}

// Arbore minim de acoperire
class DSU
{
	vector<int> parent, rank;

public:
	DSU(int n) 
	{
		parent.resize(n);
		rank.resize(n);
		for (int i = 0; i < n; i++) 
		{
			parent[i] = i;
			rank[i] = 1;
		}
	}

	int find(int i) 
	{
		return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
	}

	void unite(int x, int y) 
	{
		int s1 = find(x), s2 = find(y);
		if (s1 != s2)
			if (rank[s1] < rank[s2]) 
				parent[s1] = s2;
			else if (rank[s1] > rank[s2]) 
				parent[s2] = s1;
			else 
				parent[s2] = s1, rank[s1]++;
	}
};

bool comparator(vector<int>& a, vector<int>& b) 
{
	if (a[2] < b[2])
		return true;
	return false;
}

pair<int, vector<pair<int, int>>> kruskalsMST(int V, vector<vector<int>>& edges)
{
	sort(edges.begin(), edges.end(), comparator);
	DSU dsu(V);
	int cost = 0, count = 0;
	vector<pair<int, int>> mstEdges;

	for (auto& e : edges) 
	{
		int x = e[0], y = e[1], w = e[2];
		if (dsu.find(x) != dsu.find(y)) 
		{
			dsu.unite(x, y);
			cost += w;
			mstEdges.push_back({ x, y });
			if (++count == V - 1) 
				break;
		}
	}
	return { cost, mstEdges };
}

int main(int argc, char* argv[])
{
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	// Codarea si decodarea Pruefer
	/*int n, root = 0;
	fin >> n;
	list_ad.resize(n);
	for (int i = 0; i < n; i++)
	{
		int v;
		fin >> v;
		if (v == -1)
		{
			root = i;
			continue;
		}
		list_ad[i].push_back(v);
		list_ad[v].push_back(i);
	}

	vector<int> code = pruefer_code();
	vector<pair<int, int>> edges = pruefer_decode(code);
	vector<int> parent = build_parent_list(n, edges, root);

	for (int i = 0; i < (int)parent.size(); i++)
		fout << parent[i] << " ";*/

	// Codarea si decodarea Huffman
	/*string text;
	fin >> text;
	
	map<char, int> freq;
	for (char ch : text)
		freq[ch]++;
	fout << freq.size() << endl;
	for (auto pair : freq)
		fout << pair.first << " " << pair.second << endl;

	priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
	for (auto pair : freq)
		pq.push(new HuffmanNode(pair.first, pair.second));
	while (pq.size() > 1) 
	{
		HuffmanNode* left = pq.top(); pq.pop();
		HuffmanNode* right = pq.top(); pq.pop();
		HuffmanNode* combined = new HuffmanNode('\0', left->freq + right->freq, left, right);
		pq.push(combined);
	}

	HuffmanNode* root = pq.top();
	unordered_map<char, string> huffmanCodes;
	buildCodes(root, "", huffmanCodes);

	string encoded = encode(text, huffmanCodes);
	fout << encoded << endl;

	string decoded = decode(encoded, root);
	fout << decoded << endl;

	freeTree(root);*/

	// Arbore minim de acoperire
	int V, E;
	fin >> V >> E;
	vector<vector<int>> edges(E, vector<int>(3));
	for (int i = 0; i < E; i++)
		fin >> edges[i][0] >> edges[i][1] >> edges[i][2];
	pair<int, vector<pair<int, int>>> kruskal = kruskalsMST(V, edges);
	cout << kruskal.first << endl << kruskal.second.size() << endl;
	for (auto& e : kruskal.second)
		cout << e.first << " " << e.second << endl;
}
