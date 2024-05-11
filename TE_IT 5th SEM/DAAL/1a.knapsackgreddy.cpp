#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // For setw and setprecision

using namespace std;

struct Item {
    int weight;
    int value;
    double ratio; // Value-to-weight ratio
};

// Custom comparator function for sorting items by value-to-weight ratio
bool cmp(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Function to solve Fractional Knapsack using a greedy approach
double fractionalKnapsack(vector<Item>& items, int cap) {
    sort(items.begin(), items.end(), cmp); // Sort items by value-to-weight ratio

    double profit = 0.0;
    int n = items.size();

    cout << "Fractional Knapsack greedy approach:" << endl;
    cout << setfill('-') << setw(58) << "" << setfill(' ') << endl;
    cout << "| " << setw(4) << "Item" << " | " << setw(7) << "Weight" << " | " << setw(7) << "Value" << " | " << setw(11) << "Fraction" << " | " << setw(8) << "Profit" << " | " << setw(18) << "Selection Status" << " |" << endl;
    cout << setfill('-') << setw(58) << "" << setfill(' ') << endl;

    for (int i = 0; i < n && cap > 0; i++) {
        string selectionStatus = "";
        if (cap >= items[i].weight) {
            double fraction = 1.0; // Select the whole item
            selectionStatus = "Selected Completely";
            cout << "| " << setw(4) << i + 1 << " | " << setw(7) << items[i].weight << " | " << setw(7) << items[i].value << " | " << setw(10) << fraction << " | " << setw(9) << items[i].value << " | " << setw(18) << selectionStatus << " |" << endl;
            profit += items[i].value;
            cap -= items[i].weight;
        } else {
            double fraction = (double)cap / items[i].weight; // Select a fraction of the item
            selectionStatus = "Selected Partially";
            cout << "| " << setw(4) << i + 1 << " | " << setw(7) << items[i].weight << " | " << setw(7) << items[i].value << " | " << setw(10) << fraction << " | " << setw(9) << fraction * items[i].value << " | " << setw(18) << selectionStatus << " |" << endl;
            profit += fraction * items[i].value;
            cap = 0;
        }
    }

    cout << setfill('-') << setw(58) << "" << setfill(' ') << endl;

    if (cap == 0) {
        cout << "The bag is full." << endl;
    }

    return profit;
}

int main() {
    cout << "Enter number of items:" << endl;
    int n, cap;
    cin >> n;
    cout << "Enter capacity of knapsack:" << endl;
    cin >> cap;

    vector<Item> items(n);

    cout << "Enter weight and value of each item:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ":" << endl;
        cout << "Weight: ";
        cin >> items[i].weight;
        cout << "Value: ";
        cin >> items[i].value;
        items[i].ratio = (double)items[i].value / items[i].weight; // Calculate value-to-weight ratio
    }

    double maxProfit = fractionalKnapsack(items, cap);

    cout << "Maximum possible profit: " << maxProfit << endl;

    return 0;
}
