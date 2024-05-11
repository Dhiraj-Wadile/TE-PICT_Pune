#include <bits/stdc++.h>
using namespace std;


struct Edge
{
   int src, dest, weight;
};


vector<Edge> elist;


void printPath(int destination, vector<int> &pred)
{
   vector<int> path;
   int curr = destination;


   while (curr != -1)
   {
       path.push_back(curr);
       curr = pred[curr];
   }


   reverse(path.begin(), path.end());


   for (int i = 0; i < path.size(); i++)
   {
       cout << path[i] << "-  "[i == path.size() - 1];
   }
   cout << endl;
}


void BellmanFord(int src, int n)
{
   vector<int> distance(n + 1, INT_MAX);
   vector<int> pred(n + 1, -1);
   distance[src] = 0;
   pred[src] = -1;


   for (int i = 1; i < n; i++)
   {
       for (const Edge &ed : elist)
       {
           if (distance[ed.src] + ed.weight < distance[ed.dest])
           {
               distance[ed.dest] = distance[ed.src] + ed.weight;
               pred[ed.dest] = ed.src;
           }
       }
   }


   // Check for negative-weight cycles
   for (const Edge &ed : elist)
   {
       if (distance[ed.src] + ed.weight < distance[ed.dest])
       {
           cout << "Negative-weight cycle detected." << endl;
           return;
       }
   }


   // Print the distances from the source vertex
   for (int i = 2; i <= n; i++)
   {


       cout << "\nShortest distance from " << src << " to " << i << " is " << distance[i] << endl;
       cout << "Predecessor of " << i << " is " << pred[i] << endl;
   }
   cout << endl;
  
   for (int i = 2; i <= n; i++)
   {
       printPath(i, pred);
   }
}




int main()
{
   int vert, noedge, u, v, w;


   cout << "Enter the number of vertices: ";
   cin >> vert;


   cout << "Enter the number of edges: ";
   cin >> noedge;


   cout << "Enter edges in the format (source destination weight):" << endl;
   for (int i = 0; i < noedge; i++)
   {
       cin >> u >> v >> w;
       elist.push_back({u, v, w});
   }


   int sourceVertex;
   cout << "Enter the source vertex: ";
   cin >> sourceVertex;


   BellmanFord(sourceVertex, vert);


   return 0;
}


// Enter the number of vertices: 6
// Enter the number of edges: 9
// Enter edges in the format (source destination weight):

// 1 2 6
// 1 3 4
// 1 4 5
// 3 2 -2
// 4 3 -2
// 2 5 -1
// 3 5 3
// 4 6 -1
// 5 6 3
// Enter the source vertex: 1
// Shortest distance from 1 to 2 is 1
// Predecessor of 2 is 3
// Shortest distance from 1 to 3 is 3
// Predecessor of 3 is 4
// Shortest distance from 1 to 4 is 5
// Predecessor of 4 is 1
// Shortest distance from 1 to 5 is 0
// Predecessor of 5 is 2
// Shortest distance from 1 to 6 is 3
// Predecessor of 6 is 5
// 1-4-3-2
// 1-4-3
// 1-4
// 1-4-3-2-5
// 1-4-3-2-5-6