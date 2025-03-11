#include "dijkstras.h"

// g++ -std=c++17 dijkstras_main.cpp dijkstras.cpp -o dijkstra

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;

    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    distance[source] = 0;

    while (!pq.empty()) {
        auto [dist, u] = pq.top();
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (Edge edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;

            if (!visited[v] && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                previous[v] = u;
                pq.push({distance[v],v});
            }
        }
    }

    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;

}

void print_path(const vector<int>& v, int total) {
    if (!v.empty()) {
        for (const int& node : v) {
            std::cout << node << " ";
        }
    }
    std::cout << "\nTotal cost is " << total << "\n";
}
