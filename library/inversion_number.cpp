#include<vector>
using namespace std;
typedef long long ll;

ll count_inv_num(vector<int>& vec) {
    int n = vec.size();
    if (n <= 1) return 0;

    ll res = 0;
    vector<int> b(vec.begin(), vec.begin() + n / 2);
    vector<int> c(vec.begin() + n / 2, vec.end());

    res += count_inv_num(b);
    res += count_inv_num(c);

    int i = 0, j = 0, k = 0;
    while (i < n) {
        if (j < b.size() && (k == c.size() || b[j] <= c[k])) {
            vec[i++] = b[j++];
        } else {
            res += n / 2 - j;
            vec[i++] = c[k++];
        }
    }

    return res;
}