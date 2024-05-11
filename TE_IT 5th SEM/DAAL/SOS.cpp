#include<bits/stdc++.h>
using namespace std;

bool ok = false;

void f(int i, int n, int arr[], int targetsum, vector<int>& subset) {
    
    if (targetsum == 0) {
        ok = true;
        cout << "[";
        for (int i = 0; i < subset.size() - 1; i++) {
            cout << subset[i] << ",";
        }
        cout << subset[subset.size() - 1];
        cout << "]" << endl;
        return;
    }

    if (i == n) {
        return;
    }
   
    // Include
    if (arr[i] <= targetsum) {
        subset.push_back(arr[i]);
        f(i + 1, n, arr, targetsum - arr[i], subset);
        subset.pop_back();
    }

    // Not Include
    f(i + 1, n, arr, targetsum, subset);
}

int main() {
    int n;
    cout << "Enter the length of Array: ";
    cin >> n;
    int arr[n];
    cout << "Enter the elements of Array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int targetsum;
    cout << "Enter the Target Sum: ";
    cin >> targetsum;
    vector<int> subset;

    f(0, n, arr, targetsum, subset);

    if (!ok) {
        cout << "No subset found with the given Target Sum." << endl;
    }

    return 0;
}
