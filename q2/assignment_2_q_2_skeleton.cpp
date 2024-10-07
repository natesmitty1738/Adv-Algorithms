// CSCI 411 - Fall 2024
// Assignment 2 Question 2 - Outpost
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the outpost problem on assignment 2.

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <math.h>
#include <queue>

// Struct to represent an Outpost
struct Outpost
{
  int id;  // Unique identifier for the outpost
  float x; // X-coordinate of the outpost
  float y; // Y-coordinate of the outpost
  float s; // Signal strength of the outpost's transmitter
};

// Function to find the maximum number of outposts that can be contacted
int maxContacts(std::vector<Outpost> &outposts, std::vector<std::vector<float>> &distances)
{
  int maxContacted = 0;
  int n = outposts.size();

  // Try starting from each outpost
  for (int start = 0; start < n; start++)
  {
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    int contacted = 0;

    // Start BFS from the current outpost
    q.push(start);
    visited[start] = true;

    // BFS
    while (!q.empty())
    {
      int current = q.front();
      q.pop();
      contacted++;

      // check all neighbors
      for (int neighbor = 0; neighbor < n; neighbor++)
      {
        // If the neighbor is not visited and within signal range
        if (!visited[neighbor] && distances[current][neighbor] <= outposts[current].s)
        {
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }
    }

    // update max number of contacted outposts
    maxContacted = std::max(maxContacted, contacted);
  }

  return maxContacted;
}

// calculate distance between two outposts
float distance(Outpost a, Outpost b)
{
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main()
{
  // Read the total number of outposts
  int n = -1;
  std::cin >> n;

  // Read outpost information
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

  // Calculate pairwise distances between outposts
  std::vector<std::vector<float>> distances(outposts.size(), std::vector<float>(outposts.size(), 0));
  for (int i = 0; i < outposts.size(); i++)
  {
    for (int j = i + 1; j < outposts.size(); j++)
    {
      float dist = distance(outposts[i], outposts[j]);
      distances[i][j] = dist;
      distances[j][i] = dist;
    }
  }

  // Calculate and output the maximum number of contactable outposts
  std::cout << maxContacts(outposts, distances) << std::endl;

  return 0;
}