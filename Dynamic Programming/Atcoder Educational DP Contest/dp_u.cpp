
// Problem : U - Grouping
// Contest : AtCoder - Educational DP Contest
// URL : https://atcoder.jp/contests/dp/tasks/dp_u
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

// Code by : Abhishek Tiwari @devil_within
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define all(v) (v).begin(), (v).end()
#define mp make_pair
#define pb push_back
#define pf push_front
#define ff first
#define ss second
#define lcm(a, b) ((a) * (b)) / __gcd(a, b)
#define vt vector<int>
#define pii pair<int, int>
#define ar array
const long double PI = acos(-1);
using namespace std;

using namespace __gnu_pbds;
template <class T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long int;
using ld = long double;
// using int = int64_t;

/*******************************************************************************************/
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    os << "]\n";
    return os;
}
template <typename T> ostream &operator<<(ostream &os, const set<T> &v)
{
    os << "{";
    for (auto it : v)
    {
        os << it;
        if (it != *v.rbegin())
            os << ", ";
    }
    os << "}\n";
    return os;
}
template <typename T, typename S> ostream &operator<<(ostream &os, const map<T, S> &v)
{
    os << "{";
    for (auto it : v)
    {
        os << "(" << it.first << " : " << it.second << ")";
        if (it != *v.rbegin())
            os << ", ";
    }
    os << "}\n";
    return os;
}
template <typename T, typename S> ostream &operator<<(ostream &os, const pair<T, S> &v)
{
    os << "(";
    os << v.first << ", " << v.second << ")";
    return os;
}
template <typename T> inline istream &operator>>(istream &in, vector<T> &a)
{
    for (auto &x : a)
        in >> x;
    return in;
}
/*******************************************************************************************/
// N dimensional Vector, Vec<n , int>
template <int D, typename T> struct Vec : public vector<Vec<D - 1, T>>
{
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template <typename... Args> Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...))
    {
    }
};
template <typename T> struct Vec<1, T> : public vector<T>
{
    Vec(int n = 0, const T &val = T()) : vector<T>(n, val)
    {
    }
};
/*******************************************************************************************/
int fpow(int x, int y, int p);

mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b)
{
    return uniform_int_distribution<ll>(a, b)(mt_rng);
}

const int d4i[4] = {-1, 0, 1, 0}, d4j[4] = {0, 1, 0, -1};
const int d8i[8] = {-1, -1, 0, 1, 1, 1, 0, -1}, d8j[8] = {0, 1, 1, 1, 0, -1, -1, -1};

const ll INF = LONG_LONG_MAX;
const int MAXN = 2e5, MAXM = 2e5;
const int M = 1e9 + 7;

const int MXN = 16;
const int MASK = 1ll << (MXN + 1);
int N;
ll score[MASK];
ll dp[MASK];
void rec(int idx, vector< int > &left, int mask , int group) {
	if(idx == left.size() ) {
		dp[mask] = max(dp[mask] , score[group] + dp[ mask ^ group ] );
		return;
	}
	rec(idx + 1 , left , mask , group); // dont take idx in group
	rec(idx + 1 , left , mask , group ^ (1ll << left[idx]) ); // take idx in group
}

void solve()
{
	cin >> N;
	Vec< 2 , ll > a( N , N );
	cin >> a;
    // Calculate score for any group
    for(int mask = 0; mask < MASK; ++mask ) {
    	for(int i = 0; i < N; ++i) {
    		for(int j = i + 1; j < N; ++j) {
    			if ( (mask & (1ll << i))  && (mask & (1ll << j )) ) 
    				score[mask] += a[i][j];
    		}
    	}
    }
    // Complexity : 3 ^ n 
    // For each mask : 
    	// Generate all possible submasks of left ones in this mask
    	// For submask in all submasks : 
				// This submask is 1 group ie. ans = score[submask]
				// For everything else other than this submask ie. mask ^ subset,
				 // ans is already computed dp[ mask ^ subset ] 
				// dp[ mask ] = max( dp[max] , score[subset] + dp[mask ^ submask] )
    for(int mask = 0 ; mask < MASK; ++mask ) {
    	vector< int > left;
    	for(int i = 0;  i < N; ++i) 
    		if(mask & (1ll << i ) ) 
    			left.pb(i);
    	rec(0 , left , mask , 0);
    }
    cout << dp[MASK -1 ] << "\n";
}

signed main()
{
#ifndef ONLINE_JUDGE
// freopen("input.txt" , "r" , stdin);freopen("output.txt" , "w" ,
// stdout);freopen("error.txt" , "w" , stderr);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // cout << fixed << setprecision(12);
    int T = 1;
    // cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        solve();
        // cout << "Case #"<<tc<<": \n";
    }
}

// Functions
ll fpow(ll x, ll y, ll p = LONG_LONG_MAX)
{
    ll res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}




