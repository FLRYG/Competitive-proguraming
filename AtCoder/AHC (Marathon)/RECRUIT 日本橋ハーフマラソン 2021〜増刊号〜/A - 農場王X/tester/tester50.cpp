#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
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

#define LOCALTEST 1

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
};

int main(int argc, char* argv[]) {
    try {
        ifstream inp(argv[1]);
        ifstream out(argv[2]);
        ofstream res_main(argv[3], ios::app);
        ofstream tmp_score(argv[4], ios::app);
        int index = atoi(argv[5]);

        inp >> N >> M >> T;
        veges_start.resize(T);
        veges_end.resize(T);
        for (int i = 0; i < M; i++) {
            int r, c, s, e, v;
            inp >> r >> c >> s >> e >> v;
            Vegetable vege(r, c, s, e, v);
            veges_start[s].push_back(vege);
            veges_end[e].push_back(vege);
        }

        Game game;
        vector<Action> actions;
        for (int day = 0; day < T; day++) {
            vector<int> v;
            string line;
            getline(out, line);
            int i = 0, len = line.size();
            string s;
            while (i < len) {
                if (line[i] != ' ')
                    s += line[i];
                else {
                    v.push_back(stoi(s));
                    s.clear();
                }
                i++;
            }
            v.push_back(stoi(s));
            s.clear();
            if (v.size() == 1)
                actions.push_back(Action::pass());
            else if (v.size() == 2)
                actions.push_back(Action::purchase(v[0], v[1]));
            else
                actions.push_back(Action::move(v[0], v[1], v[2], v[3]));
            game.simulate(day, actions[day]);
        }
        res_main << "index = " << index << " : ";
        res_main << "num_machine = " << game.num_machine << " , ";
        res_main << "money = " << game.money << endl;

        tmp_score << game.money << endl;

        inp.close();
        out.close();
        res_main.close();
        tmp_score.close();

        return 0;
    } catch (logic_error e) {
        cerr << e.what() << endl;
        return 1;
    } catch (char* str) {
        cerr << "error: " << str << endl;
        return 1;
    }
    return 1;
}