// Directed Graph with Adjacency List Simulation

#include <iostream>

using namespace std;

// Structure to represent an edge in the adjacency list
struct edge {
    int adj_vtx; // index of adjacent vertex
    edge* next;  // pointer to next edge in list

    edge() {
        adj_vtx = -1;
        next = nullptr;
    }
};

// Queue Class for BFS
class Queue {
private:
    struct Node {
        int data;
        Node* next;

        Node(int value) {
            data = value;
            next = nullptr;
        }
    };

    Node* front;
    Node* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(int item) {
        Node* newNode = new Node(item);
        if (isEmpty()) { // if empty, front + rear = newNode
            front = rear = newNode;
        } else {         // else, add new node to rear
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) return -1;

        Node* temp = front;
        int data = temp->data;
        front = front->next;

        delete temp;
        if (front == nullptr) rear = nullptr;
        return data;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

// Directed Graph with Adjacency Lists
class Graph {
private:
    int V;       // num vertices
    edge** adj;  // pointer to array containing edges
    
    // Helper for DFS; Recursively Prints
    void DFSUtil(int v, bool visited[]) {
        visited[v] = true; // mark currrent as visited
        cout << v << " ";  // output

        // Traverse Deeper
        edge *temp = adj[v];                      // temp pointer to traverse
        while (temp != nullptr) {                 // while not at end
            if (!visited[temp->adj_vtx]) {        // if not visited
                DFSUtil(temp->adj_vtx, visited);  // recursively traverse deeper
            }
            temp = temp->next;                    // move to next edge
        }
    }


public:
    // Constructor initializes graph with V vertices
    Graph(int V) {
        this->V = V;           // set num vertices
        adj = new edge*[V];    // create empty array of edge pointers for each vertex
        for (int i = 0; i < V; i++) {
            adj[i] = nullptr;  // initialize all to null
        }
    }

    // Adds a directed edge from vertex v to vertex w
    void addEdge(int v, int w) {
        edge* newEdge = new edge(); // new edge
        newEdge->adj_vtx = w;       // set vertex to w
        newEdge->next = nullptr;    // set next to null

        if (adj[v] == nullptr) {    // if list empty, newEdge is first edge
            adj[v] = newEdge; 
        } else {                    // go to end of list
            edge* temp = adj[v];
            while (temp != nullptr && temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newEdge;   // append edge to end
        }
    }

    // Breadth-First Search from starting vertex
    void BFS(int s) {
        // Bool Array to track Visited Verticies, Set all to False
        bool* visited = new bool[V]; 
        for (int i = 0; i < V; i++) visited[i] = false;

        Queue queue;       // create queue
        queue.enqueue(s);  // enqueue starting vertex
        visited[s] = true; // starting vertex is visted

        // Loop thru Queue: Dequeue Vertex, Print
        while (!queue.isEmpty()) {
            int v = queue.dequeue(); // dequeue front vertex
            cout << v << " ";        // print

            // Loop thru Adj List: Enqueues Unvisited Vertices, Marks Them, Move to Next Edge
            edge* temp = adj[v];      // temp pointer to traverse adj list
            while (temp != nullptr) { // while not end of adj lsit
                int adj_vtx = temp->adj_vtx;  // get vertex number
                if (!visited[adj_vtx]) {      // If not visited
                    queue.enqueue(adj_vtx);      // enqueue vertex
                    visited[adj_vtx] = true;     // mark visited
                }
                temp = temp->next; // move to next edge in Adj List
            }
        }
    }

    // Depth-First Search from a given vertex
    void DFS(int v) {
        // Mark all vertices as Not Visited
        bool *visited = new bool[V]; // array track visited vertices
        for (int i = 0; i < V; i++) visited[i] = false; // set all to Not Visited

        // Print traversal recursively
        DFSUtil(v, visited);
    }

    // Find if Path Exists from s to t with BFS
    bool pathExist (int s, int t) {
        if (s == t) return true;

        // Bool Array to track Visited Verticies, Set all to False
        bool* visited = new bool[V]; 
        for (int i = 0; i < V; i++) visited[i] = false;

        Queue queue;       // create queue
        queue.enqueue(s);  // enqueue starting vertex
        visited[s] = true; // starting vertex is visted

        // Loop thru Queue: Dequeue Vertex, Print
        while (!queue.isEmpty()) {
            int v = queue.dequeue(); // dequeue front vertex

            // Loop thru Adj List: Enqueues Unvisited Vertices, Marks Them, Move to Next Edge
            edge* temp = adj[v];      // temp pointer to traverse adj list
            while (temp != nullptr) { // while not end of adj lsit
                int adj_vtx = temp->adj_vtx;  // get vertex number

                if (adj_vtx == t) return true; // found path

                if (!visited[adj_vtx]) {      // if not visited
                    queue.enqueue(adj_vtx);      // enqueue vertex
                    visited[adj_vtx] = true;     // mark visited
                }
                temp = temp->next; // move to next edge in Adj List
            }
        }
        return false; // no path found
    }
};

// Directed Graph with Adjacency List Simulation
int main() {
    Graph g(5);

    // Add Edges
    cout << "  > adding edges... \n\n";
    g.addEdge(0, 1); // 0 -> 1 -> 2 -> x
    g.addEdge(0, 2); // 1 -> 3 -> x
    g.addEdge(1, 3); // 2 -> 4 -> x
    g.addEdge(2, 4); // 3 -> 4 -> x
    g.addEdge(3, 4); // 4 -> 2 -> x
    g.addEdge(4, 2);

    // Perform BFS
    cout << "BFS from vertex 0: ";
    g.BFS(0);
    cout << endl;

    // Perform DFS
    cout << "DFS from vertex 0: ";
    g.DFS(0);
    cout << endl;

    // Check Path Existence
    cout << "Path exists from 0 to 4: ";
    bool exists = g.pathExist(0, 4); // Check for a path from vertex 0 to 4
    cout << (exists ? "Yes" : "No") << endl;

    cout << "Path exists from 4 to 3: ";
    exists = g.pathExist(4, 3); // Check for a path from vertex 1 to 4
    cout << (exists ? "Yes" : "No") << endl;

    return 0;
}
