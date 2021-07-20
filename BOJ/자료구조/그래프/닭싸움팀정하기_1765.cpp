#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define fasti ios_base::sync_with_stdio(false); cin.tie(0);
#define fastio ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define INF 1e9+7
#define pii pair<int, int>

typedef long long ll;
// typedef pair<int, int> pii;

using namespace std;

int N, M;
int Node[1001];
bool Check[1001];

vector<pii > graph[1001];
bool visited[1001];


int findtopnode(int a){
    if(Node[a] < 0) return a;
    return Node[a] = findtopnode(Node[a]);
}

bool Union_Node(int a, int b){
    a = findtopnode(a);
    b = findtopnode(b);
    
    if(a == b) return false;
    
    if(Node[a] < Node[b]){
        Node[a] += Node[b];
        Node[b] = a;
    }
    else{
        Node[b] += Node[a];
        Node[a] = b;
    }
    
    return true;
}

void input(){
    cin >> N >> M;
    char C;
    int p, q;
    for(int i = 0; i < M; i++){
        cin >> C >> p >> q;
        if(C == 'F'){
            graph[p].push_back({q, 1});
            graph[q].push_back({p, 1});
        }
        else if(C == 'E'){
            graph[p].push_back({q, 0});
            graph[q].push_back({p, 0});
        }
    }
    memset(Node, -1, sizeof(Node));
}

void dfs(int now, int depth, int ecnt, vector<int> &ord){
    ord.push_back(now);
    // cout << "now : " << now << "\n";
    if(depth > 0){
        int prev = ord[ord.size()-2];
        if(!ecnt){
            // cout << now << "," << prev << "  funion\n";
            Union_Node(now, prev);
        }
        else{
            if(ecnt == 2){
                // cout << now << "," << ord[ord.size()-2] << "  eunion\n";
                
                Union_Node(now, ord[ord.size()-3]);
                ecnt = 1;
                // return;
            }
        }
    }
    
    visited[now] = true;
    
    for(int i = 0; i < graph[now].size(); i++){
        int next = graph[now][i].first;
        int next_friend = graph[now][i].second;
        if(visited[next]) continue;
        
        dfs(next, depth+1, (next_friend? 0 : ecnt+1), ord);
    }
    ord.pop_back();
}

void solve(){
    vector<int> ord;
    for(int i = 1; i <= N; i++){
        memset(visited, 0, sizeof(visited));
        dfs(i, 0, 0, ord);
            // cout << "node : " << Node[i] << "\n";
    }
    int ans = 0;
    for(int i = 1; i <= N; i++){
        // cout << i << " :  " << Node[i] << "\n";
        if(Node[i] < 0){
            ans++;
        }
    }
    cout << ans;
}

int main(){
    input();
    solve();
    
    return 0;
}
