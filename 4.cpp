/*
 * 数据结构课程设计
 * 项目四  N皇后问题
 * 姓名：李向真
 * 学号：1552970
 * */

#include<iostream>
#include<cmath>

using namespace std;

bool qualified(int* map,int m,int n);   // 合法性检验函数
void printmap(int* map,int n);      // 打印合理的N皇后布局

int main(){

    int n;
    cout<<"现有N X N 的棋盘，放入N个皇后，要求所有皇后不在同一行、列和同一斜线上！\n\n";    // 输出交互提示
    cout<<"请输入皇后个数：";
    cin>>n;                 // 读入地盘规模
    cout<<"\n皇后摆法：\n\n";
    const int N = n;        // 定义常量N作为棋盘大小，用于建立辅助数组
    int map[N];             // 辅助数组，存储每行中摆放皇后的列号
    int count = 0;
    int i = 0,j = 0;
    while(1){               // 循环尝试皇后可能的摆放位置
        while(j < N){          // 对第i行的所有j列情况进行尝试
            if(qualified(map,i,j)){     // 判断是否为合法位置
                map[i] = j;         // 如果是合法位置就放置节点
                j = 0;              // 列号归0
                break;
            }
            else                // 如果不是合法位置，继续探索下一列
                ++j;
        }
        if(j == N){             // 如果当前行没有合法位置
            if(i == 0)          // 如果行号为0，说明已经找到所有情况，循环结束
                break;
            else{               // 如果行号非0，就退回前一行
                --i;
                j = map[i] + 1;     // 探索前一行之前合法位置的下一个
            }
        }
        else if(i == N - 1){            // 如果已经探索到最后一行，说明已经产生一种方案
            printmap(map,N);           // 输出该方案
            ++count;                    // 记录方案个数
            j = map[i] + 1;             // 探索该行下一个位置
        }
        else                            // 如果是中间行，则继续探索下一行
            ++i;
    }
    cout<<"\n共有"<<count<<"种解法！"<<endl;
    return 0;
}

/*
 * 位置合法性检验函数
 * 检验摆放位置是否合法
 * 即其横竖斜向都不存在其他皇后
 * */
bool qualified(int* map,int m,int n){
    for(int i = 0;i < m;++i){       // 遍历已经摆好的每个皇后位置，检查是否有冲突
        if(map[i] == n||abs(m - i) == abs(n - map[i]))
            return false;
    }
    return true;
}

/*
 * 皇后位置打印函数
 * 根据给定的皇后位置信息
 * 格式化输出该图中皇后摆法
 * */
void printmap(int* map,int n){
    for(int i = 0;i < n;++i){
        for(int j = 0;j < n;++j){       // 格式化输出棋盘各行
            if(map[i] == j)
                cout<<"X ";
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
    cout<<endl;
}
