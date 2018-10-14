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
#define max_iterations 1000000
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

class game
{
    ll n; 
    v<vi>initial_state,final_state;
    map<v<vi>,v<vi> >trace_game;
    set<v<vi> >visited; //matrix,height
    set<pair<pi,v<vi> > >st; //height,cost,
    map<ll,pi>num_pos;//position of number in final_state
public:
    game()
    {
        cout<<"Enter size of the board"<<endl;
        cin>>n;
        initial_state = v<vi>(n,vi(n));
        final_state = v<vi>(n,vi(n));
        cout<<"Enter the initial_state"<<endl;
        f(0,i,n) f(0,j,n) cin>>initial_state[i][j];
        cout<<"Enter goal state"<<endl;
        f(0,i,n) f(0,j,n) {cin>>final_state[i][j];num_pos[final_state[i][j]] = mp(i,j);}
    }
    bool isvalid(ll i,ll j)
    {
        if(i<0 or j<0 or i>=n or j>=n) return false;
        return true;
    }
    void print_grid(v<vi>game_state)
    {
        f(0,i,n)
        {
            f(0,j,n)
            {
                cout<<game_state[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    pi zero_pos(v<vi>game_state)
    {
        f(0,i,n) f(0,j,n) if(game_state[i][j]==0) return mp(i,j);
    }
    pii move_generator(v<vi>game_state)
    {
        pii moves;
        f(0,i,n)
        {
            f(0,j,n)
            {
                if(game_state[i][j] == 0)
                {
                    if(isvalid(i-1,j)) moves.pb(mp(i-1,j));
                    if(isvalid(i+1,j)) moves.pb(mp(i+1,j));
                    if(isvalid(i,j-1)) moves.pb(mp(i,j-1));
                    if(isvalid(i,j+1)) moves.pb(mp(i,j+1));
                }
            }
        }
        return moves;
    }
    ll airplane_distance(v<vi>game_state)
    {
        ll cost = 0;
        f(0,i,n)
        {
            f(0,j,n)
            {
                pi pos = num_pos[game_state[i][j]];
                cost+=abs(i-pos.first)+abs(j-pos.second);
            }
        }
        return cost;
    }
    bool is_destination(v<vi>game_state)
    {
        f(0,i,n)
        {
            f(0,j,n) 
            {
                if(game_state[i][j]!=final_state[i][j]) return false;
            }
        }
        return true;
    }
    void game_play()
    {
        ll iterations = 0;
        st.insert(mp(mp(0,0),initial_state));
        trace_game[initial_state] = initial_state;
        while(!st.empty())
        {
            pair<pi,v<vi> >current_node = *(st.begin());
            st.erase(st.begin());
            if(visited.find(current_node.second)!=visited.end()) continue;
            visited.insert(current_node.second);
            if(is_destination(current_node.second))
            {
                print_grid(current_node.second);
                cout<<"Moves required: "<<current_node.first.second<<endl;
                return;
            }
            pii moves = move_generator(current_node.second);
            pi pos_zero = zero_pos(current_node.second);
            f(0,i,moves.size())
            {
                v<vi>duplicate = current_node.second;
                swap(duplicate[pos_zero.first][pos_zero.second],duplicate[moves[i].first][moves[i].second]);
                if(visited.find(duplicate)==visited.end())
                {
                    ll height = current_node.first.second;
                    trace_game[duplicate] = current_node.second;
                    st.insert(mp(mp(height+1+airplane_distance(duplicate),height+1),duplicate));
                } 
            }
            iterations++;
            if(iterations > max_iterations) 
            {
                cout<<"Probably not solvable"<<endl;
                return;
            }
        }
    }
    bool are_equal(v<vi>a,v<vi>b)
    {
        f(0,i,n)
        {
            f(0,j,n)
            {
                if(a[i][j]!=b[i][j]) return false;
            }
        }
        return true;
    }
    void print_move_sequence()
    {
        v<v<vi> >move_sequence;
        v<vi>cur = final_state;
        while(!are_equal(cur,trace_game[cur]))
        {
            move_sequence.pb(cur);
            cur = trace_game[cur];
        }
        move_sequence.pb(initial_state);
        for(ll i=move_sequence.size()-1;i>-1;i--)
        {
            print_grid(move_sequence[i]);
        }
    }
};
int main()
{
    game khelo;
    cout<<endl<<endl;
    khelo.game_play();
    khelo.print_move_sequence();
} 