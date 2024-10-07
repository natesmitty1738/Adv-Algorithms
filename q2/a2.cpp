#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <math.h>
#include <queue>
#include <vector>

struct Outpost {
  int id;
  int x;
  int y;
  float s;
};

int maxContacts(std::vector<Outpost> &outposts, std::vector<std::vector<float>> &distances) {
  int maxContacted = 0;
  int n = outposts.size();

  //start from each outpost
  for (int start = 0; start < n; start++) {
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    int contacted = 0;
    //bfs
    q.push(start);
    visited[start] = true;

    while(!q.empty()) {
      //use .front() to go from current - >next node
      int current = q.front();
      //remove
      q.pop();
      contacted++;
    
      //iterate through neighbors
      for (int neighbor = 0; neighbor < n; neighbor++) {
        if (!visited[neighbor] && distances[current][neighbor] <= outposts[current].s) {
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }
    }
    maxContacted = std::max(maxContacted, contacted);
  }
  return maxContacted;
}

float distance(Outpost a, Outpost b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
  int n = -1; //initialize n# outposts
  std::cin >> n;

  std::vector<Outpost> outposts;
  float x = 0, y = 0, s = 0;
  for (int i = 0; i < n; i++)
  {
    std::cin >> x >> y >> s;
    Outpost o;
    o.id = i;
    o.x = x;
    o.y = y;
    o.s = s;
    outposts.push_back(o);
  }

  std::vector<std::vector<float>> distances(outposts.size(), std::vector<float>(outposts.size(), 0));
  for (int i = 0; i < outposts.size(); i++) {
    for (int j = i + 1; j < outposts.size(); j++) {
      float dist = distance(outposts[i], outposts[j]);
      distances[i][j] = dist;
      distances[j][i] = dist;
    }
  }

  std::cout << maxContacts(outposts, distances) << std::endl;

  return 0;
}