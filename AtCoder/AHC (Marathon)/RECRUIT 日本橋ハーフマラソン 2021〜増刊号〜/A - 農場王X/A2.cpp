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
typedef pair<int, int> P;
typedef pair<int, P> IP;
typedef pair<P, P> PP;
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
    vector<vector<queue<Vegetable>>> next_vege;
    vector<vector<int>> evaluation;
    int core_r;
    int core_c;
    vector<P> route;

    Game() : Game(10) {}

    Game(int _max_num_machine)
        : num_machine(0),
          next_price(1),
          money(1),
          max_num_machine(_max_num_machine) {
        has_machine.assign(N, vector<int>(N, 0));
        vege_values.assign(N, vector<int>(N, 0));
        next_vege.assign(N, vector<queue<Vegetable>>(N));
        for (int day = 0; day < T; day++) {
            for (const Vegetable& vege : veges_start[day]) {
                next_vege[vege.r][vege.c].push(vege);
            }
        }
        evaluation.assign(N, vector<int>(N, 0.0));
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
                    next_vege[i][j].pop();
                }
            }
        }
        // disappear
        for (const Vegetable& vege : veges_end[day]) {
            vege_values[vege.r][vege.c] = 0;
            if (day == next_vege[vege.r][vege.c].front().e)
                next_vege[vege.r][vege.c].pop();
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

    Action select_next_action(int day) {
        if (day == 0) {
            int r = 7, c = 7, v = 0;
            for (Vegetable& vege : veges_start[day]) {
                if (v < vege.v) {
                    r = vege.r;
                    c = vege.c;
                    v = vege.v;
                }
            }
            core_r = r;
            core_c = c;
            return Action::purchase(r, c);
        }

        if (num_machine == 1) {
            if (money < next_price) {
                // move
                int tmp_r = core_r;
                int tmp_c = core_c;
                int max_v = -1;
                core_r = -1;
                core_c = -1;
                rep(i, N) rep(j, N) {
                    if (next_vege[i][j].empty()) continue;
                    Vegetable& vege = next_vege[i][j].front();
                    if (vege.s <= day && day <= vege.e && max_v < vege.v) {
                        max_v = vege.v;
                        core_r = i;
                        core_c = j;
                    }
                }
                assert(max_v != -1);
                assert(core_r != -1);
                assert(core_c != -1);
                if (tmp_r == core_r && tmp_c == core_c) return Action::pass();
                return Action::move(tmp_r, tmp_c, core_r, core_c);
            } else {
                // purchase
                // if(tmp_r==core_r && tmp_c==core_c){
                //     if(core_c+1<N) return Action::purchase(core_r,core_c+1);
                //     else return Action::purchase(core_r,core_c-1);
                // }else{
                //     rep(dir,4){
                //         if(tmp_r+DR[dir]==core_r && tmp_c+DC[dir]==core_c){
                //             return Action::purchase(core_r,core_c);
                //         }
                //     }
                //     route.push_back({core_r,core_c});
                //     if(core_c+1<N) return Action::purchase(core_r,core_c+1);
                //     else return Action::purchase(core_r,core_c-1);
                // }
                if (core_c + 1 < N)
                    return Action::purchase(core_r, core_c + 1);
                else
                    return Action::purchase(core_r, core_c - 1);
            }
            return Action::pass();
        }

        // if(num_machine==2){
        //     if(money<next_price){
        //         // move
        //         if(route.size()>0){
        //             P p=*(route.end()-1);
        //             route.pop_back();
        //             rep(i,N) rep(j,N){
        //                 if(abs(p.first-i)+abs(p.second-j)>1 &&
        //                 has_machine[i][j]){
        //                     return Action::move(i,j,p.first,p.second);
        //                 }
        //             }
        //         }else{
        //             int tmp_r=core_r;
        //             int tmp_c=core_c;
        //             int max_v=-1;
        //             core_r=-1;
        //             core_c=-1;
        //             rep(i,N) rep(j,N){
        //                 if(max_v<vege_values[i][j]){
        //                     max_v=vege_values[i][j];
        //                     core_r=i;
        //                     core_c=j;
        //                 }
        //             }
        //         }
        //     }else{

        //     }
        //     return Action::pass();
        // }

        if (route.size() == 0) {
            // cout<<"  ";
            // rep(i,N) cout<<i%10<<' ';
            // cout<<endl;
            // rep(i,N){
            //     cout<<i%10<<' ';
            //     rep(j,N) cout<<has_machine[i][j]<<' ';
            //     cout<<endl;
            // }

            // cout<<"core: "<<core_r<<' '<<core_c<<endl;
            vector<vector<int>> dist(N, vector<int>(N, INF));
            priority_queue<IP,vector<IP>,greater<IP>> que;
            que.push({0, {core_r, core_c}});
            while (!que.empty()) {
                IP ip = que.top();
                que.pop();
                int d = ip.first;
                int cr = ip.second.first;
                int cc = ip.second.second;
                if (dist[cr][cc] <= d) continue;
                dist[cr][cc] = d;
                for (int dir = 0; dir < 4; dir++) {
                    int nr = cr + DR[dir];
                    int nc = cc + DC[dir];
                    if (0 <= nr && nr < N && 0 <= nc && nc < N) {
                        if (has_machine[nr][nc])
                            que.push({d, {nr, nc}});
                        else
                            que.push({d + 1, {nr, nc}});
                    }
                }
            }
            // cout<<"dist: OK"<<endl;

            int max_v = -1;
            core_r = -1;
            core_c = -1;
            rep(i, N) rep(j, N) {
                if (has_machine[i][j]) {
                    evaluation[i][j] = vege_values[i][j];
                } else if (!next_vege[i][j].empty()) {
                    Vegetable& vege = next_vege[i][j].front();
                    if (dist[i][j] <= vege.e - day) {
                        evaluation[i][j] = vege.v;
                    }
                }
                if (evaluation[i][j] > max_v) {
                    max_v = evaluation[i][j];
                    core_r = i;
                    core_c = j;
                }
            }
            assert(core_r != -1);
            assert(core_c != -1);
            // cout<<"core: "<<core_r<<' '<<core_c<<endl;
            // cout<<"has?: "<<has_machine[core_r][core_c]<<endl;

            int tmp_r = core_r;
            int tmp_c = core_c;
            int len = dist[core_r][core_c];
            rep(i, len) {
                // cout << tmp_r << ' ' << tmp_c << endl;
                route.push_back({tmp_r, tmp_c});
                int tmp_v = -1, d = -1;
                rep(dir, 4) {
                    int nr = tmp_r + DR[dir];
                    int nc = tmp_c + DC[dir];
                    if (0 <= nr && nr < N && 0 <= nc && nc < N &&
                        dist[nr][nc] + 1 == dist[tmp_r][tmp_c] &&
                        tmp_v < evaluation[nr][nc]) {
                        d = dir;
                        tmp_v = evaluation[nr][nc];
                    }
                }
                assert(d != -1);
                tmp_r += DR[d];
                tmp_c += DC[d];
            }
        }

        if (route.size() == 0) {
            return Action::pass();
        }

        if (num_machine >= max_num_machine || money < next_price) {
            // マシンを移動
            double min_v = INF;
            int min_r = -1;
            int min_c = -1;
            int cnt = -1;
            P p = *(route.end() - 1);
            route.pop_back();
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    if (abs(p.first - r) + abs(p.second - c) > 1 &&
                        has_machine[r][c]) {
                        if (cnt == -1) cnt = count_connected_machines(r, c);
                        int fl = 1;
                        has_machine[r][c] = 0;
                        for (int dir = 0; dir < 4; dir++) {
                            int nr = r + DR[dir];
                            int nc = c + DC[dir];
                            if (0 <= nr && nr < N && 0 <= nc && nc < N &&
                                has_machine[nr][nc]) {
                                if (count_connected_machines(nr, nc) < cnt - 1)
                                    fl = 0;
                                break;
                            }
                        }
                        has_machine[r][c] = 1;
                        if (fl && evaluation[r][c] < min_v) {
                            min_v = evaluation[r][c];
                            min_r = r;
                            min_c = c;
                        }
                    }
                }
            }
            assert(min_v != INF);
            assert(min_r != -1);
            assert(min_c != -1);
            return Action::move(min_r, min_c, p.first, p.second);
        } else {
            // マシンを購入・設置
            P p = *(route.end() - 1);
            route.pop_back();
            return Action::purchase(p.first, p.second);
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
    for (int max_num_machine = 30; max_num_machine <= 60; max_num_machine++) {
        Game game(max_num_machine);
        vector<Action> actions;
        for (int day = 0; day < T; day++) {
            // cout << "day" << day << endl;
            Action action = game.select_next_action(day);
            // cout << "action" << endl;
            actions.push_back(action);
            game.simulate(day, action);
            // cout << "simulate" << endl;
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