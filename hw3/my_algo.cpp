#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <fstream>
#include <string>


using namespace std;

vector<unordered_set<int>> V;
vector<int> best_clique;

int find_pivot(unordered_set<int>& P, unordered_set<int>& X)
{
    int etalon = -1;
    int etalon_size = -1;
    unordered_set<int> PX = P;
    PX.insert(X.begin(), X.end());
    for (int u : PX)
    {
        int cnt = 0;
        for (int v : P)
            if (V[u].count(v)) cnt++;

        if (cnt > etalon_size)
        {
            etalon_size = cnt;
            etalon = u;
        }
    }
    return etalon;
}

void BronKerbosch(vector<int> R, unordered_set<int> P, unordered_set<int> X)
{
    if (P.empty() && X.empty())
    {
        if (R.size() > best_clique.size())
            best_clique = R;
        return;
    }

    int u = find_pivot(P,X);
    vector<int> candidates;

    if (u == -1)
        for (int el : P) candidates.push_back(el);
    else
    {
        for (int el: P)
            if (V[u].find(el) == V[u].end()) candidates.push_back(el);
    }


    for (int el: candidates)
    {
        vector<int> R_next = R;
        unordered_set<int> P_next;
        unordered_set<int> X_next;

        R_next.push_back(el);

        for (int i: P)
        {
            if (V[el].find(i) != V[el].end()) P_next.insert(i);
        }
        for (int j: X)
        {
            if (V[el].find(j) != V[el].end()) X_next.insert(j);
        }

        BronKerbosch(R_next, P_next, X_next);
        P.erase(el);
        X.insert(el);
    }
}

void output_vector(vector<int> vec)
{
    cout << "Library max clique:"  << endl;
    for (int i: vec)
    {
        cout << i << ' ';
    }
    cout << endl;
}

int main()
{
    vector<string> filenames = {"graph1.txt", "graph2.txt", "graph3.txt"};
    for (const string& filename : filenames)
    {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Cannot open file: " << filename << "\n";
            return 1;
        }
        cout << "Processing file: " << filename << endl;

        int N;
        int a, b;

        fin >> N;

        V.assign(N + 1, {});
        while (fin >> a >> b)
        {
            V[a].insert(b);
            V[b].insert(a);
        }

        vector<int> R;
        unordered_set<int> P;
        unordered_set<int> X;

        for (int i = 1; i <= N; i++)
            P.insert(i);

        auto start = chrono::high_resolution_clock::now();

        BronKerbosch(R, P, X);

        auto end = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(end - start).count();

        output_vector(best_clique);
        cout << "Size of maximum clique: " << best_clique.size() << endl;
        cout << "My algorithm time: " << ms << " ms" << endl << endl;
    }
    return 0;
}