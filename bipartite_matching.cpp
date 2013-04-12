#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

#define uint unsigned int
#define UNMATCHED 0xffffffff
#define MAX_INSTANCE_SIZE 500

using namespace std;

uint size_A, size_B, num_edges;
vector<uint> graph[MAX_INSTANCE_SIZE];
uint matched[MAX_INSTANCE_SIZE];
bool visited[MAX_INSTANCE_SIZE];

typedef struct _vertex {
  char type;
  uint id;
} vertex;

uint vertex_to_uid(vertex v) {
  return ((v.type == 'A') ? 0 : size_A) + v.id;
}

vertex uid_to_vertex(uint uid) {
  vertex ret;
  ret.type = (uid < size_A) ? 'A' : 'B';
  ret.id = (uid < size_A) ? uid : uid - size_A;
  return ret;
}

bool augment_path(uint uid) {
  for (uint i = 0; i < graph[uid].size(); i++) {
    uint neighbour = graph[uid][i];
    if (visited[neighbour]) {
      continue;
    }

    if (matched[neighbour] == UNMATCHED) {
      matched[uid] = neighbour;
      matched[neighbour] = uid;
      return true;
    } else if (matched[neighbour] != uid) {
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
  // initialize variables
  fill(matched, matched + MAX_INSTANCE_SIZE, UNMATCHED);

  scanf("%d %d %d\n", &size_A, &size_B, &num_edges);

  vertex vertex_A, vertex_B;
  uint uid_A, uid_B;
  for (uint i = 0; i < num_edges; i++) {
    scanf("%c%d %c%d\n", &vertex_A.type, &vertex_A.id, &vertex_B.type, &vertex_B.id);
    uid_A = vertex_to_uid(vertex_A);
    uid_B = vertex_to_uid(vertex_B);

    graph[uid_A].push_back(uid_B);
    graph[uid_B].push_back(uid_A);
  }

  uint size_matching = 0;
  for (uint i = 0; i < size_A; i++) {
    if (matched[i] == UNMATCHED) {
      fill(visited, visited + MAX_INSTANCE_SIZE, false);
      if (augment_path(i)) {
        size_matching++;
      }
    }
  }

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
