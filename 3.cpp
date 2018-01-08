/*
 * 数据结构课程设计
 * 题目三  勇闯迷宫游戏
 * 姓名：李向真
 * 学号：1552970
 * */

#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

#define MAXSIZE 100     // 定义地图最大规模

/*
 * 定义路径节点类
 * 存储节点坐标信息
 * 有配套的构造函数
 * 自定义了比较函数
 * 自定义了输出流
 * */
struct PathPoint{
    PathPoint():x(0),y(0){}     // 默认构造函数
    PathPoint(int a = 0,int b = 0):x(a),y(b){}  // 传入坐标值的构造函数
    friend ostream& operator <<(ostream&, const PathPoint&);    // 自定义输出流
    bool operator == (const PathPoint& target){     // 自定义比较函数
        return (x==target.x&&y==target.y);
    }

    int x;      // 节点横坐标
    int y;      // 节点纵坐标
};

/*
 * 自定义输入流
 * 格式化输出该节点的坐标
 * */
ostream& operator <<(ostream& out, const PathPoint& p){
    out<<'<'<<p.x<<','<<p.y<<'>';
    return out;
}

int map[MAXSIZE][MAXSIZE];      // 地图数组，记录地图信息
int mark[MAXSIZE][MAXSIZE];     // 标记访问过的位置
vector<PathPoint> PathStack;  // 栈存储路径

void initMap(int M,int N);      // 地图初始化函数
void readMap(int M,int N);      // 地图信息读入函数
void createPath(PathPoint e);   // 路径搜寻函数
void print(int M,int N,PathPoint e);        // 路径打印函数

int main(){

    int m,n;
    cout<<"请输入迷宫行数与列数(不包括外墙):\n";       // 读入迷宫规模
    cin>>m>>n;
    const int M = m;        // 定义迷宫规模常量
    const int N = n;

    initMap(M,N);           // 初始化迷宫地图

    readMap(M,N);           // 读入迷宫地图

    cout<<"请输入出口坐标：\n";
    cin>>m>>n;                  // 读入迷宫出口
    PathPoint exit(m,n);        // 建立出口节点

    //出口合法性检查
    if(map[exit.x][exit.y] == 1||exit.y != N){      // 如果出口处有墙或出口不在迷宫边缘则非法
        cout<<"非法的出口！\n";
        return 0;
    }

    if(map[1][1] == 1)
        cout<<"（1，1）起始位置有墙，路径非法\n";
    else{
        createPath(exit);       // 在迷宫中搜索路径

        print(M,N,exit);            // 打印路径
    }


    return 0;
}

/*
 * 对地图进行初始化操作
 * 包括地图边缘、标记数组等
 * */
void initMap(int M,int N){
    //初始化map,mark
    memset(map,0,(M + 2)*(N + 2)*sizeof(int));      // 对地图清零
    memset(mark,0,(M + 2)*(N + 2)*sizeof(int));     // 对标记数组清零
    for(int i = 0;i < N + 2;++i)                    // 将地图边界外墙置1
        map[M + 1][i] = map[0][i] = 1;
    for(int i = 0;i < M + 2;++i)
        map[i][0] = map[i][N + 1] = 1;
}

/*
 * 读入地图信息
 * 0 代表通路，1 代表路障
 * 读入的迷宫地图不包括外墙
 * */
void readMap(int M,int N){
    //输入地图
    cout<<"请输入地图各行各列（0 代表通路，1 代表路障）\n";

    for(int i = 1;i <= M;++i)
        for(int j = 1;j <= N;++j){
            cin>>map[i][j];
        }

}

/*
 * 在迷宫中搜索路径
 * 通过栈来存储沿途节点
 * 采用DFS策略探寻路线
 * */
void createPath(PathPoint e){

    mark[1][1] = 1;     // 从（1，1）位置开始探寻
    PathStack.push_back(PathPoint(1,1));    // 将起始（1，1）位置压入栈中

    while(!PathStack.empty()){      // 栈非空时一直探寻路径
        PathPoint current = PathStack.back();   // 取出栈顶元素，以它为起点探寻路径
        if(current == e)        // 栈顶元素为出口，则找到路径，探寻结束
            break;
        if(mark[current.x][current.y - 1] == 0&&map[current.x][current.y - 1] == 0){        //先探寻上方路径
            PathStack.push_back(PathPoint(current.x,current.y - 1));
            mark[current.x][current.y - 1] = 1;
        }
        else if(mark[current.x + 1][current.y] == 0&&map[current.x + 1][current.y] == 0){   //探寻右侧路径
            PathStack.push_back(PathPoint(current.x + 1,current.y));
            mark[current.x + 1][current.y] = 1;
        }
        else if(mark[current.x][current.y + 1] == 0&&map[current.x][current.y + 1] == 0){   //探寻下方路径
            PathStack.push_back(PathPoint(current.x,current.y + 1));
            mark[current.x][current.y + 1] = 1;
        }
        else if(mark[current.x - 1][current.y] == 0&&map[current.x - 1][current.y] == 0){   //探寻左侧路径
            PathStack.push_back(PathPoint(current.x + 1,current.y));
            mark[current.x - 1][current.y] = 1;
        }
        else
            PathStack.pop_back();       //四个方向均走不通，则退回前一步
    }

}

/*
 * 格式化输出路线图以及路线
 * 内部创建了辅助数组printmap
 * */
void print(int M,int N,PathPoint e){
    //结果输出

    char printmap[M + 2][N + 2];        // 建立输出辅助数组

    if(PathStack.back() == e){          // 如果找到了出口，则打印路线地图

        for(int i = 0;i < M + 2;++i)        // 先将墙与路写入
            for(int j = 0;j < N + 2;++j){
                if(map[i][j] == 1)
                    printmap[i][j] = '#';
                else
                    printmap[i][j] = '0';
            }
        for(int i = 0;i < PathStack.size();++i){        // 写入搜索到的路径
            printmap[PathStack[i].x][PathStack[i].y] = 'x';
        }
        cout<<"迷宫地图：\n\n";      //格式化输出地图
        cout<<"   	";
        for(int i = 0;i < N + 2;++i)
            cout<<i<<"列	";
        cout<<endl;
        for(int i = 0;i < M + 2;++i){
            cout<<i<<"行	";
            for(int j = 0;j < N + 2;++j)
                cout<<printmap[i][j]<<"  	";
            cout<<"\n\n";
        }

        cout<<"迷宫路径：\n\n";      // 格式化输出路径
        for(int i = 0;i < PathStack.size() - 1;++i){
            cout<<PathStack[i]<<" ---> ";
        }
        cout<<e<<endl;
    }
    else
        cout<<"迷宫没有合法路径！\n";    // 如果没有找到出口则提示错误

}