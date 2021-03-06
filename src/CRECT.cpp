#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef unsigned long long ull;

#define X first
#define Y second
#define pb push_back
#define mp make_pair
#define ep emplace_back
#define EL printf("\n")
#define sz(A) (int) A.size()
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FOD(i,r,l) for (int i=r;i>=l;i--)
#define fillchar(a,x) memset(a, x, sizeof (a))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

const int N = 405;
int n, m, L[N], h[N];
char a[N][N];
ll  ans, F[N], S1[260], S2[260][260];

ll solve(vector<char> f) {
	ll ans = 0ll;
	FOR(j,1,m) h[j] = L[j] = F[j] = 0;
	FOR(i,1,n) {
		FOR(j,1,m) {
			int ok = 0;
			for (auto ch : f) if (a[i][j] == ch) ok = 1;
			h[j] = ok ? h[j] + 1 : 0;
		}

		stack<int> st;
		FOR(j,1,m) {
			while (! st.empty() && h[j] <= h[st.top()]) st.pop();
			L[j] = st.empty() ? 1 : st.top() + 1;
			st.push(j);
		}

		FOR(j,1,m) {
			int k = L[j] - 1;
			F[j] = (ll) h[j] * (j - k) + F[k];
			ans += F[j];
		}
	}
	return ans;
}

int main() {
//  freopen("INP.TXT", "r", stdin);
//  freopen("OUT.TXT", "w", stdout);

	scanf("%d%d\n", &n,&m);
	FOR(i,1,n) scanf("%s\n", a[i]+1);

	for(char q='A'; q<='E'; q++) {
		vector<char> f;
		f.pb(q);
		S1[q] = solve(f);
	}

	for(char q='A'; q<='E'; q++)
		for(char w=q+1; w<='E'; w++) {
			vector<char> f;
			f.pb(q);
			f.pb(w);
			S2[q][w] = solve(f) - S1[q] - S1[w];
		}

	for(char q='A'; q<='E'; q++) {
		for(char w=q+1; w<='E'; w++) {
			for(char e=w+1; e<='E'; e++) {
				vector<char> f;
				f.pb(q);
				f.pb(w);
				f.pb(e);
				ans += solve(f) - S1[q] - S1[w] - S1[e] - S2[q][w] - S2[w][e] - S2[q][e];
			}
		}
	}

	cout << ans;

	return 0;
}
