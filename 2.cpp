/*
 * 数据结构课程设计
 * 题目二  约瑟夫生者死者游戏
 * 姓名：李向真
 * 学号：1552970
 * */

#include<iostream>
using namespace std;

/*
 * 乘客结构体
 * 即组成约瑟夫环的节点类型
 * */
struct Member{
    Member():next(NULL){}       // 默认构造函数
    Member(int s){              // 构造函数，传入乘客位置编号
        id = s;
        next = NULL;
    }

    int id;                 // 位置编号
    Member* next;           // 相邻的下一个节点
};

/*
 * 约瑟夫生死环类型
 * 实际上是一个循环链表
 * 提供在环内移步、删除等操作
 * */
struct DyingList{
    DyingList(){}           // 默认构造函数
    DyingList(int sz);      // 构造函数，传入环的长度

    Member* step(int n,Member* beg);    // 移步函数，移动指定步数
    Member* kill(Member* target);       // 杀人函数，删除节点

    int size;                       // 生死环的长度
    Member* head;                   // 生死环头节点指针
};


/*
 * 生死环构造函数
 * 传入生死环长度
 * 建立对应长度的生死环
 * */
DyingList::DyingList(int sz){
    size = sz;          // 生死环长度赋值
    head = new Member(1);         // 建立头节点
    Member* p = head;

    for(int i = 2;i <= sz;++i){     // 循环的建立链表节点
        p->next = new Member(i);
        p = p->next;
    }
    p->next = head;
}

/*
 * 移步函数
 * 传入要移动的步数以及移动起始节点
 * 返回移动后的位置指针
 * */
Member* DyingList::step(int n,Member* beg){
    for(int i = 0;i < n;++i){       // 循环移步，每次移动移步
        beg = beg->next;
    }
    return beg;         // 返回移动后位置
}

/*
 * 杀人函数
 * 即删除函数
 * 传入要删除的节点指针
 * 返回被删节点的下一个节点
 * */
Member* DyingList::kill(Member* target){
    if(target == head)          // 处理删除头节点的情况
        head = target->next;

    Member* p = head;
    while(p->next != target){       // 寻找被删除节点的前驱节点
        p = p->next;
    }
    p->next = target->next;         // 从链中去除节点
    p = target->next;               // 保留被删节点的下一个节点
    delete target;                  // 释放被删空间
    return p;                       // 返回被删节点的下一个
}

int main(){

    /*
     * 初始化游戏信息
     * */
    cout<<"现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一个人开始报数，如此循环，直到剩下K个人为止\n\n";
    int n,m,s,k;
    cout<<"请输入生死游戏的总人数N:";
    cin>>n;
    cout<<"请输入游戏开始的位置S:";
    cin>>s;
    cout<<"请输入死亡数字M:";
    cin>>m;
    cout<<"请输入剩余的生者人数K:";
    cin>>k;
    cout<<endl;


    /*
     * 处理非法输入的情况
     * */
    if(n == 0){
        cout<<"游戏人数为0，非法输入！\n";
        return 0;
    }
    else if(n < k){
        cout<<"游戏人数过少，非法输入！\n";
        return 0;
    }
    else if(n < s){
        cout<<"非法的开始位置！\n";
        return 0;
    }


    DyingList list(n);          // 根据输入的乘客数量创建约瑟夫环
    Member* current = list.head;        // 指针最初指向生死环头节点
    current = list.step(s - 1,current);         // 根据开始位置的要求跳转到对应位置

    /*
     * 循环执行 n - k 次，每次杀死一个人
     * 最后环中剩余 k 个人
     * */
    for(int i = 1;i <= n - k;++i){
        Member* killed = list.step(m - 1,current);      // 每次跳转 m - 1 个位置
        cout<<"第"<<i<<"个死者的位置是：	"<<killed->id<<endl;        // 杀死对应位置的人
        current = list.kill(killed);
    }

    /*
     * 输出游戏结果
     * */
    cout<<"\n最后剩下：	"<<k<<"人\n";

    cout<<"剩余生者的位置为：	";
    Member* p = list.head;
    for(int i = 0;i < k;++i){       // 循环遍历输出链中剩余的人的位置
        cout<<p->id<<"	";
        p = p->next;
    }

    return 0;
}
