// c16

#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX];    // Adjacency matrix
int graphSize[MAX];     // Number of neighbors per node
int allPaths[MAX][MAX]; // Stores all valid paths
int pathLengths[MAX];   // Length of each stored path
int totalPaths = 0;

int currentPath[MAX]; // Temporary path used during DFS

void dfs(int curr, int end, int depth, int minDepth, int pathLen)
{
    if (depth > minDepth + 1)
        return;

    if (curr == end)
    {
        if (depth == minDepth || depth == minDepth + 1)
        {
            for (int i = 0; i < pathLen; ++i)
                allPaths[totalPaths][i] = currentPath[i];
            pathLengths[totalPaths] = pathLen;
            totalPaths++;
        }
        return;
    }

    for (int i = 0; i < graphSize[curr]; ++i)
    {
        int neighbor = graph[curr][i];

        // Check if neighbor is already in currentPath
        bool visited = false;
        for (int j = 0; j < pathLen; ++j)
        {
            if (currentPath[j] == neighbor)
            {
                visited = true;
                break;
            }
        }

        if (!visited)
        {
            currentPath[pathLen] = neighbor;
            dfs(neighbor, end, depth + 1, minDepth, pathLen + 1);
        }
    }
}

int bfsMinSteps(int start, int end, int n)
{
    bool visited[MAX];
    for (int i = 0; i < n; ++i)
        visited[i] = false;

    queue<int> q;
    queue<int> d;
    q.push(start);
    d.push(0);
    visited[start] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        int depth = d.front();
        d.pop();

        if (node == end)
            return depth;

        for (int i = 0; i < graphSize[node]; ++i)
        {
            int neighbor = graph[node][i];
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
                d.push(depth + 1);
            }
        }
    }

    return -1;
}

int main()
{
    int n, m;
    cout << "Enter number of cities and number of roads: ";
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        graphSize[i] = 0;

    cout << "Enter each road (2 cities connected, e.g. 0 1):\n";
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u][graphSize[u]++] = v;
        graph[v][graphSize[v]++] = u; // undirected
    }

    int start, end;
    cout << "Enter start city and destination city: ";
    cin >> start >> end;

    int minSteps = bfsMinSteps(start, end, n);

    currentPath[0] = start;
    dfs(start, end, 0, minSteps, 1);

    cout << "\nValid routes from " << start << " to " << end << ":\n";
    for (int i = 0; i < totalPaths; ++i)
    {
        for (int j = 0; j < pathLengths[i]; ++j)
            cout << allPaths[i][j] << " ";
        cout << endl;
    }

    return 0;
}
