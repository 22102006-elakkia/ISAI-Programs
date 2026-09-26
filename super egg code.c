int dp[101][100005];

int solve(int k, int n) {
    if (n == 0 || n == 1) return n;
    if (k == 1) return n;
    if (dp[k][n] != -1) return dp[k][n];

    int ans = INT_MAX;
    int low = 1, high = n;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        int broken = solve(k - 1, mid - 1);
        int not_broken = solve(k, n - mid);

        int worst = 1 + (broken > not_broken ? broken : not_broken);
        ans = (worst < ans) ? worst : ans;

        if (broken > not_broken) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return dp[k][n] = ans;
}
int superEggDrop(int k, int n) {
    memset(dp, -1, sizeof(dp));
    return solve(k, n);
}