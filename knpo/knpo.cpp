#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include "knpo.h"
    
using namespace std;

int findShortestPath(vector<vector<int>>& adj_matrix, int V, int src) {

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
    return dist.back();
}

vector<string> readDataFromFile(vector<vector<int>> &adj_matrix)
{ 
    //открытие файла
    ifstream file;
    file.open("input.csv");
    //считывание первой строки файла
    string line;
    getline(file, line);
    stringstream ss(line);

    string label;
    vector<string> labels;
    int targetCityNumber = 0;

    //заполнить вектор названиями городов
    while (getline(ss, label, ';')) {
        if (label != "") {
            labels.push_back(label);
        }
    }
    adj_matrix.resize(labels.size(), vector<int>(labels.size(), 0));
    //заполнение матрицы смежности из файла
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

    file.close();

    return labels;
}

void outputResultToFile(vector<vector<int>> adj_matrix, vector<string> labels)
{
    //вывод в файл
    ofstream fout;
    fout.open("output.txt");
    fout << findShortestPath(adj_matrix, labels.size(), 0);
    fout.close();
}

int main()
{   
    vector<vector<int>> adj_matrix;
    auto labels = readDataFromFile(adj_matrix);
    int num_nodes = labels.size();

    outputResultToFile(adj_matrix, labels);

    return 0;
}
