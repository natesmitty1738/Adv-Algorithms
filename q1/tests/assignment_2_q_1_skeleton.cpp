#include <iostream>
#include <memory>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>

using namespace std;

/******************************************************************************
 * A simple Node struct                                                       *
 * id - int - the id or name of the node                                      *
 * dist - int - the distance from some given node to this node                *
 * inI - bool - true if the node is a member of the set I and false otherwise *
 * visited - bool - whether or not this node has been visited                 *
 * ****************************************************************************/
struct Node
{
  int id;
  int dist;
  bool inI;
  bool visited;

  Node(int id) : id(id), dist(INT_MAX), inI(false), visited(false) {} // Constructor for initialization
};

/**************************************************************************
 * A simple Edge struct                                                   *
 * from - shared_ptr<Node> - the node where this edge starts              *
 * to - shared_ptr<Node> - the node where this edge ends                  *
 * weight - int - the weight of this edge                                 *
 * ************************************************************************/
struct Edge
{
  shared_ptr<Node> from;
  shared_ptr<Node> to;
  int weight;

  Edge(shared_ptr<Node> from, shared_ptr<Node> to, int weight) : from(from), to(to), weight(weight) {} // Constructor for initialization
};

/****************************************************************************************************************************
 * Given a graph, find the set of nodes that belong to the set I, that is, the set of vertices v such that there            *
 * is at least one path of length negative infinity ending at v.                                                            *
 * A - vector<vector<shared_ptr<Edge>>> - an adjacency list representation of a graph where each element is a weighted edge *
 * return - vector<int> - the integer ids of nodes in the set I                                                             *
 * **************************************************************************************************************************/
vector<int> findReachableNodes(const vector<vector<shared_ptr<Edge>>>& A, const vector<bool>& inCycle);

vector<int> findSetI(vector<vector<shared_ptr<Edge>>> &A) {
    int n = A.size() - 1; // Number of vertices
    vector<long long> dist(n + 1, 0);
    vector<int> parent(n + 1, -1);
    vector<bool> inQueue(n + 1, false);
    vector<int> count(n + 1, 0);
    queue<int> q;

    // Bellman-Ford algorithm
    for (int i = 0; i <= n; i++) {
        q.push(i);
        inQueue[i] = true;
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (const auto& edge : A[u]) {
            int v = edge->to->id;
            if (dist[u] + edge->weight < dist[v]) {
                dist[v] = dist[u] + edge->weight;
                parent[v] = u;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                    count[v]++;
                    if (count[v] > n) {
                        // Negative cycle detected
                        vector<bool> inCycle(n + 1, false);
                        for (int i = 0; i < n; i++) {
                            v = parent[v];
                        }
                        int start = v;
                        do {
                            inCycle[v] = true;
                            v = parent[v];
                        } while (v != start);

                        return findReachableNodes(A, inCycle);
                    }
                }
            }
        }
    }

    // No negative cycles found
    return {};
}

vector<int> findReachableNodes(const vector<vector<shared_ptr<Edge>>>& A, const vector<bool>& inCycle) {
    int n = A.size() - 1;
    vector<bool> visited(n + 1, false);
    vector<int> reachable;
    queue<int> q;

    // Start BFS from all nodes in the cycle
    for (int i = 1; i <= n; i++) {
        if (inCycle[i] && !visited[i]) {
            q.push(i);
            visited[i] = true;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        reachable.push_back(u);

        for (const auto& edge : A[u]) {
            int v = edge->to->id;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    sort(reachable.begin(), reachable.end());
    return reachable;
}

int main()
{
  // Get the number of nodes and number of edges from cin, separated by a space
  int n = -1, m = -1;
  cin >> n >> m;

  // Initialize an adjacency list
  vector<vector<shared_ptr<Edge>>> A(n + 1);

  // Populate nodes
  vector<shared_ptr<Node>> nodes(n + 1);
  for (int i = 1; i <= n; i++)
  {
    nodes[i] = make_shared<Node>(i);
  }

  // Add a dummy node (0) with edges to all other nodes
  nodes[0] = make_shared<Node>(0);
  for (int i = 1; i <= n; i++)
  {
    shared_ptr<Edge> dummyEdge = make_shared<Edge>(nodes[0], nodes[i], 0);
    A[0].push_back(dummyEdge);
  }

  // Get edges from cin and add them to the adjacency list
  int u = -1, v = -1, w = -1;
  for (int i = 0; i < m; i++)
  {
    cin >> u >> v >> w;
    shared_ptr<Edge> e = make_shared<Edge>(nodes[u], nodes[v], w);
    A[u].push_back(e);
  }

  // Find nodes belonging to the set I and print them out in ascending order
  vector<int> I = findSetI(A);

  // Print the result
  if (!I.empty())
  {
    for (size_t i = 0; i < I.size(); i++)
    {
      cout << I[i] << (i < I.size() - 1 ? " " : "\n");
    }
  }
  else
  {
    cout << endl; // Print an empty line if I is empty
  }

  return 0;
}