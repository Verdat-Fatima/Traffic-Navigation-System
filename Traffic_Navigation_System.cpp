#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <map>
using namespace std;

class Graph {
    int numLocations;
    vector<vector<pair<int, int>>> map;

public:
    //  Constructor - creates a map with empty roads
    Graph(int size) {
        numLocations = size;
        map.resize(size);
    }

    //  Add a road between two locations
    void addRoad(int from, int to, int distance) {
        map[from].push_back({to, distance});
        map[to].push_back({from, distance}); // bidirectional road
    }

    // Use Dijkstra's algorithm to find shortest path
    void findShortestPath(int start, int end, vector<string>& names) {
        vector<int> dist(numLocations, INT_MAX);  // Distance from start
        vector<int> previous(numLocations, -1);   // To reconstruct path
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()){
            int current = pq.top().second;
            pq.pop();

            for (auto& neighbor : map[current]) {
                int next = neighbor.first;
                int roadLength = neighbor.second;

                if (dist[next] > dist[current] + roadLength) {
                    dist[next] = dist[current] + roadLength;
                    previous[next] = current;
                    pq.push({dist[next], next});
                }
            }
        }

        //Print result
        cout << "\nShortest distance from " << names[start]
             << " to " << names[end] << " is: " << dist[end] << " km" << endl;

        cout << "Route: ";
        showPath(previous, start, end, names);
        cout << endl;
    }

    // Show the actual path using stack
    void showPath(vector<int>& previous, int start, int end, vector<string>& names) {
        stack<int> path;
        int current = end;

        while (current != -1) {
            path.push(current);
            current = previous[current];
        }

        // If no path exists
        if (path.top() != start) {
            cout << "No route found.";
            return;
        }

        while (!path.empty()) {
            cout << names[path.top()];
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
    }
};

int main() {
    int totalPlaces = 7;
    Graph g(totalPlaces);

    // Mapping names to numbers
    map<string, int> nameToNumber = {
        {"F-6", 0},
        {"G-9", 1},
        {"BlueArea", 2},
        {"I-8", 3},
        {"RawalLake", 4},
        {"Centaurus", 5},
        {"Faizabad", 6}
    };

    // Mapping numbers to names
    vector<string> numberToName = {
        "F-6", "G-9", "BlueArea", "I-8", "RawalLake", "Centaurus", "Faizabad"
    };

    // Add roads (edges) between locations
    g.addRoad(0, 1, 5); // F-6 <-> G-9
    g.addRoad(0, 2, 3); // F-6 <-> BlueArea
    g.addRoad(1, 3, 4); // G-9 <-> I-8
    g.addRoad(1, 5, 4); // G-9 <-> Centaurus
    g.addRoad(2, 5, 2); // BlueArea <-> Centaurus
    g.addRoad(2, 6, 7); // BlueArea <-> Faizabad
    g.addRoad(3, 4, 3); // I-8 <-> RawalLake
    g.addRoad(3, 4, 5); // I-8 <-> RawalLake
    g.addRoad(4, 5, 1); // RawalLake <-> Centaurus
    g.addRoad(4, 6, 5); // RawalLake <-> Faizabad
    g.addRoad(5, 6, 4); // Centaurus <-> Faizabad

cout << R"(                 Islamabad Locations Map 

                (5 km)                     (4 km)
       [F-6]---------------- [G-9]------------------------[I-8]
         |                     \                           /  |
        (3 km)               (4 km)                  (5 km) (3 km)
         |                       \                     /      |
       [BlueArea]---(2km)----[Centaurus]---(1km)----[RawalLake]
                \                    |                 /
                  \                  |               /
                  (7 km)           (4 km)        (5 km)
                       \             |           /
                         \           |         /
                            \        |       /
                               [ Faizabad ]
                                
)";


    // Take input
    cout << "Islamabad Traffic Navigation System\n";
    cout << "Available Places: F-6, G-9, BlueArea, I-8, RawalLake, Centaurus, Faizabad\n";

    string from, to;
    cout << "Enter start place: ";
    cin >> from;
    cout << "Enter destination: ";
    cin >> to;

    // Check for invalid input
    if (nameToNumber.find(from) == nameToNumber.end() || nameToNumber.find(to) == nameToNumber.end()) {
        cout << "Invalid place name.\n";
        return 0;
    }

    int startIndex = nameToNumber[from];
    int endIndex = nameToNumber[to];

    g.findShortestPath(startIndex, endIndex, numberToName);

    return 0;
}