#include <iostream>
#include <vector>
#include <string>
#include <queue>       
#include <algorithm>   
using namespace std;


struct Edge {
    int tujuan;
    int jarak;
};


class GRAPH {
private:
    int numVertices;
    vector<vector<Edge>> adjMatrix; 
    vector<char> charKota;
    vector<string> namaKota;

public:
    GRAPH(int V);

    int JumlahTotalKota() const { return numVertices; }
    char ambilCharKota(int i) const { return charKota[i]; }
    string ambilNamaKota(int i) const { return namaKota[i]; }
    const vector<Edge>& ambilAdjMatrix(int i) const { return adjMatrix[i]; }
};


class DFS {
private:
    const GRAPH& graph; 
    void dfsUtil(int mulai, vector<bool>& visited);

public:
    DFS(const GRAPH& g);
    void mulaiPerjalanan(int mulai);
};


class BFS {
private:
    const GRAPH& graph;

public:
    BFS(const GRAPH& g);
    void JalurTercepat(int mulai, int selesai);
};


GRAPH::GRAPH(int V) {
    numVertices = V;

    adjMatrix.resize(numVertices);
    charKota.resize(numVertices);
    namaKota.resize(numVertices);

    char isiCharKota[] = {'A', 'B', 'C', 'D', 'E'};
    string isiNamaKota[] = {
        "Ikan Bakar Pak Harry",
        "Gudang Kaleng Bekas",
        "Sushi Kucing Alya",
        "Kedai IKLC",
        "Pasar Ikan Tengah Malam"
    };

    for (int i = 0; i < numVertices; i++) {
        if (i < 5) {
            charKota[i] = isiCharKota[i];
            namaKota[i] = isiNamaKota[i];
        } else {
            cout << "\nMaaf Kode di Program Hanya Untuk 5 Kota Saja" << endl;
        }
    }


    adjMatrix[0].push_back({2, 2}); 
    adjMatrix[2].push_back({0, 2}); 

    adjMatrix[0].push_back({1, 5}); 
    adjMatrix[1].push_back({0, 5}); 

    adjMatrix[2].push_back({3, 1}); 
    adjMatrix[3].push_back({2, 1});

    adjMatrix[3].push_back({4, 3}); 
    adjMatrix[4].push_back({3, 3}); 

    adjMatrix[3].push_back({1, 4}); 
    adjMatrix[1].push_back({3, 4}); 
}


DFS::DFS(const GRAPH& g) : graph(g) {
}

void DFS::mulaiPerjalanan(int mulai) {
    cout << "PENJELAJAHAN PARUL (DFS dari A):" << endl;
    vector<bool> visited(graph.JumlahTotalKota(), false);
    dfsUtil(mulai, visited);

    cout << endl << endl;
}

void DFS::dfsUtil(int mulai, vector<bool>& visited) {
    visited[mulai] = true;

    cout << graph.ambilCharKota(mulai) << " ";
    for (const auto& tetangga : graph.ambilAdjMatrix(mulai)) {
        int v = tetangga.tujuan;
        if (!visited[v]) {
            cout << " -> ";
            dfsUtil(v, visited);
        }
    }
}


BFS::BFS(const GRAPH& g) : graph(g) {
}

void BFS::JalurTercepat(int mulai, int selesai) {
    int n = graph.JumlahTotalKota();

    queue<int> q;
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> jarakKota(n, 0); 

    q.push(mulai);
    visited[mulai] = true;

    cout << "JALUR TERCEPAT PARUL (BFS):" << endl;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == selesai) break;

        for (const auto& tetangga : graph.ambilAdjMatrix(u)) {
            int v = tetangga.tujuan;
            int jarak = tetangga.jarak;

            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                jarakKota[v] = jarak; 
                q.push(v);
            }
        }
    }

    vector<int> jalur;
    int totalJarak = 0;
    int posisiSekarang = selesai;

    while (posisiSekarang != -1) {
        jalur.push_back(posisiSekarang);
        posisiSekarang = parent[posisiSekarang];
    }

    reverse(jalur.begin(), jalur.end());

    for (size_t i = 0; i < jalur.size(); i++) {
        int u = jalur[i];
        cout << graph.ambilNamaKota(u) << " ( "
             << graph.ambilCharKota(u) << " ) " << endl;

        if (i < jalur.size() - 1) {
            int v = jalur[i + 1];
            int bobot = jarakKota[v]; 
            cout << bobot << "m" << endl;
            totalJarak += bobot;
        }
    }

    cout << endl;
    cout << "Jalur terpendek: ";
    for (size_t i = 0; i < jalur.size(); i++) {
        cout << graph.ambilCharKota(jalur[i]);
        if (i < jalur.size() - 1) {
            cout << " -> ";
        }
    }

    cout << endl;

    cout << "Total langkah : " << jalur.size() - 1 << " edge" << endl;
    cout << "Total " << totalJarak << " meter" << endl;
}


int main() {
    cout << "\n";

    GRAPH g(5); 

    DFS dfs(g); 
    dfs.mulaiPerjalanan(0); 

    BFS bfs(g); 
    bfs.JalurTercepat(0, 4); 

    cin.get(); 
    return 0; 
}