#include <iostream>
#include <vector>
#include <iomanip> // For setw

using namespace std;

struct Item {
    int weight;
    int value;
};

// Function to solve 0/1 knapsack using dynamic programming
void knapsackdp(vector<Item>& items, int cap) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));

    // Build the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= cap; w++) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].value + dp[i - 1][w - items[i - 1].weight]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Print the DP table with border
    cout << "0/1 knapsack dynamic programming approach:" << endl;
    cout << "+" << string(13, '-') << "+";
    for (int w = 0; w <= cap; w++) {
        cout << string(9, '-') << "+";
    }
    cout << endl;

    cout << "| " << setw(2) << "Item" << " | " << setw(7) << "Weight" << " | " << setw(7) << "Value" << " |";
    for (int w = 0; w <= cap; w++) {
        cout << setw(9) << w;
    }
    cout << "|" << endl;

    cout << "+" << string(13, '-') << "+";
    for (int w = 0; w <= cap; w++) {
        cout << string(9, '-') << "+";
    }
    cout << endl;

    for (int i = 0; i <= n; i++) {
        cout << "| " << setw(2) << i << " | " << setw(7) << (i > 0 ? items[i - 1].weight : "") << " | " << setw(7) << (i > 0 ? items[i - 1].value : "") << " |";
        for (int w = 0; w <= cap; w++) {
            cout << setw(9) << dp[i][w];
        }
        cout << "|" << endl;
    }

    cout << "+" << string(13, '-') << "+";
    for (int w = 0; w <= cap; w++) {
        cout << string(9, '-') << "+";
    }
    cout << endl;

    // Find the selected items
    int i = n, w = cap;
    vector<Item> selectedItems;
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(items[i - 1]);
            w -= items[i - 1].weight;
        }
        i--;
    }

    // Print the results
    cout << "The maximum profit is: " << dp[n][cap] << endl;

    if (cap == 0) {
        cout << "The bag is full." << endl;
    } else {
        cout << "Selected items:" << endl;
        cout << "Item  Weight  Value" << endl;
        for (int j = selectedItems.size() - 1; j >= 0; j--) {
            cout << j + 1 << "     " << selectedItems[j].weight << "     " << selectedItems[j].value << endl;
        }
    }
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
        cin >> items[i].weight >> items[i].value;
    }

    knapsackdp(items, cap);

    return 0;
}
