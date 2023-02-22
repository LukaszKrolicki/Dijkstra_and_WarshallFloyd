# include <iostream>
using namespace std;

struct Edge{
    int s; //wierzcholek
    int t; //sasiad
    double w;        //waga krawêdzi
};

class Graph{
    private:
        double** Matrix;
        int n;                //liczba wêz³ów
        bool directed;
    public:
        Graph(int n, int m, Edge edges[], bool directed);    //tworzy graf w oparciu o pdan¹ listê krawêdzi z wagami
        void Dijkstra(int s);
        void wypisz();
        int szukaj(int* S, int* d, int n);
        void shortestPath(int s, int t, int* parent);
        void WarshallFloyd();
        friend ostream& operator<<(ostream& out, Graph& g);

};

Graph::Graph(int n, int m, Edge edges[], bool directed){
    this->n=n;
    this->directed=directed;

    Matrix = new double*[n];

    for(int i=0; i<n;i++){
        Matrix[i]= new double[n];
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j){
                Matrix[i][j]=0;
            }
            else{
                Matrix[i][j]=1234;
            }
        }
    }

    for(int i=0; i<m; i++){
        Matrix[edges[i].s][edges[i].t]=edges[i].w;

        if(directed==false){
            Matrix[edges[i].t][edges[i].s]=edges[i].w;
        }
    }
}

void Graph::wypisz(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<Matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

int znajdz(int* S, int* d, int n){
    int index=0;

    for(int i=0; i<n; i++){
        if(S[i]==0){
            index=i;
        }
    }

    for(int i=0; i<n; i++){
        if(S[i]==0 && d[i]<d[index]){
            index=i;
        }
    }

    return index;
}

void Graph::Dijkstra(int s){
    int parent[n];
    int d[n];
    int S[n]{};

    for(int i=0; i<n; i++){
        d[i]=2115;
    }

    d[s]=0;

    int u;
    for(int i=0; i<n; i++){
        u=znajdz(S,d,n);
        S[u]=1;
        for(int j=0; j<n; j++){
            if(Matrix[u][j]!=1234 && u!=j){
                if(d[j]>Matrix[u][j]+d[u]){
                    d[j]=Matrix[u][j]+d[u];
                    parent[j]=u;
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        cout<<d[i]<<" ";
    }

    cout<<endl;
    shortestPath(0,1,parent); //poczatek, koniec
}

void Graph::shortestPath(int s, int t, int* parent){
    int droga[n];
    int size=0;
    droga[size]=t;
    size++;
    int x=t;
    for(int i=0; i<n; i++){
        if(x!=s){
            x=parent[x];
            droga[size]=x;
            size++;
        }else{
            break;
        }
    }

    for(int i=size-1; i>=0; i--){
        cout<<droga[i]<<" ";
    }

}

void Graph::WarshallFloyd(){
    int d[n][n];
    int p[n][n];

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            d[i][j]=Matrix[i][j];
            if(Matrix[i][j]!=0 && Matrix[i][j]!=1234){
                p[i][j]=i;
            }
        }
    }

    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(d[i][j]>d[i][k]+d[k][j]){
                    d[i][j]=d[i][k]+d[k][j];
                    p[i][j]=p[k][j];
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<d[i][j]<<" ";
        }
    }

}

int main(){
    int n=6;
    int m=15;
    Edge edges[]={{0,4,6}, {0,5,1},{1,0,2}, {1,2,5}, {1,4,1}, {2,1,3}, {2,3,2}, {2,4,1}, {3,2,1}, {3,5,4}, {4,0,6}, {4,1,4}, {4,3,2}, {5,3,1}, {5,4,1}};
    Graph g(n,m,edges,true);
    g.wypisz();
    cout<<endl;
    //g.Dijkstra(0);
    g.WarshallFloyd();
}
