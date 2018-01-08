/*
 * 数据结构课程设计
 * 题目六  家谱管理系统
 * 姓名：李向真
 * 学号：1552970
 * */

#include <iostream>
#include <string>

using namespace std;

/*成员结构体 member*/
struct member{
    member(){}    // 默认构造函数
    member(string n):name(n){}   // 用成员名字初始化
    ~member(){         //  析构函数
        offspring = NULL;
        brother = NULL;
    }
    string name;     // 成员姓名
    member* offspring = NULL;   // 长子
    member* brother = NULL;     // 兄弟
};

typedef member* familyTree;   // 家谱树类型

member* findMember(familyTree tree,string m){  // 根据名字查找成员
    if(tree == NULL)   //查找失败
        return NULL;
    if(tree->name == m)  //查找成功
        return tree;

    member* temp = findMember(tree->brother,m);
    if(temp != NULL)     //先查找长子
        return temp;
    else
        return findMember(tree->offspring,m);   //递归查找同辈成员
}

member* addOffspring(familyTree tree,string n){  // 为指定成员添加后代
    if(tree->offspring == NULL)   //处理空树情况
        tree->offspring = new member(n);
    else{
        member* temp = tree->offspring;
        while(temp->brother != NULL)   //找到同辈最后一个子女
            temp = temp->brother;
        temp->brother = new member(n);
    }
    return tree;
}

member* modify(familyTree tree,string past,string now){ // 修改指定成员的名字
    member* temp = findMember(tree,past);
    if(temp == NULL)    //判断操作合法性
        cout<<"查无此人！\n";
    else
        temp->name = now;

    return temp;
}

void deleteFamily(familyTree tree){  // 删除指定成员
    if(tree != NULL){
        deleteFamily(tree->brother);   //递归的删除该节点所有兄弟及子女节点
        deleteFamily(tree->offspring);
        delete tree;
    }
}

void displayOffspring(familyTree p){  //遍历输出子女信息
    cout<<p->name<<"的第一代子孙是：";
    p = p->offspring;        //先输出长子
    while(p != NULL){       //循环输出兄弟节点
        cout<<p->name<<" ";
        p = p->brother;
    }
    cout<<endl;
}

void menu(){    //打印菜单
    cout<<"**          家谱管理系统         **\n"
        <<"=================================\n"
        <<"**    请选择要执行的操作：        **\n"
        <<"**     A --- 完善家庭            **\n"
        <<"**     B --- 添加家庭成员        **\n"
        <<"**     C --- 解散局部家庭        **\n"
        <<"**     D --- 更改家庭成员姓名    **\n"
        <<"**     E --- 退出程序           **\n"
        <<"=================================\n"
        <<"首先建立一个家谱！\n"
        <<"请输入祖先的姓名：";
}

int main() {

    string n;
    familyTree myTree;
    menu();  //初始化输出菜单
    cin>>n;
    cout<<"此家谱的祖先是："<<n<<endl;
    myTree = new member(n);   //新建一颗家谱树
    char op;
    int num;
    member* p;
    cout<<"\n请选择要执行的操作：";
    /*
     * 依据不同的选择执行操作
     */
    while(cin>>op && op != 'E'){
        switch (op){
            case 'A':
                cout<<"请输入要建立家庭的人的姓名：";
                cin>>n;
                p = findMember(myTree,n);
                if(p == NULL){         //处理非法输入
                    cout<<"查无此人！\n";
                    break;
                }
                cout<<"请输入" <<n<<"的儿女数：";
                cin>>num;
                cout<<"请依此输入"<<n<<"的儿女的姓名：";
                for(int i = 0;i < num;++i){    //循环添加子女
                    cin>>n;
                    addOffspring(p,n);
                }
                displayOffspring(p);
                break;
            case 'B':
                cout<<"请输入要添加儿子(或女儿)的人的姓名：";
                cin>>n;
                p = findMember(myTree,n);
                if(p == NULL){          //处理非法输入
                    cout<<"查无此人！\n";
                    break;
                }
                cout<<"请输入"<<n<<"新添加的儿子(或女儿)的姓名：";
                cin>>n;
                addOffspring(p,n);
                displayOffspring(p);
                break;
            case 'C':
                cout<<"请输入要解散的人的姓名：";
                cin>>n;
                cout<<"要解散家庭的人是："<<n<<endl;
                p = findMember(myTree,n);
                if(p == NULL){        //处理非法输入
                    cout<<"查无此人！\n";
                    break;
                }
                displayOffspring(p);
                deleteFamily(p->offspring);  //删除该节点所有子女
                p->offspring = NULL;         //将相应指针置空，以免非法访问
                break;
            case'D':
                cout<<"请输入要更改的人的目前姓名：";
                cin>>n;
                string now;
                cout<<"请输入更改后的姓名：";
                cin>>now;
                modify(myTree,n,now);   //修改该节点
                cout<<n<<"已更名为"<<now<<endl;
                break;
        }
        cout<<"\n请选择要执行的操作：";
    }
    return 0;
}




















