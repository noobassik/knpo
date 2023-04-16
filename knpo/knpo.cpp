#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include "knpo.h"

using namespace std;

void dijkstra(vector<vector<int>>& adj_matrix, int V, int src, int targetCityNumber) {

    vector<int> dist(V, INT_MAX); // Инициализировать все расстояния как бесконечные
    dist[src] = 0; // Расстояние исходной вершины от самой себя всегда равно 0 

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (int v = 0; v < V; v++) {
            if (adj_matrix[u][v] != 0 && dist[v] > dist[u] + adj_matrix[u][v]) {
                dist[v] = dist[u] + adj_matrix[u][v];
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    //cout << "Vertex\tDistance from source\n";
    //for (int i = 0; i < V; i++)
    //    cout << i + 1 << "\t" << dist[i] << endl;

    cout << dist[targetCityNumber];
}

int main()
{
    ifstream file;
    file.open("text.csv");
    
    string targetCity;
    int targetCityNumber = 0;
    getline(file, targetCity);

    string line;
    getline(file, line);

    stringstream ss(line);
    string label;
    vector<string> labels;
    while (getline(ss, label, ';')) {
        if (label != "") {
            labels.push_back(label);
        }
        //красивее написать, всегда дает (кол-во городов - 1), добавить условие остановки
        targetCityNumber += (label != targetCity and label != "");
    }
    auto num_nodes = labels.size();

    // инициализировать матрицу нулями
    vector<vector<int>> adj_matrix(num_nodes, vector<int>(num_nodes, 0));
 
    // считывание
    int row = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        int col = 0;
        while (getline(ss, value, ';')) {
            if (value != "" && col > 0) {
                adj_matrix[row][col - 1] = stoi(value);
            }
            col++;
        }
        row++;
    }



    vector<int> cost(labels.size()); // стоимость бензина в каждом городе
    for (int i = 0; i < labels.size(); i++)
    {
        for (int j = 0; j < labels.size(); j++)
        {
            if (adj_matrix[j][i])
            {
                cost[i] = adj_matrix[j][i];
            }
        }
    }


    // вывод
    cout << ";";
    for (string label : labels) {
        cout << label << ";";
    }
    cout << endl;
    for (int i = 0; i < num_nodes; i++) {
        cout << labels[i] << ";";
        for (int j = 0; j < num_nodes; j++) {
            cout << adj_matrix[i][j] << ";";
        }
        cout << endl;
    }

    file.close();

    dijkstra(adj_matrix, labels.size(), 0, targetCityNumber);

    return 0;
}
