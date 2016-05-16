// Weighted Directed Graph using Adjacency List

#include <iostream>
#include <vector>
#include <queue> 
using namespace std;

struct EdgeNode {
	int vertice_id;
	int weight;
	EdgeNode *next;
};

struct GraphNode {
	int id;
	char value;
	EdgeNode *next;
	bool flag = false;
};

typedef GraphNode VerticeNode;

struct comparator {
	bool operator()(int i, int j) {
		return i > j;
	}
};

class Graph {
public:
	vector<GraphNode*> vertex;

	int AddVertice(char v = 0) {
		int id = vertex.size();
		GraphNode* tmp = new GraphNode;
		tmp->id = id;
		tmp->value = v;
		tmp->next = NULL;
		vertex.push_back(tmp);
		return id;
	}

	void AddEdge(int vertice1, int vertice2, int weight) {
		for (auto vertice : vertex) {
			if (vertice->id == vertice1) {
				EdgeNode* tmp = new EdgeNode;
				tmp->vertice_id = vertice2;
				tmp->weight = weight;
				tmp->next = NULL;
				EdgeNode* edge = vertice->next;
				if (edge == NULL)
					vertice->next = tmp;
				else {
					while (edge->next != NULL) {
						edge = edge->next;
					}
					edge->next = tmp;
				}
				break;
			}
		}
	}

	void print() {
		for (auto vertice : vertex) {
			cout << vertice->id << "| -> ";
			auto edge = vertice->next;
			while (edge != NULL) {
				cout << edge->vertice_id << " -> ";
				edge = edge->next;
			}
			cout << endl;
		}
	}

	GraphNode* getVertice(int key) {
		for (auto vertice : vertex) {
			if (vertice->id == key) {
				return vertice;
			}
		}
		return NULL;
	}

	void bfs(int key) {
		GraphNode *vertice;
		EdgeNode *edge;
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			vertice = getVertice(q.front());
			q.pop();
			edge = vertice->next;
			while (edge != NULL) {
				if (getVertice(edge->vertice_id)->flag == false) {
					cout << edge->vertice_id << endl;
					if (key == edge->vertice_id) {
						cout << "Found" << endl;
					}
					getVertice(edge->vertice_id)->flag = true;
					q.push(edge->vertice_id);
				}
				edge = edge->next;
			}
		}
	}

	void dijkstra() {
		priority_queue<int, std::vector<int>, comparator> pq;
		//vector<int> PriorityQueue;
		int total_vertice = vertex.size();
		int *d		= new int[total_vertice];
		int *pred	= new int[total_vertice];
		
		for (int i = 0; i < total_vertice; i++) {
			d[i] = 999999;
			pq.push(i);
		}
		//make_heap(PriorityQueue.begin(), PriorityQueue.end()); // Make vector PQ using make_heap() 
		
		int s = pq.top(); // Our source vertice
		d[s] = 0;  // Path of source is set to zero
		pred[s] = -1;

		while (!pq.empty()) {
			int u = pq.top();
			pq.pop();
			//pop_heap(PriorityQueue.begin(), PriorityQueue.end());
			//PriorityQueue.pop_back();

			//cout << u << endl;
			EdgeNode* u_adjacent = vertex[u]->next;
			//cout << "Transversing Edges  " << endl;
			while (u_adjacent != NULL) { // each edge of vertex u
				
				int v = u_adjacent->vertice_id;
				//cout << "\t" << v << "\tdu:" << d[u] << "\tweigh:" << u_adjacent->weight << "\tdv:" << d[v] << endl;
				if (d[u] + u_adjacent->weight < d[v]) {
					d[v] = d[u] + u_adjacent->weight;
					pq.push(v);
					pred[v] = u;
				}
				u_adjacent = u_adjacent->next;
			}
			//pq.pop();
		}

		for (int i = 0; i < total_vertice; i++) {
			printf("d[%d]=%d \t\t pred[%d]=%d\n",i,d[i],i,pred[i]);
		}
	}
};

int main() {
	Graph g;
	cout << "STARTED" << endl;
	int v1 = g.AddVertice('A');
	int v2 = g.AddVertice('B');
	int v3 = g.AddVertice('C');
	int v4 = g.AddVertice('D');
	int v5 = g.AddVertice('E');

	g.AddEdge(v1, v2, 7);
	g.AddEdge(v1, v3, 2);

	g.AddEdge(v2, v4, 1);
	g.AddEdge(v2, v3, 2);

	g.AddEdge(v3, v4, 8);
	g.AddEdge(v3, v2, 3);
	g.AddEdge(v3, v5, 5);
	
	g.AddEdge(v4, v5, 5);
	
	g.AddEdge(v5, v4, 4);

	
	//g.bfs(v5);

	g.print();
	cout << endl << endl;
	g.dijkstra();

	return 0;
}