/*
*
*/
#include <iostream>
#include <list>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void FoundMininterpolation();
void Game();
void FindMinWay();
void  SchoolRun();

//201712-1
void FoundMininterpolation() {
    int n;
    int a[1005];
    std::cin>>n;
    for(int i=0; i<n; i++) {
        std::cin>>a[i];
    }

    sort(a,a+n);
    int ans=a[1]-a[0];
    for(int i= 2; i<n; i++) {
        if(a[i]-a[i-1]<ans)
            ans=a[i]-a[i-1];
    }
    cout<<ans;
}
//201712-2
void Game() {
    int n,k;
    cin>>n>>k;
    queue<int> childqueue;
    for(int i=1; i<=n; i++) {
        childqueue.push(i);
    }
    for(int counter=1;; counter++) {
        if(counter%k==0||counter%10==k) {
            childqueue.pop();
            if(childqueue.size()==1) {
                cout<<childqueue.front();
                break;
            }
            continue;
        }
        childqueue.push(childqueue.front());
        childqueue.pop();

    }
}
//201712-4
#define MaxVexter 5000
#define Infinity 10000000000
#define StartVexterHNH (-1)
typedef long long ll;
typedef int Vexter;

class graphNode {
public:
    Vexter link_vexter;
    ll weight;
    int type;
    graphNode(Vexter vexter,ll weig,int ty) {
        link_vexter=vexter;
        weight=weig;
        type=ty;
    }
};
class PathNode {
public:
    Vexter thisVexter;
    Vexter path;
    ll distance;
    ll short_way_distance;
    int path_type;
    PathNode() {

    };
    PathNode(Vexter vertex,Vexter last,ll dis) {
        thisVexter=vertex;
        path=last;
        distance=dis;
        short_way_distance=0;
        path_type=0;
    }
    bool operator<(const PathNode &rhs)const {
        return distance<rhs.distance;
    }
    bool operator>(const PathNode &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const PathNode &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const PathNode &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const PathNode &rhs) const {
        return distance == rhs.distance;
    }

    bool operator!=(const PathNode &rhs) const {
        return !(rhs == *this);
    }
};
class Graph {
public:
    Graph() {

    };
    void Link(Vexter startVertex,Vexter endVertex,ll weight,int type);
    void DoubleLink(Vexter startVertex,Vexter endVertex,ll weight,int type);
    void Dijkstra(Vexter startVertex,Vexter endVertex);
private:
    list<graphNode> Link_list[MaxVexter];
    list<PathNode> shortest_Node_heap;
};
void Graph::Link(Vexter startVertex,Vexter endVertex,ll weight,int type) {
    graphNode graphNode(endVertex,weight,type);
    Link_list[startVertex].push_back(graphNode);

}
void Graph::DoubleLink(Vexter startVertex,Vexter endVertex,ll weight,int type) {
    Link(startVertex,endVertex,weight,type);
    Link(endVertex,startVertex,weight,type);
}
void Graph::Dijkstra(Vexter startVertex,Vexter endVertex) {
    PathNode pathnode_list[MaxVexter];
    for(int num=1; num<MaxVexter; num++) {
        pathnode_list[num].thisVexter=num;
        pathnode_list[num].path=StartVexterHNH;
        pathnode_list[num].distance=Infinity;
    }
    pathnode_list[startVertex].distance=0;
    pathnode_list[startVertex].thisVexter=startVertex;
    pathnode_list[startVertex].path=StartVexterHNH;
    shortest_Node_heap.push_back(pathnode_list[startVertex]);

    while(!shortest_Node_heap.empty()) {
        Vexter tmp=shortest_Node_heap.front().thisVexter;
        shortest_Node_heap.pop_front();
        for(list<graphNode>::iterator it=Link_list[tmp].begin(); it!=Link_list[tmp].end(); it++) {
            graphNode itor= *it;
            if(pathnode_list[itor.link_vexter].distance==Infinity) {
                if(!pathnode_list[tmp].path_type) {//之前走大道
                    if(itor.type) {//小道且之前大道
                        pathnode_list[itor.link_vexter].path_type=1;
                        pathnode_list[itor.link_vexter].short_way_distance=itor.weight;
                        pathnode_list[itor.link_vexter].distance=pathnode_list[tmp].distance+itor.weight*itor.weight;
                        shortest_Node_heap.push_back(pathnode_list[itor.link_vexter]);

                    } else {//大道且之前是大道
                        pathnode_list[itor.link_vexter].path_type=0;
                        pathnode_list[itor.link_vexter].short_way_distance=0;
                        pathnode_list[itor.link_vexter].distance=pathnode_list[tmp].distance+itor.weight;
                        shortest_Node_heap.push_back(pathnode_list[itor.link_vexter]);
                    }
                } else {//之前走小道
                    if(itor.type) {//小道且之前小道
                        pathnode_list[itor.link_vexter].path_type=1;
                        pathnode_list[itor.link_vexter].short_way_distance=pathnode_list[tmp].short_way_distance+itor.weight;
                        pathnode_list[itor.link_vexter].distance=pathnode_list[tmp].distance+itor.weight*itor.weight+2*pathnode_list[tmp].short_way_distance*itor.weight;
                        shortest_Node_heap.push_back(pathnode_list[itor.link_vexter]);
                    } else {//大道且之前是小道
                        pathnode_list[itor.link_vexter].path_type=0;
                        pathnode_list[itor.link_vexter].short_way_distance=0;
                        pathnode_list[itor.link_vexter].distance=pathnode_list[tmp].distance+itor.weight;
                        shortest_Node_heap.push_back(pathnode_list[itor.link_vexter]);
                    }
                }
                pathnode_list[itor.link_vexter].path=tmp;
                shortest_Node_heap.sort();
            } else {
                if(!pathnode_list[tmp].path_type) {//之前走大道
                    if(itor.type) {//小道且之前大道
                        if(	pathnode_list[itor.link_vexter].distance>pathnode_list[tmp].distance+itor.weight*itor.weight) {
                            pathnode_list[itor.link_vexter].path_type=1;
                            pathnode_list[itor.link_vexter].short_way_distance=itor.weight;
                            pathnode_list[itor.link_vexter].distance=pathnode_list[tmp].distance+itor.weight*itor.weight;
                            pathnode_list[itor.link_vexter].path=tmp;
                        }
                    } else {//大道且之前是大道
                        if(	pathnode_list[itor.link_vexter].distance>pathnode_list[tmp].distance+itor.weight) {
                            pathnode_list[itor.link_vexter].path_type=0;
                            pathnode_list[itor.link_vexter].short_way_distance=0;
                            pathnode_list[itor.link_vexter].distance=pathnode_list[tmp].distance+itor.weight;
                            pathnode_list[itor.link_vexter].path=tmp;

                        }
                    }
                } else {//之前走小道
                    if(itor.type) {//小道且之前小道
                        if(	pathnode_list[itor.link_vexter].distance>pathnode_list[tmp].distance+itor.weight*itor.weight+2*pathnode_list[tmp].short_way_distance*itor.weight) {
                            pathnode_list[itor.link_vexter].path_type=1;
                            pathnode_list[itor.link_vexter].short_way_distance=pathnode_list[tmp].short_way_distance+itor.weight;
                            pathnode_list[itor.link_vexter].distance=pathnode_list[tmp].distance+itor.weight*itor.weight+2*pathnode_list[tmp].short_way_distance*itor.weight;
                            pathnode_list[itor.link_vexter].path=tmp;
                        }

                    } else {//大道且之前是小道
                        if(	pathnode_list[itor.link_vexter].distance>pathnode_list[tmp].distance+itor.weight) {
                            pathnode_list[itor.link_vexter].path_type=0;
                            pathnode_list[itor.link_vexter].short_way_distance=0;
                            pathnode_list[itor.link_vexter].distance=pathnode_list[tmp].distance+itor.weight;
                            pathnode_list[itor.link_vexter].path=tmp;
                        }

                    }
                }
            }


        }
    }
    cout<<pathnode_list[endVertex].distance;
}
void FindMinWay() {
    Graph graph;
    int n;
    ll m,length;
    cin>>n>>m;
    int type,start,end;
    for(ll i=000000; i<m; i++) {
        cin>>type>>start>>end>>length;
        graph.DoubleLink(start,end,length,type);
    }
    graph.Dijkstra(1,n);
}

//201709
class JsonOpreater {

public:
    void Run();

    void JsonOprate();

    void UpdateObject();

    void AddToLast(char ch);

private:
    int n, m;

    char itor;
    string strtmp, keytmp, valuetmp, objecttmp;
    bool readflag, keyflag;
    list<char> punct_stack;
    list <string> object_stack;
    map<string, string> json_map;
};

void JsonOpreater::JsonOprate() {
    int i = 0;
    int counter = 0;
    bool isTrans=false;
    cin >> n >> m;
    cin.get();
    while (counter++ < n) {
        strtmp.clear();
        keytmp.clear();
        valuetmp.clear();
        isTrans=false;
        readflag = false;
        keyflag = true;
        getline(cin,strtmp);
        for (i = 0; i < strtmp.length(); i++) {
            if (strtmp[i] == '\"') {
                if (i > 0 && strtmp[i - 1] == '\\'&&isTrans) {
                    if (keyflag)
                        keytmp.erase(keytmp.end()-1);
                    else
                        valuetmp.erase(valuetmp.end()-1);
                    AddToLast('\"');
                    isTrans=false;
                } else {//露脕脠毛脣芦脪媒潞脜
                    if (punct_stack.back() == '\"') {
                        punct_stack.pop_back();
                        readflag = false;
                        if (keyflag) {
                            keyflag = false;
                        } else {
                            json_map.insert(pair<string, string>(objecttmp + keytmp, "STRING " + valuetmp));
                        }
                    } else {
                        punct_stack.push_back('\"');
                        readflag = true;
                    }
                }
            } else if (strtmp[i] == '}') {
                if (punct_stack.back() == '{' && !readflag) {
                    punct_stack.pop_back();
                    if(!objecttmp.empty()) {
                        object_stack.pop_back();
                        UpdateObject();
                    }
                } else {
                    AddToLast('}');
                }
            } else if (strtmp[i] == ':') {
                if (readflag) {
                    AddToLast(':');
                } else
                    continue;
            } else if (strtmp[i] == '{') {
                if (!keytmp.empty()) {
                    object_stack.push_back(keytmp);
                    json_map.insert(pair<string, string>(objecttmp+keytmp, "OBJECT"));
                }
                punct_stack.push_back('{');
                UpdateObject();
            } else if(strtmp[i]=='\\') {
                if((i==0)||strtmp[i-1]!='\\') {
                    AddToLast(strtmp[i]);
                    isTrans=true;
                } else {
                    if(isTrans) {
                        isTrans=false;
                        continue;
                    } else {
                        AddToLast(strtmp[i]);
                        isTrans=true;
                    }
                }
            } else {
                AddToLast(strtmp[i]);
            }
        }
    }
}

void JsonOpreater::UpdateObject() {
    objecttmp.clear();
    for (list<string>::iterator itor = object_stack.begin(); itor != object_stack.end(); itor++) {
        objecttmp += (*itor) + '.';
    }
}

void JsonOpreater::AddToLast(char ch) {
    if(readflag) {
        if (keyflag)
            keytmp.push_back(ch);
        else
            valuetmp.push_back(ch);
    }
}

void JsonOpreater::Run() {
    int counter = 0;
    JsonOprate();

    vector<string> requesttmp(m);
    for(int i=0; i<m; i++) {
        getline(cin,requesttmp[i]);
    }
    while (counter++ < m) {
        if (json_map.count(requesttmp[counter-1])) {
            cout << json_map[requesttmp[counter-1]]<<endl;
        } else {
            cout << "NOTEXIST" << endl;
        }
    }
}



int main(int argc, char** argv) {
    JsonOpreater jsonOpreater;
    jsonOpreater.Run();
    return 0;
}