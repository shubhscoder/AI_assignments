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
ll cnt=0;
struct node
{
	ll val,child;
	v<node*>child_ptr;
	node(ll val,ll num_child)
	{
		this->val = val;
		child = num_child;
		child_ptr = v<node*>(child,0);
	}
};
ll num()
{
	srand(time(0)+cnt*60);
	ll sign = rand()%2;
	if(sign==0) sign=-1;
	cnt++;
	return sign*rand()%100;
}
ll return_random_number_for_branches()
{
	//return b instead of 2 if you want a tree with random branching factor at each height.
	//I have made a binary tree because it can be easily traced on paper and the results can be proven
	srand(time(0)+cnt*60);
	ll b = rand()%4;
	if(b==0) b=4;
	return 2;
}
node* new_node(ll val,ll child)
{
	node * n = new node(val,child);
	return n;
}
pair<ll,node*> raw_alpha_beta(ll dept,ll motive,ll alpha,ll beta)
{
	//keep changing dept to see varying results
	if(dept>=2)
	{
		ll val = num();
		return mp(val,new_node(val,0));
	}
	if(motive)
	{
		ll best = -inf,children = return_random_number_for_branches();
		node * p = new_node(best,children);
		f(0,i,children)
		{
			pair<ll,node*> child = raw_alpha_beta(dept+1,!motive,alpha,beta);
			p->child_ptr[i] = child.second;
			best = max(best,child.first);
			alpha = max(alpha,best);
			if(alpha>=beta) break;
		}
		p->val = best;
		return mp(best,p);
	}
	else
	{
		ll best = inf,children = return_random_number_for_branches();
		node * p = new_node(best,children);
		f(0,i,children)
		{
			pair<ll,node*> child = raw_alpha_beta(dept+1,!motive,alpha,beta);
			p->child_ptr[i] = child.second;
			best = min(best,child.first);
			beta = min(beta,best);
			if(alpha>=beta) break;
		}
		p->val = best;
		return mp(best,p);
	}
}

void bfs(node * root)
{
	queue<node*>q;
	q.push(root);
	while(!q.empty())
	{
		node * cur = q.front();
		q.pop();
		cout<<cur->child<<" "<<cur->val<<endl;
		f(0,i,cur->child)
		{
			if(cur->child_ptr[i]!=0)
			{
				q.push(cur->child_ptr[i]);
			}
		}
	}
}

int main()
{
	cnt = 0;
	node * root = raw_alpha_beta(0,1,-inf,inf).second;
	bfs(root);
} 