/**
 * This code is written for demonstrative purposes. We do gross things in ways
 * that are easy to understand (and subsequently remember). It's how I'd write
 * it in a competition.
 */

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

#define uint unsigned int
#define UNMATCHED 0xffffffff

// The algorithm runs in O(VE) which is about MAX_INSTANCE_SIZE^3. An instance
// size of about 500 will run in under a second on your average 2013 machine.

#define MAX_INSTANCE_SIZE 500

using namespace std;

uint size_A, size_B, num_edges;

// We store the bipartite graph as your standard adjacency list.
vector<uint> graph[MAX_INSTANCE_SIZE];

// matched[u] == v and matched[v] == u iff (u, v) is a matched edge.
uint matched[MAX_INSTANCE_SIZE];

// We use this for our DFS
bool visited[MAX_INSTANCE_SIZE];

typedef struct _vertex {
  char type;
  uint id;
} vertex;

// We map all the vertex identifiers into a unique id. Vertices in partition A
// are mapped to [ 0, size A ) and the vertices in partition B are mapped
// to [ size A, number of vertices ). This makes it easy to store the graph
// as a single array and converting back is also very easy.

uint vertex_to_uid(vertex v) {
  return ((v.type == 'A') ? 0 : size_A) + v.id;
}

vertex uid_to_vertex(uint uid) {
  vertex ret;
  if (uid < size_A) {
    ret = (vertex) { 'A', uid };
  } else {
    ret = (vertex) { 'B', uid - size_A };
  }
  ret.type = (uid < size_A) ? 'A' : 'B';
  ret.id = (uid < size_A) ? uid : uid - size_A;
  return ret;
}

// This is the heart of the algorithm. It starts from a free node and performs
// a depth-first search to find an augmenting path. The recursion returns true
// if it finds another free node at the end of an alternating path and then
// as the recursion unwinds, it 'swaps' all the matched edges by updating
// the matched array.
bool augment_path(uint uid) {
  visited[uid] = true;

  for (uint i = 0; i < graph[uid].size(); i++) {
    uint neighbour = graph[uid][i];
    if (visited[neighbour]) {
      continue;
    }

    // Base-case. We've reached a node at the end of an alternating path that
    // ends in a freenode.
    if (matched[neighbour] == UNMATCHED) {
      matched[uid] = neighbour;
      matched[neighbour] = uid;
      return true;
    } else if (matched[neighbour] != uid) {
      // This is not your standard DFS. Because we're DFSing along an
      // alternating path, when we choose the next vertex to visit, we MUST
      // then go along its matching edge. So we say we've visited the neighbour
      // trivially and then recursing on matched[neighbour].

      visited[neighbour] = true;
      if (augment_path(matched[neighbour])) {
        matched[uid] = neighbour;
        matched[neighbour] = uid;
        return true;
      }
    }
  }

  return false;
}

int main() {
  // Uninitialize variables
  fill(matched, matched + MAX_INSTANCE_SIZE, UNMATCHED);

  // Standard competition practice of using cstdio instead of iostream
  scanf("%d %d %d\n", &size_A, &size_B, &num_edges);

  // Reading input
  vertex vertex_A, vertex_B;
  uint uid_A, uid_B;
  for (uint i = 0; i < num_edges; i++) {
    scanf("%c%d %c%d\n", &vertex_A.type, &vertex_A.id, &vertex_B.type, &vertex_B.id);
    uid_A = vertex_to_uid(vertex_A);
    uid_B = vertex_to_uid(vertex_B);

    // Build adjacency list
    graph[uid_A].push_back(uid_B);
    graph[uid_B].push_back(uid_A);
  }

  // We try to augment every free node in partition A. It is provable (see
  // README) that you only need to visit every node once. And you only need to
  // look at a single partition because of the symmetry of a matching.
  uint size_matching = 0;
  for (uint i = 0; i < size_A; i++) {
    if (matched[i] == UNMATCHED) {
      fill(visited, visited + MAX_INSTANCE_SIZE, false);
      if (augment_path(i)) {
        size_matching++;
      }
    }
  }

  // Output
  printf("Size of maximum matching: %d\n", size_matching);
  for (uint i = 0; i < size_A; i++) {
    if (matched[i] != UNMATCHED) {
      vertex matched_A = uid_to_vertex(i);
      vertex matched_B = uid_to_vertex(matched[i]);

      printf("A%d B%d\n", matched_A.id, matched_B.id);
    }
  }

  return 0;
}
