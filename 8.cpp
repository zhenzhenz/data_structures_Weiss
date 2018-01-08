/*
 * 数据结构课程设计
 * 题目八  电网建设造价模拟系统
 * 姓名：李向真
 * 学号：1552970
 * */


#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

#define MAXSIZE 1000    // 定义图的最大规模
#define MAXWEIGHT 100000    // 定义边的最大权值

struct edge{   // 定义边结构体
    edge(string a,string b,int c):x(a),y(b),weight(c){}
    string x,y;
    int weight;
};

int graph[MAXSIZE][MAXSIZE];    // 定义图结构
map<string,int> node;       // 定义图中节点名称到节点存储位置的映射
map<int,string> denode;     // 定于图中节点存储位置到名称的映射
vector<edge> MST;           // 定义最小生成树

void printMenu();   // 打印主菜单
void getNodes();    // 向图中插入顶点
void addEdge();     // 向图中插入边
void prim(int start);        // prim 算法求最小生成树
void printTree();   // 打印最小生成树

int main() {
    printMenu();    // 输出主菜单
    char c;
    cout<<"请选择操作："; // 用户输入操作
    cin>>c;
    string t;
    while(c != 'E'){
        switch (c){     // 根据操作执行相关函数
            case 'A':
                getNodes();
                break;
            case 'B':
                addEdge();
                break;
            case 'C':
                cout<<"请输入起始顶点：";
                cin>>t;
                if(node.find(t) == node.end())
                    cout<<"顶点不存在！\n";
                else
                    prim(node[t]);
                break;
            case 'D':
                printTree();
                break;
        }

        cout<<"请选择操作：";
        cin>>c;
    }

    return 0;
}

/*
 * 向图中插入节点
 * 构建节点存储位置和节点名称的两个映射
 * 同时对节点中的边进行初始化
 * */
void getNodes(){
    cout<<"请输入顶点个数： ";
    int n;
    cin>>n;
    cout<<"请依次输入各顶点名称：\n";
    string name;
    for(int i = 0;i < n;++i){
        cin>>name;
        node.insert(make_pair(name,i));    // 建立节点名称到节点存储位置的映射
        denode.insert(make_pair(i,name));      // 建立节点存储位置到名称的映射
    }
    for(int i = 0;i < n;++i)
        for(int j = 0;j < n;++j){
            graph[i][j] = MAXWEIGHT;        //初始化所有边
        }
    cout<<endl;
}

/*
 * 向图书插入边
 * 无边连接的节点间边为MAXWEIGHT
 * */
void addEdge(){
    int w;
    string n1,n2;
    cout<<"请输入两个顶点及边：";
    cin>>n1>>n2>>w;
    while(n1 != "?"&&n2 != "?"&&w != 0){        //循环插入所有边
        if(node.find(n1) == node.end()||node.find(n2) == node.end()){       //处理节点不存在的情况
            cout<<"顶点不存在！\n";
        }
        else{
            graph[node[n1]][node[n2]] = graph[node[n2]][node[n1]] = w;
        }
        cout<<"请输入两个顶点及边：";
        cin>>n1>>n2>>w;
    }
    cout<<endl;
}


/*
 * prim算法
 * 构建最小生成树
 * */
void prim(int start){
    const int N = node.size();  //节点数量
    int distan[N];      //未选入节点到已选入及节点集的最短距离
    int parent[N];      //节点连向选入节点的父节点
    int count = 1;
    for(int i = 0;i < N;++i){   //初始化辅助数组
        distan[i] = graph[start][i];
        parent[i] = start;
    }
    parent[start] = -1;     //初始化 0 节点
    distan[start] = 0;

    while(1){
        int v = -1;     //记录距离最近节点
        int mindis = MAXWEIGHT; //记录最近距离

        for(int i = 0;i < N;++i){   //循环遍历，找出最近节点
            if(distan[i] != 0&&distan[i] < mindis){
                v = i;
                mindis = distan[i];
            }
        }
        if(v == -1)     //不存在最近节点，则算法结束
            break;
        ++count;        //记录已选入节点数量
        distan[v] = 0;
        MST.emplace_back(edge(denode[parent[v]],denode[v],graph[parent[v]][v]));    //将新生成的边插入最小生成树

        for(int i = 0;i < N;++i){       //跟新未选入节点到已选入及节点集的最短距离
            if(distan[i] != 0&&distan[i] > graph[i][v]){
                distan[i] = graph[i][v];
                parent[i] = v;
            }
        }

    }
    if(count < N - 1)       //处理图不连通的情况
        cout<<"不存在最小生成树！";
    else
        cout<<"生成Prim最小生成树！\n";

}

/*
 * 输出最小生成树
 * */
void printTree(){
    cout<<"最小生成树的顶底及边为：\n\n";
    for(int i = 0;i < MST.size();++i){
        cout<<MST[i].x<<"-<"<<MST[i].weight<<">->"<<MST[i].y<<"    ";   //
    }
    cout<<"\n\n";
}

/*
 * 打印主菜单
 * */
void printMenu(){
    cout<<"**       电网造价模拟系统        **\n";
    cout<<"=================================\n";
    cout<<"**       A --- 创建电网顶点      **\n";
    cout<<"**       B --- 添加电网的边      **\n";
    cout<<"**       C --- 构造最小生成树    **\n";
    cout<<"**       D --- 显示最小生成树    **\n";
    cout<<"**       E --- 退出程序         **\n";
    cout<<"=================================\n";
}














