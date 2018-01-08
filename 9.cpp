/*
 * 数据结构课程设计
 * 题目九  二叉排序树
 * 姓名：李向真
 * 学号：1552970
 * */

#include <iostream>
#include <sstream>

using namespace std;

typedef int ElementType;    // 元素键值类型
typedef struct TNode *BinTree;  // 二叉排序树类型

struct TNode{           //二叉排序树节点类型
    ElementType Data;   //节点关键字类型
    BinTree Left;       //左子树
    BinTree Right;      //右子树
};

BinTree Insert( BinTree BST, ElementType X );   // 插入函数

BinTree Find( BinTree BST, ElementType X );     //查找函数

void printTree(BinTree BT);                 //输出函数
void InorderTraversal( BinTree BT );        //中序遍历
void menu();        //主菜单函数

int main()
{
    menu();     //打印主菜单

    BinTree BST = NULL;     //创建新的空树
    ElementType X;

    stringstream ss;   // 字符流类型
    string nodes;       // 以字符串形式读入一行二叉树节点
    int temp;
    int choice;         // 操作选择
    cout<<"Please select:   ";
    cin>>choice;

    while(choice != 4){     //循环输入所选操作
        switch (choice){
            case 1:
                cout<<"Please input key to create Bsort_Tree:\n";       // 读入字符串所有节点
                getchar();
                getline(cin,nodes);
                ss<<nodes;

                while(ss>>X&&X != 0){       // 当读入元素为0时，插入停止
                    BST = Insert(BST,X);
                }
                printTree(BST);
                break;
            case 2:
                cout<<"Please input key which is inserted:  ";   //插入单个节点
                cin>>temp;
                Insert(BST,temp);
                printTree(BST);
                break;
            case 3:
                cout<<"Please input key which is searched:  ";
                cin>>temp;
                BinTree found = Find(BST,temp);
                if(found == NULL)           // 处理元素不存在情况
                    cout<<temp<<" not exist\n\n";
                else
                    cout<<"search success!\n\n";
                break;
        }
        cout<<"Please select:   ";
        cin>>choice;
    }

    return 0;
}

/*
 * 打印主菜单
 * */
void menu(){
    cout<<"**        二叉排序树            **\n";
    cout<<"=================================\n";
    cout<<"**       1 --- 建立二叉排序树    **\n";
    cout<<"**       2 --- 插入元素         **\n";
    cout<<"**       3 --- 查询元素         **\n";
    cout<<"**       4 --- 退出程序         **\n";
    cout<<"=================================\n";
}

/*
 * 向二叉排序树中插入节点
 * 参数传入树的根节点以及被插入的元素键值
 * 返回被操作节点的指针类型
 * 便于递归操作
 * */
BinTree Insert( BinTree BST, ElementType X ){
    if(!BST){           // 处理空树情况
        BST = new TNode;
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
    }
    else{       // 递归插入
        if(X > BST->Data)    // 根据节点键值选择插入位置
            BST->Right = Insert(BST->Right,X);
        else if(X < BST->Data)
            BST->Left = Insert(BST->Left,X);
        else
            cout<<"The input key<"<<X<<">"<<"iS have in!\n";      // 处理元素已经存在的情况
    }

    return BST;
}

/*
 * 在二叉排序树中查找元素
 * 递归查找
 * 返回被查找元素的指针
 * */
BinTree Find( BinTree BST, ElementType X ){
    if(BST == NULL){
        return NULL;
    }
    if(BST->Data == X){

        return BST;
    }
    else if(BST->Data < X)
        return Find(BST->Right,X);
    else
        return Find(BST->Left,X);
}

/*
 * 中序遍历二叉排序树
 * 中序遍历的顺序就是节点键值大小排序
 * */
void InorderTraversal( BinTree BT ){
    if(!BT){
        return;
    }

    else{
        InorderTraversal(BT->Left);
        cout<<BT->Data<<"->";
        InorderTraversal(BT->Right);
    }
}

/*
 * 打印二叉排序树
 * 打印的顺序按照节点键值从小到大
 * 内部调用中序遍历
 * */
void printTree(BinTree BT){
    if(BT == NULL) {
        cout<<"Empty Tree\n";
        return;
    }
    else{
        cout<<"Bsort_Tree is:\n";
        InorderTraversal(BT);
        cout<<"\n\n";
    }
}
