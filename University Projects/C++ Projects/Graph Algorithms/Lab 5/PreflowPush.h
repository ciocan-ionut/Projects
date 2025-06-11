#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class PreflowPush {
    int n; 
    int s, t; 
    vector<vector<int>> capacity; 
    vector<vector<int>> flow;     
    vector<int> height;           
    vector<int> excess;           
    vector<vector<int>> adj;      

public:
    PreflowPush(int n, int s, int t, const vector<vector<int>>& capacity);

    void initializePreflow();

    bool push(int u);

    void relabel(int u);

    int maxFlow();
};