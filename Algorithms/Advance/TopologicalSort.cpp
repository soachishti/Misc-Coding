#include <iostream>
#include <windows.h>
#include <queue> 
#include <stack> 
#include <string> 
using namespace std;

struct VerticeInfo {
	int status;
	string value;
};

class Graph {
public:
	int TotalVertice = 10;
	int **AdjacencyMatrix;
	VerticeInfo *VInfo;

	Graph(int tv) {
		TotalVertice = tv;
		AdjacencyMatrix = new int*[TotalVertice];
		for (int i = 0; i < TotalVertice; i++) {
			AdjacencyMatrix[i] = new int[TotalVertice];
			for (int j = 0; j < TotalVertice; j++) {
				AdjacencyMatrix[i][j] = 0;
			}
		}

		VInfo = new VerticeInfo[TotalVertice];
		for (int i = 0; i < TotalVertice; i++) {
			VInfo[i].value = "";		// Vertice Info 
			VInfo[i].status = 0;		// Flag: set to 0		
		}
	}

	bool AddEdge(int vertice1, int vertice2) {
		if (vertice1 >= 0 && vertice2 >= 0 && vertice1 < TotalVertice && vertice2 < TotalVertice) {
			AdjacencyMatrix[vertice1][vertice2]++;
			return true;
		}
		return false;
	}

	void print() {
		for (int i = 0; i < TotalVertice; i++) {
			for (int j = 0; j < TotalVertice; j++) {
				cout << AdjacencyMatrix[i][j] << "\t";
			}
			cout << endl;
		}
	}

	void ResetFlags() {
		for (int i = 0; i < TotalVertice; i++) 
			VInfo[i].status = 0; // Reset flags
	}

	bool bfs(string key) {
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int vertice = q.front();
			q.pop();

			for (int i = 0; i < TotalVertice; i++) {
				// Check Flag
				if (VInfo[vertice].status == 0) {
					cout << VInfo[vertice].value << endl;
					// Found data
					if (VInfo[vertice].value == key) {

						ResetFlags();
						return true;
					}
					VInfo[vertice].status = 1;
				}
				// Is there edge, Then add to queue.	
				if (VInfo[i].status == 0 && AdjacencyMatrix[vertice][i] != 0) {
					q.push(i);
				}
			}
		}
		ResetFlags();
		return false;
	}

	bool dfs(string key) {
		stack<int> s;
		s.push(0);
		while (!s.empty()) {
			int vertice = s.top();
			int StackSize = s.size();
			for (int i = 0; i < TotalVertice; i++) {
				// Check Flag
				if (VInfo[vertice].status == 0) {
					cout << VInfo[vertice].status << endl;
					// Found data
					if (VInfo[i].value == key) {
						ResetFlags();
						return true;
					}
					VInfo[i].status = 1;
				}

				// Is there edge, Then add to queue.	
				if (VInfo[i].status == 0 && AdjacencyMatrix[vertice][i] != 0) {
					s.push(i);
					break;
				}
			}
			// If no new vertice added, Mean it is end
			if (StackSize == s.size()) {
				// Backtracking
				s.pop();
			}
		}
		ResetFlags();
		return false;
	}

	bool HaveLoop() {
		stack<int> s;
		s.push(0);
		bool isBack = false;
		while (!s.empty()) {
			int vertice = s.top();
			int StackSize = s.size();
			for (int i = 0; i < TotalVertice; i++) {
				// Check Flag
				if (VInfo[vertice].status == 0) {
					cout << VInfo[vertice].value << endl;
					VInfo[vertice].status = 1;
				}
				cout << vertice << "\t" << i << endl;
				// Is there edge, Then add to queue.	
				if (VInfo[i].status == 0 && AdjacencyMatrix[vertice][i] != 0) {
					s.push(i);
					break;
				}
				else if (!isBack && VInfo[i].status == 1 && AdjacencyMatrix[vertice][i] != 0) {
					return true;
				}
			}
			// If no new vertice added, Mean it is end
			if (StackSize == s.size()) {
				// Backtracking
				s.pop();
			}
		}
		ResetFlags();
		return false;
	}

	void TopologicalSortPrint() {
		stack<int> s;
		for (int j = 0; j < TotalVertice; j++) {
			if (VInfo[j].status == 1) continue;
			s.push(j);
			//cout << endl << "STARTED AT " << VInfo[j].value << endl;

			while (!s.empty()) {
				int vertice = s.top();
				int StackSize = s.size();
				for (int i = 0; i < TotalVertice; i++) {
					// Is vertice is not visited and Have edges then add them to queue. 
					if (VInfo[i].status == 0 && AdjacencyMatrix[vertice][i] != 0) {		
						s.push(i);
						break;
					}
				}
				
				// If no new vertice added, Mean it is end
				if (StackSize == s.size()) {
					// Backtracking
					
					if (VInfo[vertice].status == 0)
						cout << VInfo[vertice].value << endl;
						//cout << vertice << "# " << VInfo[vertice].value << endl;
					
					// Vertice visited
					VInfo[vertice].status = 1;

					s.pop();
				}

				
			}
		}
		ResetFlags();
	}

	void SetVerticeValue(int i, string value) {
		VInfo[i].value = value;
	}
};

int main() {
	int TotalVertice = 9;
	Graph g(TotalVertice);
	g.SetVerticeValue(0, "Watch");
	g.SetVerticeValue(1, "Belt");
	g.SetVerticeValue(2, "Shirt");
	g.SetVerticeValue(3, "Tie");
	g.SetVerticeValue(4, "Jacket");
	g.SetVerticeValue(5, "Socks");
	g.SetVerticeValue(6, "Shoes");
	g.SetVerticeValue(7, "Undershorts");
	g.SetVerticeValue(8, "Pant");

	g.AddEdge(2, 3);
	g.AddEdge(3, 4);
	g.AddEdge(2, 1);
	g.AddEdge(1, 4);
	g.AddEdge(7, 8);
	g.AddEdge(8, 1);
	g.AddEdge(7, 6);
	g.AddEdge(8, 6);
	g.AddEdge(5, 6);

	//g.print();
	g.TopologicalSortPrint();
	return 0;
}