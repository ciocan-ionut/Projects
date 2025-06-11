#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("graf.txt");
ifstream f("tranzitiv.txt");
ifstream file("labirint_1.txt");

void BFS(int n, int start, int mat_ad[10][10], int coada[100], int* vizitat, int* distanta, int* parinte) {
    int i, k, st, dr;
    st = dr = 1;
    coada[1] = start;
    vizitat[start] = true;
    distanta[start] = 0;

    while (st <= dr) 
    {
        k = coada[st];
        for (i = 1; i <= n; i++) 
        {
            if (!vizitat[i] && mat_ad[k][i] == 1) 
            {
                vizitat[i] = true;
                dr++;
                coada[dr] = i;
                distanta[i] = distanta[k] + 1;
                parinte[i] = k;
            }
        }
        st++;
    }
}

struct Graf
{
    int mat[10][10];
    int n;
};

void DFS_VISIT(Graf* G, int u, int mat_ad[10][10], int* vizitat)
{
    vizitat[u] = true;
    for (int i = 1; i <= G->n; i++)
        if (mat_ad[u][i] == 1 && !vizitat[i])
            DFS_VISIT(G, i, mat_ad, vizitat);
}

const int rows = 21, cols = 42;
char maze[rows][cols];
int dist[rows][cols];
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

void LeeRec(int x, int y, int cost)
{
    if (x < 0 || x >= rows || y < 0 || y >= cols || maze[x][y] == '1')
        return;

    if (dist[x][y] <= cost)
        return;

    dist[x][y] = cost;

    for (int k = 0; k < 4; k++)
        LeeRec(x + dx[k], y + dy[k], cost + 1);
}

void traseu(int x, int y)
{
    if (dist[x][y] == 1)
        return;

    maze[x][y] = '.';

    for (int k = 0; k < 4; k++)
    {
        int newX = x + dx[k];
        int newY = y + dy[k];

        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
            dist[newX][newY] == dist[x][y] - 1)
        {
            traseu(newX, newY);
            break;
        }
    }
}

int main()
{
    int n, mat_ad[10][10], coada[100], vizitat_BFS[10] = { false }, distante[10] = { 0 }, vizitat_DFS[10] = { false }, parinti[10];
    Graf G;
    //Citim nr. de noduri
	cin >> n; G.n = n;

    //Citim matricea de adiacenta
	for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> mat_ad[i][j];
            G.mat[i][j] = mat_ad[i][j];
        }

    //Cerinta 4
    int sursaBFS;
    cout << "Introduceti nodul sursa (BFS): ";
    cin >> sursaBFS;
    BFS(n, sursaBFS, mat_ad, coada, vizitat_BFS, distante, parinti);
    for (int i = 1; i <= n; i++)
        if (vizitat_BFS[i])
            cout << "Varful " << i << " distanta fata de sursa este: " << distante[i] << endl;
    
    //Cerinta 5
    int source2;
    cout << endl << "Introduceti nodul sursa (DFS): ";
    cin >> source2;
    DFS_VISIT(&G, source2, mat_ad, vizitat_DFS);
    for (int i = 1; i <= n; i++) 
        if (vizitat_DFS[i] == 1) 
            cout << "Varful " << i << endl;

    //Cerinta 1
    int v, v1, v2;
    fin >> v;
    int mat_adM[10][10] = { 0 }, vizitat_BFSM[10] = { false }, distanteM[10] = { 0 }, parintiM[10] = { 0 };
    while (fin >> v1 >> v2)
        mat_adM[v1][v2] = 1;
    int source3, destinatie;
    cout << endl << "Introduceti varful sursa (Moore): ";
    cin >> source3;
    BFS(v, source3, mat_adM, coada, vizitat_BFSM, distanteM, parintiM);
    cout << "Introduceti varful destinatie: ";
    cin >> destinatie;
    if (parintiM[destinatie] == 0)
        cout << "Nu exista lant!";
    else
    {
        cout << "Lantul minim: ";
        while (destinatie != 0)
        {
            cout << destinatie << ' ';
            destinatie = parintiM[destinatie];
        }
    }

    //Cerinta 2
    int mat_tranz[10][10];
    f >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            f >> mat_tranz[i][j];
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (mat_tranz[i][j] == 0)
                    mat_tranz[i][j] = mat_tranz[i][k] * mat_tranz[k][j];
    cout << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << endl;
        for (int j = 1; j <= n; j++)
            cout << mat_tranz[i][j] << ' ';
    }

    //Cerinta 3
    int startX, startY, finishX, finishY;
    if (!file)
        return 1;
    for (int i = 0; i < rows; i++)
        file.getline(maze[i], cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 'S')
            {
                startX = i + 1;
                startY = j - 1;
            }
            if (maze[i][j] == 'F')
            {
                finishX = i - 1;
                finishY = j;
            }
            dist[i][j] = 100;
        }
    file.close();

    LeeRec(startX, startY, 1); //Cream matricea de distante
    if (dist[finishX][finishY] == 100)
        return 1;
    traseu(finishX, finishY); //Modificam labirintul pentru a afisa drumul
    
    cout << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << endl;
        for (int j = 0; j < cols; j++)
            cout << maze[i][j];
    }
    return 0;
}