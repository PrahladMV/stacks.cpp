/* Given an integer array arr[] of size N, find the maximum of the minimums for every window size in the given array.
I have solved this program using stack */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> findNextSmaller(vector<int>& arr, int n) {
    vector<int> result(n, -1);
    stack<int> s;

    for (int i = 0; i < n; i++) {
        while (!s.empty() && arr[s.top()] > arr[i]) {
            result[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }

    return result;
}

vector<int> findPrevSmaller(vector<int>& arr, int n) {
    vector<int> result(n, n);
    stack<int> s;

    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && arr[s.top()] > arr[i]) {
            result[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }

    return result;
}

int maxOfMinForEveryWindowSize(vector<int>& arr, int n) {
    vector<int> nextSmaller = findNextSmaller(arr, n);
    vector<int> prevSmaller = findPrevSmaller(arr, n);

    vector<int> windowSize(n, 0);

    for (int i = 0; i < n; i++) {
        int window = nextSmaller[i] - prevSmaller[i] - 1;
        windowSize[window] = max(windowSize[window], arr[i]);
    }

    for (int i = n - 2; i >= 0; i--) {
        windowSize[i] = max(windowSize[i], windowSize[i + 1]);
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        result += windowSize[i];
    }

    return result;
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int answer = maxOfMinForEveryWindowSize(arr, n);

    cout << "Maximum of the minimums for every window size: " << answer << endl;

    return 0;
}
