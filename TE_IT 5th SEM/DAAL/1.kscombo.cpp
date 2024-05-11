#include <bits/stdc++.h>
using namespace std;

struct Item {
    int weight;
    int value;
};

bool cmp(Item a, Item b) {
    double ratioA = (double)a.value / a.weight;
    double ratioB = (double)b.value / b.weight;
    return ratioA > ratioB;
}

void printTableHeader(const string& title, const vector<string>& headers) {
    cout << title << ":" << endl;
    for (const auto& header : headers) {
        cout << setw(12) << header;
    }
    cout << endl;
}

void fractional_knapsack(Item arr[], int cap, int n) {
    double profit = 0;
    sort(arr, arr + n, cmp);

    vector<string> headers = {"Item", "Weight", "Value", "Fraction", "Profit"};
    printTableHeader("Fractional Knapsack Greedy Approach", headers);

    for (int i = 0; i < n && cap > 0; i++) {
        double fraction = min(1.0, (double)cap / arr[i].weight);
        double itemProfit = fraction * arr[i].value;

        cout << setw(12) << i + 1 << setw(12) << arr[i].weight << setw(12) << arr[i].value << setw(12) << fraction << setw(12) << itemProfit << endl;

        profit += itemProfit;
        cap -= fraction * arr[i].weight;
    }

    cout << "Maximum possible profit: " << profit << endl;
}

void knapsack(Item arr[], int cap, int n) {
    double profit = 0;
    sort(arr, arr + n, cmp);

    vector<string> headers = {"Item", "Weight", "Value", "Profit"};
    printTableHeader("0/1 Knapsack Greedy Approach", headers);

    for (int i = 0; i < n && cap > 0; i++) {
        if (cap >= arr[i].weight) {
            cout << setw(12) << i + 1 << setw(12) << arr[i].weight << setw(12) << arr[i].value << setw(12) << arr[i].value << endl;
            profit += arr[i].value;
            cap -= arr[i].weight;
        }
    }

    cout << "Maximum possible profit: " << profit << endl;
}

void knapsackdp(int val[], int wt[], int W, int n) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    printTableHeader("0/1 Knapsack Dynamic Programming Approach", {"Dynamic Programming Table"});
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            cout << setw(12) << dp[i][w];
        }
        cout << endl;
    }

    cout << "The maximum profit is: " << dp[n][W] << endl;
    cout << setw(12) << "ITEM" << setw(12) << "WEIGHT" << setw(12) << "PROFIT" << endl;

    int i = n, w = W;
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << setw(12) << i << setw(12) << wt[i - 1] << setw(12) << val[i - 1] << endl;
            w -= wt[i - 1];
        }
        i--;
    }
}

int main() {
    int choice;
    int n, cap;

    do {
        cout << "Menu:" << endl;
        cout << "1. Fractional Knapsack" << endl;
        cout << "2. 0/1 Knapsack Greedy Approach" << endl;
        cout << "3. 0/1 Knapsack Dynamic Programming Approach" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice != 4) {
            cout << "Enter number of items:" << endl;
            cin >> n;
            cout << "Enter capacity of bag:" << endl;
            cin >> cap;

            Item arr[n];
            int weight[n], profit[n];

            for (int i = 0; i < n; i++) {
                int v, w;
                cout << "Enter weight and value of item " << i + 1 << ":" << endl;
                cin >> w >> v;
                arr[i].weight = w;
                arr[i].value = v;
                weight[i] = w;
                profit[i] = v;
            }

            switch (choice) {
                case 1:
                    fractional_knapsack(arr, cap, n);
                    break;
                case 2:
                    knapsack(arr, cap, n);
                    break;
                case 3:
                    knapsackdp(profit, weight, cap, n);
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        }

    } while (choice != 4);

    return 0;
}
