#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <typeinfo>

#include <vector>
#include <array>
#include <valarray>
#include <queue>
#include <stack>
#include <set>
#include <map>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include <cmath>
#include <climits>

using namespace std;

#define NO cout<<"NO"
#define YES cout<<"YES"
#define ln cout<<"\n"
#define INF 1000000010
#define INFL 1000000010000000010LL
#define all(x) (x).begin(),(x).end()
#define int long long
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)


struct Node {
    int val;
    int c;

    Node () {}

    Node (int _val, int _c) {
        val = _val,
                c = _c;
    }
};


struct seg_tree {
    vector<Node> tree;
    int sz;

    void init(int n) {
        sz = 1;
        while (sz < n) sz *= 2;
        tree.resize(2*sz-1);
    }

    void build(vector<int> &v, int x, int lx, int rx){
        if (rx == lx + 1) {
            if (lx < v.size()) {
                tree[x] = Node(v[lx], 1);
            }
            else {
                tree[x] = Node(INFL, 1);
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(v, x*2+1, lx, m);
        build(v, x*2+2, m, rx);
        combine(x, lx, rx);
    }
    void build(vector<int> &v) {
        init(v.size());
        build(v, 0, 0, sz);
    }

    void combine(int x, int lx, int rx) {
        if (rx == lx + 1) return;
        if (tree[x*2+1].val > tree[x*2+2].val) {
            tree[x] = tree[x*2+2];
        }
        else if (tree[x*2+1].val < tree[x*2+2].val) {
            tree[x] = tree[x*2+1];
        }
        else {
            tree[x] = tree[x*2+1];
            tree[x].c += tree[x*2+2].c;
        }
    }

    int get(int x, int lx, int rx, int l, int r) {
        if (l >= rx || lx >= r) return INFL;
        if (l <= lx && rx <= r) {
            res.push_back(tree[x]);
            return INFL;
        }
        int m = (lx + rx) / 2;
        get(x*2+1, lx, m, l, r);
        get(x*2+2, m, rx, l, r);
        return INFL;
    }
    vector<Node> res;
    pair<int, int> get(int l, int r) {
        res.clear();
        get(0, 0, sz, l, r);
        int mn = INFL;
        int c = 1;
        for(auto x: res) {
            if (x.val == mn) {
                c += x.c;
            }
            else if (x.val < mn) {
                mn = x.val;
                c = x.c;
            }
        }
        return {mn, c};
    }

    void update(int x, int lx, int rx, int i, int v) {
        if (rx-1 == lx) {
            tree[x] = Node(v, 1);
            return;
        }
        int m = (lx + rx) / 2;
        if (m > i) update(x*2+1, lx, m, i, v);
        else update(x*2+2, m, rx, i, v);
        combine(x, lx, rx);
    }

    void update(int i, int v) {
        update(0, 0, sz, i, v);
    }

};

void t_main() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for(int &x: v) cin >> x;
    seg_tree tr;
    tr.build(v);
    for(int i=0; i<m; i ++ ) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t==1) tr.update(l, r);
        else {
            pair<int, int> res = tr.get(l, r);
            cout << res.first << " " << res.second;
            ln;
        }
    }
}

signed main () {
    fast;
    int t = 1;
    //cin >> t;
    while (t--) {
        t_main();
    }
    return 0;
}
