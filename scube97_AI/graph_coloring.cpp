/*
    Author : Shubham Sangamnerkar,PICT,Pune
    Roll   : 4351
    Div    : BE-3
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pi pair<ll,ll>
#define pii vector<pair<ll,ll> >
#define v vector
#define vi vector<ll>
#define f(a,i,n) for(int i=a;i<n;i++)
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define MAX 1000001
#define all(x) x.begin(),x.end()
const ll inf=(ll) 1e18;

ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}
ll spf[MAX+1];
void sieve()//complexity = approx 3*10^6
{
    f(1,i,MAX) {spf[i]=i;} 
    for(ll i=2;i<MAX;i+=2){spf[i]=2;}
    for(ll i=3;i<MAX;i+=2)
    {
        if(spf[i]==i) //if i is prime mark its multiples with spf as i
        {
            for(ll j=i*i;j<MAX;j+=i)
            {
                spf[j]=min(i,(ll)spf[j]);
            }
        }
    }
}
class graph
{
	ll n,edges,m;
	//n : number of vertices
	//edges : number of edges 
	//m : colors constraint
	v<vi>adj;
	vi color;
public:
	graph()
	{
		cout<<"Number of vertices"<<endl;
		cin>>n;
		cout<<"Number of edges"<<endl;
		cin>>edges;
		cout<<"Maximum number of colors that can be used"<<endl;
		cin>>m;
		adj = v<vi>(n+1);//adjacency_list
		color = vi(n,-1);//color of i is the color of the ith vertex
		input_graph();
	}
	void input_graph()
	{
		ll x,y;
		cout<<"Enter the edges(1 based indexing)"<<endl;
		f(0,i,edges)
		{
			cin>>x>>y;
			x--;y--;
			adj[x].pb(y);
			adj[y].pb(x);
		}
	}
	bool valid(ll cur,ll color_assigned)
	{
		f(0,i,adj[cur].size())
		{
			if(color[adj[cur][i]]==color_assigned) return false;
		}
		return true;
	}
	bool color_graph(ll cur)
	{
		if(cur==n) return true;
		f(0,i,m)
		{
			if(valid(cur,i))
			{
				color[cur] = i;
				if(color_graph(cur+1))
				{
					return true;
				}
				//backtrack
				color[cur] = -1;
			}
		}
		//if none of the colors assigned satisfy the constraints
		return false;
	}
	void print_sol()
	{
		f(0,i,n) cout<<color[i]<<" ";cout<<endl;
	}
};
int main()
{
	graph banao;
	if(banao.color_graph(0))
	{
		banao.print_sol();
	}
	else
	{
		cout<<"No solution\n";
	}
} 

/*
Sample Input1:
n:4
edges:6
max colors:3
graph:
1 2
1 3
1 4
2 3
2 4
3 4

Sample Input2:
Sample Input1:
n:4
edges:6
max colors:4
graph:
1 2
1 3
1 4
2 3
2 4
3 4
*/