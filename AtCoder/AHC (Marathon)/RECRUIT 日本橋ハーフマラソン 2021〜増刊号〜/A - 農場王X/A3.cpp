#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#define rep(i, n) for (int i = 0; i < n; i++)
#define repn(i, n) for (int i = 1; i <= n; i++)
#define repr(e, x) for (auto& e : x)
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef pair<int, int> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

#define LOCALTEST 0

const int DR[4] = {1, 0, -1, 0};
const int DC[4] = {0, 1, 0, -1};

struct Vegetable {
    int r, c, s, e, v;
    Vegetable(int r_, int c_, int s_, int e_, int v_)
        : r(r_), c(c_), s(s_), e(e_), v(v_) {}
};

struct Action {
    vector<int> vs;

   private:
    explicit Action(const vector<int>& vs_) : vs(vs_) {}

   public:
    static Action pass() { return Action({-1}); }

    static Action purchase(int r, int c) { return Action({r, c}); }

    static Action move(int r1, int c1, int r2, int c2) {
        return Action({r1, c1, r2, c2});
    }
};

int N, M, T;
vector<vector<Vegetable>>
    veges_start;  // veges_start[i] : vegetables appear on day i
vector<vector<Vegetable>>
    veges_end;  // veges_end[i] : vegetables disappear on day i

struct Game {
    vector<vector<int>> has_machine;
    vector<vector<int>> vege_values;
    int num_machine;
    int next_price;
    int money;

    int max_num_machine;

    Game() : num_machine(0), next_price(1), money(1) {
        has_machine.assign(N, vector<int>(N, 0));
        vege_values.assign(N, vector<int>(N, 0));
    }

    Game(int _max_num_machine)
        : num_machine(0),
          next_price(1),
          money(1),
          max_num_machine(_max_num_machine) {
        has_machine.assign(N, vector<int>(N, 0));
        vege_values.assign(N, vector<int>(N, 0));
    }

    void purchase(int r, int c) {
        assert(!has_machine[r][c]);
        assert(next_price <= money);
        has_machine[r][c] = 1;
        money -= next_price;
        num_machine++;
        next_price = (num_machine + 1) * (num_machine + 1) * (num_machine + 1);
    }

    void move(int r1, int c1, int r2, int c2) {
        assert(has_machine[r1][c1]);
        has_machine[r1][c1] = 0;
        assert(!has_machine[r2][c2]);
        has_machine[r2][c2] = 1;
    }

    void simulate(int day, const Action& action) {
        // apply
        if (action.vs.size() == 2) {
            purchase(action.vs[0], action.vs[1]);
        } else if (action.vs.size() == 4) {
            move(action.vs[0], action.vs[1], action.vs[2], action.vs[3]);
        }
        // appear
        for (const Vegetable& vege : veges_start[day]) {
            vege_values[vege.r][vege.c] = vege.v;
        }
        // harvest
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (has_machine[i][j] && vege_values[i][j] > 0) {
                    money += vege_values[i][j] * count_connected_machines(i, j);
                    vege_values[i][j] = 0;
                }
            }
        }
        // disappear
        for (const Vegetable& vege : veges_end[day]) {
            vege_values[vege.r][vege.c] = 0;
        }
    }

    int count_connected_machines(int r, int c) {
        vector<pair<int, int>> queue = {{r, c}};
        vector<vector<int>> visited(N, vector<int>(N, 0));
        visited[r][c] = 1;
        int i = 0;
        while (i < queue.size()) {
            int cr = queue[i].first;
            int cc = queue[i].second;
            for (int dir = 0; dir < 4; dir++) {
                int nr = cr + DR[dir];
                int nc = cc + DC[dir];
                if (0 <= nr && nr < N && 0 <= nc && nc < N &&
                    has_machine[nr][nc] && !visited[nr][nc]) {
                    visited[nr][nc] = 1;
                    queue.push_back({nr, nc});
                }
            }
            i++;
        }
        return i;
    }

    Action select_next_action(int day, int span = 10) {
        if (num_machine >= max_num_machine || money < next_price) {
            // マシンを移動
            vector<vector<int>> sum_future_veges(N, vector<int>(N, 0));
            rep(i,N) rep(j,N){
                sum_future_veges[i][j]+=100*vege_values[i][j];
            }
            int max_day = min(T, day + num_machine);
            for (int i = day; i < max_day; i++) {
                for (const Vegetable& vege : veges_start[i]) {
                    sum_future_veges[vege.r][vege.c] += vege.v*100/(i-day+1);
                }
            }
            int min_sum = INF;
            int min_r = -1;
            int min_c = -1;
            int cnt = -1;
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    if (has_machine[r][c]) {
                        if(cnt==-1) cnt=count_connected_machines(r,c);
                        int fl=1;
                        has_machine[r][c]=0;
                        for (int dir = 0; dir < 4; dir++) {
                            int nr = r + DR[dir];
                            int nc = c + DC[dir];
                            if (0 <= nr && nr < N && 0 <= nc && nc < N &&
                                has_machine[nr][nc]) {
                                if(count_connected_machines(nr,nc)<cnt-1) fl=0;
                                break;
                            }
                        }
                        has_machine[r][c]=1;
                        if (fl && sum_future_veges[r][c] < min_sum) {
                            min_sum = sum_future_veges[r][c];
                            min_r = r;
                            min_c = c;
                        }
                    }
                }
            }
            has_machine[min_r][min_c]=0;
            int max_sum = 0;
            int max_r = -1;
            int max_c = -1;
            if(num_machine>1){
                for (int r = 0; r < N; r++) {
                    for (int c = 0; c < N; c++) {
                        if (!has_machine[r][c]) {
                            bool fl = false;
                            if (num_machine == 0) fl = true;
                            for (int dir = 0; dir < 4; dir++) {
                                int nr = r + DR[dir];
                                int nc = c + DC[dir];
                                if (0 <= nr && nr < N && 0 <= nc && nc < N &&
                                    has_machine[nr][nc]) {
                                    fl = true;
                                    break;
                                }
                            }
                            if (fl && max_sum < sum_future_veges[r][c]) {
                                max_sum = sum_future_veges[r][c];
                                max_r = r;
                                max_c = c;
                            }
                        }
                    }
                }
            }else{
                for (int r = 0; r < N; r++) {
                    for (int c = 0; c < N; c++) {
                        if (max_sum < sum_future_veges[r][c]) {
                            max_sum = sum_future_veges[r][c];
                            max_r = r;
                            max_c = c;
                        }
                    }
                }
            }
            has_machine[min_r][min_c]=1;
            if (max_sum > min_sum) {
                return Action::move(min_r, min_c, max_r, max_c);
            } else {
                has_machine[min_r][min_c]=1;
                return Action::pass();
            }
            return Action::pass();
        } else {
            // マシンを購入・設置
            vector<vector<int>> sum_future_veges(N, vector<int>(N, 0));
            int max_day = min(T, day + num_machine + 1);
            for (int i = day; i < max_day; i++) {
                for (const Vegetable& vege : veges_start[i]) {
                    sum_future_veges[vege.r][vege.c] += vege.v;
                }
            }
            int max_sum = 0;
            int max_r = -1;
            int max_c = -1;
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    if (has_machine[r][c]) {
                        continue;
                    }
                    bool fl = false;
                    if (num_machine == 0) fl = true;
                    for (int dir = 0; dir < 4; dir++) {
                        int nr = r + DR[dir];
                        int nc = c + DC[dir];
                        if (0 <= nr && nr < N && 0 <= nc && nc < N &&
                            has_machine[nr][nc]) {
                            fl = true;
                        }
                    }
                    if (fl && max_sum < sum_future_veges[r][c]) {
                        max_sum = sum_future_veges[r][c];
                        max_r = r;
                        max_c = c;
                    }
                }
            }
            if (max_sum > 0) {
                return Action::purchase(max_r, max_c);
            } else {
                return Action::pass();
            }
        }
    }
};

int main() {
    cin >> N >> M >> T;
    veges_start.resize(T);
    veges_end.resize(T);
    for (int i = 0; i < M; i++) {
        int r, c, s, e, v;
        cin >> r >> c >> s >> e >> v;
        Vegetable vege(r, c, s, e, v);
        veges_start[s].push_back(vege);
        veges_end[e].push_back(vege);
    }

    int score = 0;
    vector<Action> ans;
    Game best_game;
    for (int max_num_machine = 20; max_num_machine <= 60; max_num_machine++) {
        Game game(max_num_machine);
        vector<Action> actions;
        for (int day = 0; day < T; day++) {
            Action action = game.select_next_action(day);
            actions.push_back(action);
            game.simulate(day, action);
        }
        if (game.money > score) {
            score = game.money;
            ans = actions;
            best_game = game;
        }
    }

    for (const Action& action : ans) {
        for (int i = 0; i < action.vs.size(); i++) {
            cout << action.vs[i] << (i == action.vs.size() - 1 ? "\n" : " ");
        }
    }

#if LOCALTEST
    cout << "num_machine: " << best_game.num_machine << " , ";
    cout << "money: " << best_game.money << endl;
#endif
}