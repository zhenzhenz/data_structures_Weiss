/*
 * 数据结构课程设计
 * 题目七  修理牧场
 * 姓名：李向真
 * 学号：1552970
 * */

#include <iostream>

using namespace std;


struct Node{    //堆结点
    int* data;      //堆元素数组
    int size;       //堆的大小
    int capacity;      //堆可以空间大小
};

typedef Node* Heap;     //堆类型

/*
 * 新建立一个空的堆
 * 堆的预计大小由参数 ``` int size ``` 给出
 * */
Heap creat(int size){
    Heap h = new Node;
    h->data = new int[size + 1];
    h->size = 0;
    h->capacity = size;
    h->data[0] = -10006;

    return h;
}

/*
 * 插入函数
 * 向堆中插入一个新元素
 * 元素权值由参数传入
 * */
Heap insert(Heap h,int x){

    if(h->size == h->capacity){
        cout<<"Heap is FULL\n";
        return h;
    }

    int i = ++h->size;

    for( ; h->data[i/2] > x; i /= 2){
        h->data[i] = h->data[i/2];
    }
    h->data[i] = x;
    return h;
}

/*
 *删除函数
 *删除堆顶节点
 *返回该节点权值
 * */
int delet(Heap h){
    if(h->size == 0){
        cout<<"堆为空！\n";
        return -1;
    }
    int result = h->data[1];
    int tag = h->data[h->size];
    --h->size;
    int p,c;
    for(p = 1;p*2 <= h->size;p = c){
        c = p*2;
        if(c + 1 <= h->size && h->data[c] > h->data[c + 1])
            ++c;
        if(h->data[c] >= tag)
            break;
        else
            h->data[p] = h->data[c];
    }
    h->data[p] = tag;
    return result;
}


void test();

/*
 * 程序主函数
 * */
int main() {

//    test();

    int n,x;
    cin>>n;     //输入堆的最大规模
    Heap hp = creat(2*n);     //建立新的堆
    for(int i = 0;i < n;++i){       //循环向堆中插入元素
        cin>>x;
        insert(hp,x);
    }

    int answer = 0;     //记录锯木头费用
    while(hp->size > 1){
        int p = delet(hp);  //连续两次取出堆顶元素
        p += delet(hp);
        answer += p;    //记录累计和
        insert(hp,p);   //将本次产生的元素插入堆
    }

    cout<<answer<<endl;     //输出答案

    return 0;
}

/*
 * 测试辅助函数
 * 对于建堆，堆的删除，堆的插入等操作进行测试
 * */
void test(){
    cout<<"输入测试元素个数：\n";
    int n,x;
    cin>>n;
    cout<<"输入各个元素值：\n";
    Heap hp = creat(n);     //建立新的堆
    for(int i = 0;i < n;++i){       //循环向堆中插入元素
        cin>>x;
        insert(hp,x);
    }

    cout<<"堆中元素序列为：\n";
    for(int i = 1;i <= n;++i)
        cout<<hp->data[i]<<" ";
    cout<<endl;

    cout<<"被删除的堆顶元素为："<<delet(hp)<<endl;
    cout<<"删除后堆中元素为："<<endl;
    for(int i = 1;i < n;++i)
        cout<<hp->data[i]<<" ";
    cout<<endl;
    cout<<"请输入要新插入的元素\n";
    cin>>x;
    insert(hp,x);
    cout<<"插入后堆中元素为：\n";
    for(int i = 1;i <= n;++i)
        cout<<hp->data[i]<<" ";
    cout<<endl;
}






