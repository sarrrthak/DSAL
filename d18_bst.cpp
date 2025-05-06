// d18

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int optimalBST(vector<int> &keys, vector<int> &prob, int n)
{
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> cost(n, vector<int>(n, 0));

    // Base case: cost and dp for single keys
    for (int i = 0; i < n; i++)
    {
        dp[i][i] = prob[i];
        cost[i][i] = prob[i];
    }

    // Build up cost[i][j]
    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1;

            // calculate cost[i][j] = sum of prob[i] to prob[j]
            cost[i][j] = 0;
            for (int k = i; k <= j; k++)
                cost[i][j] += prob[k];

            dp[i][j] = INT_MAX;

            for (int r = i; r <= j; r++)
            {
                int left = (r > i) ? dp[i][r - 1] : 0;
                int right = (r < j) ? dp[r + 1][j] : 0;
                int total = left + right + cost[i][j];

                dp[i][j] = min(dp[i][j], total);
            }
        }
    }

    return dp[0][n - 1];
}

int main()
{
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    vector<int> keys(n);
    vector<int> prob(n);

    cout << "Enter the keys: ";
    for (int i = 0; i < n; i++)
    {
        cin >> keys[i];
    }

    cout << "Enter the probabilities: ";
    for (int i = 0; i < n; i++)
    {
        cin >> prob[i];
    }

    int result = optimalBST(keys, prob, n);
    cout << "The minimum search cost is: " << result << endl;

    return 0;
}
