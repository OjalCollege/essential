#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve the 0/1 Knapsack problem
int knapsack(int capacity, vector<int> &weights, vector<int> &values, int n)
{
    // Create a DP table to store maximum values for each capacity
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Build the table in a bottom-up manner
    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= capacity; w++)
        {
            if (weights[i - 1] <= w)
            { // Check if item can fit in the knapsack
                // Take the maximum of including or excluding the item
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w]; // Exclude the item
            }
        }
    }

    // The maximum value for the given capacity
    return dp[n][capacity];
}

int main()
{
    int capacity = 50;
    vector<int> weights = {10, 20, 30};
    vector<int> values = {60, 100, 120};
    int n = weights.size();

    int maxValue = knapsack(capacity, weights, values, n);

    cout << "Maximum value we can obtain = " << maxValue << endl;

    return 0;
}
