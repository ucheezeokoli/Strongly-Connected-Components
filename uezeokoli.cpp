#include <iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

int global_time = 0;
list<int> scc_id; // push/pop_front

//colors
enum {WHITE = 0, GRAY, BLACK};

//flags
enum {SCC = 10, SEARCH, ADJ, SCCID};

struct Node{
    int time_d, time_f;
    int color;
    int prev;
    int sccid;
    vector<int> adj;

    Node(): time_d(0), time_f(0), color(WHITE), prev(0), sccid(0){}

};

//prototypes
void dbg_printAdj(Node** G, int V);
void dbg_printGraph(Node** G, int vertices, int dbg_flag);
void dbg_printSCCID(Node** G, int V);
void buildGraph(Node**, int V);
void DFS(Node** G, int vertices, int flag, int* root);
void visit(Node** G, int v, int* sccid);



int main(){

    int i, j;
    int V, E, v, u;
    Node** G;
    Node** GT;
    int* root = nullptr;
    int rooted = 0;
    root = &rooted;

    // build empty graphs from input vertices
    cin >> V;
    // buildGraph(G, V);
    // buildGraph(GT, V); 
    G = new Node*[V];
    for(i = 0; i < V; i++){
        G[i] = new Node();
    }   
    GT = new Node*[V];
    for(i = 0; i < V; i++){
        GT[i] = new Node();
    }  

    // populate graph from input edges
    cin >> E;
    for(i = 0; i < E; i++){
        cin >> v;
        cin >> u;

        //build graph and transposed graph at same time
        (*G[v]).adj.push_back(u);
        (*GT[u]).adj.push_back(v);
    }

    //first pass of DFS
    //  while pushing forest(s) to a stack
    DFS(G, V, SEARCH, root);

    //second pass of DFS in reverse time order (pop from stack)
    //  building a component from each forest
    DFS(GT, V, SCC, root);
    
    dbg_printGraph(GT, V, SCCID);

    //free allocated memory
    for(i = 0; i < V; i++){
        delete G[i];
        delete GT[i];
    }

    delete G;
    delete GT;

    return 0;
}

void DFS(Node** G, int vertices, int flag, int* root){
    int i;
    if(flag == SEARCH){
        for(i = 0; i < vertices; i++){
            if((*G[i]).color == WHITE){
                *root = i;
                visit(G, i, root);
            }
        }
    }

    else if(flag == SCC){
        while(!scc_id.empty()){
            i = scc_id.front();
            scc_id.pop_front();
            if((*G[i]).color == WHITE){
                *root = i;
                visit(G, i, root);
            }
        }
    }
}

void visit(Node** G, int v, int* sccid){
    global_time++;
    (*G[v]).time_d = global_time;
    (*G[v]).color = GRAY;

    if(*sccid > v){
        *sccid = v;
    }

    for(vector<int>::iterator it = (*G[v]).adj.begin(); it != (*G[v]).adj.end(); it++){
        if((*G[*it]).color == WHITE){
            (*G[*it]).prev = v;
            visit(G, *it, sccid);
        }
     }
    
    (*G[v]).color = BLACK;
    global_time++;
    (*G[v]).time_f = global_time;
    (*G[v]).sccid = *sccid;
    scc_id.push_front(v);
}

void dbg_printAdj(Node** G, int V){
     for(vector<int>::iterator it = (*G[V]).adj.begin(); it != (*G[V]).adj.end(); it++){
        cout << *it << ", ";
     }
     cout << endl;
}

void dbg_printSCCID(Node** G, int V){
    cout << (*G[V]).sccid << endl;
}

void dbg_printGraph(Node** G, int vertices, int dbg_flag){
    if(dbg_flag == ADJ){
        for(int i = 0; i < vertices; i++){
            cout << "V = " << i << "; connected to: ";
            dbg_printAdj(G, i);
        }
    }

    if(dbg_flag == SCCID){
        for(int i = 0; i < vertices; i++){
            dbg_printSCCID(G, i);
        }
    }
}

void buildGraph(Node** G, int V){
    G = new Node*[V];
    for(int i = 0; i < V; i++){
        G[i] = new Node();
    } 

}


