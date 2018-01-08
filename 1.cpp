/*
 * 数据结构课程设计
 * 题目一  考试报名系统
 * 姓名：李向真
 * 学号：1552970
 * */

#include<iostream>
#include<string>
using namespace std;


/*
 * 学生类型
 * 即链表中节点类型
 * 数据域包涵学生信息以及下一个节点指针
 * 内部定义一系列辅助功能函数
 * */
class Student{
    friend class StudentDatabase;       // 定义友元类方便对节点的操作

public:


    Student():_Age(0),_Next(NULL){}         // 默认构造函数，新建空学生信息

    /*
     * 构造函数
     * 初始化学生信息
     * */
    Student(string id, string name, string gender, int age,string major):_TestID(id),_Name(name),_Gender(gender),_Age(age),_Major(major){}


    void InputInfo(string id, string name, string gender, int age,string major);    // 输入学生信息


    void PrintInfo();       //  打印学生信息

    string _TestID;         // 考号
    string _Name;            // 姓名
    string _Gender;         // 性别
    int _Age;               // 年龄
    string _Major;           // 报考类别

    Student* _Next;         // 下一个学生节点
};


/*
 * 定义学生数据库类型
 * 即链表类型
 * 包涵链表的头节点
 * 内部定义一系列辅助函数
 * 基于友元的定义，可以调用节点类型的内部函数
 * */
class StudentDatabase{

public:
    StudentDatabase():_Data(NULL){}         // 默认构造函数

    void BuildDatabase(string id, string name, string gender, int age,string major);        // 数据库建立函数

    void Insert(string id, string name, string gender, int age,string major, int pos);      // 成员插入函数

    void Delete(Student* target);           // 成员删除函数

    Student* Find(string id);               // 成员查找函数

    void Modify(Student* target, Student info);     // 成员信息修改函数

    void Print(Student* target);            // 成员信息输出函数

    void Display();                         // 数据库数据输出函数

    int count();                        // 计数函数

    Student* _Data;             //  数据库数据头节点

};

int main(){

    /*
     * 新建一个学生数据库
     * */
    cout << "首请先建立考生信息系统!" << endl;
    cout << "请输入考生人数：";
    int StudentsNum;
    cin >> StudentsNum;         // 学生人数输入

    /*
     * 处理考生人数非法输入
     * */
    while(StudentsNum <= 0){            // 排除负数或0

        cout<<"学生人数需要是正整数!"<<endl;
        cout << "请输入考生人数";
        cin >> StudentsNum;
    }

    cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别!" <<endl;

    /*
     * 处理输入信息
     * 建成数据库
     * */
    StudentDatabase studentInfo;            // 新建一个数据库类型

    for(int i = 0; i < StudentsNum; ++i){           //  循环向数据库中插入成员
        string id;
        string name;
        string gender;
        int age;
        string major;
        cin>>id>>name>>gender>>age>>major;
        studentInfo.BuildDatabase(id, name, gender, age, major);        // 调用数据库类型内部建立数据库函数
    }

    if(studentInfo._Data == NULL){          // 处理为合法输入数据的情况
        cout<<"空的数据库！\n";
        return 0;
    }

    cout<<endl;
    studentInfo.Display();          // 展示数据课中的数据

    cout<<"请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)\n\n";
    cout<<"请选择您要进行的操作：";
    /*
     * 定义一系列临时变量辅助读入用户输入
     * */
    int tag;            // 操作序号
    string id;          // 学号
    string name;         // 姓名
    string gender;         // 性别
    int age;            // 年龄
    string major;       // 专业
    int pos;            // 插入位置
    Student* temp;      // 待操作节点指针

    while(cin>>tag&&tag != 0){      // 循环读入用户操作
        switch (tag)
        {
            case 1:
                cout<<"请输入你要插入的考生位置：";
                cin>>pos;                           // 输入插入位置
                cout << "请依次输入你要插入的考生的考号，姓名，性别，年龄及报考类别!" <<endl;
                cin>>id>>name>>gender>>age>>major;
                if(studentInfo.Find(id) != NULL){       // 排除学号重复
                    cout<<"考号已经存在！\n";
                    break;
                }
                studentInfo.Insert(id, name, gender, age, major, pos);      // 插入新节点
                cout<<endl;
                studentInfo.Display();
                break;
            case 2:
                cout<<"请输入要删除考生的考号：";
                cin>>id;
                if((temp = studentInfo.Find(id)) == NULL)       // 查找学生存在与否
                    cout<<"没有该考生"<<endl;
                else{
                    cout<<"你要删除的考生的信息是：";
                    temp->PrintInfo();
                    studentInfo.Delete(temp);                  // 删除该节点
                    cout<<endl;

                    studentInfo.Display();
                }
                break;
            case 3:
                cout<<"请输入要查找的考生的考号：";
                cin>>id;
                temp = studentInfo.Find(id);        // 查找学生
                if(temp != NULL){                   // 输出信息
                    cout<<"考号    "
                        <<"姓名    "
                        <<"性别    "
                        <<"年龄    "
                        <<"报考类型"<<endl;
                    studentInfo.Print(temp);
                }
                else
                    cout<<"没有该考生"<<endl;
                break;
            case 4:
                cout<<"请输入要修改的考生的考号：";
                cin>>id;
                temp = studentInfo.Find(id);        // 查找学生是否存在
                if(temp != NULL){
                    cout<<"请依次输入修改后的考生的考号，姓名，性别，年龄及报考类别:\n";
                    cin>>id>>name>>gender>>age>>major;
                    studentInfo.Modify(temp, Student(id, name, gender, age, major));
                }
                else                // 不存在输出提示
                    cout<<"没有该考生"<<endl;
                cout<<endl;
                studentInfo.Display();
                break;
            case 5:
                cout<<"数据库中一共有"<<studentInfo.count()<<"个学生\n";          // 输出统计信息
                studentInfo.Display();
                break;
        }
        cout<<"请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)\n\n";
        cout<<"请选择您要进行的操作：";
    }
    cout<< "信息已系统退出！";
    return 0;
}


/*
 * 输入学生信息
 * */
void Student::InputInfo(string id, string name, string gender, int age,string major){
    _TestID= id;
    _Name = name;
    _Gender = gender;
    _Age = age;
    _Major = major;
}

/*
 * 打印学生信息
 * */
void Student::PrintInfo(){
    cout<<_TestID<<"      "
        <<_Name<<"   "
        <<_Gender<<"      "
        <<_Age<<"      "
        <<_Major<<endl;
}

/*
 * 建立数据课函数
 * 将数据插入链表尾部
 * */
void StudentDatabase::BuildDatabase(string id, string name, string gender, int age,string major){

    if(_Data == NULL){    // 处理数据库为空的情况
        _Data = new Student(id, name, gender, age, major);
        _Data->_Next = NULL;
    }
    else{
        Student* tail = _Data;
        while(tail->_Next != NULL)          // 找到尾节点
            tail = tail->_Next;

        tail->_Next = new Student(id, name, gender, age, major);        // 插入尾部
        tail->_Next->_Next = NULL;
    }

}

/*
 * 节点插入函数
 * 根据参数给出的位置插入数据
 * */
void StudentDatabase::Insert(string id, string name, string gender, int age,string major, int pos){

    if(pos == 1){           // 处理头部插入
        Student* temp = new Student(id, name, gender, age, major);
        temp->_Next = _Data;
        _Data = temp;
        return;
    }

    Student* pre = _Data;
    pos -= 2;
    while(pos != 0&&pre != NULL){       // 找到插入位置前一个节点指针
        pre = pre->_Next;
        --pos;
    }


    if(pos != 0){               // 处理非法插入位置
        cout<<"非法插入位置！\n";
        return;
    }
    else{
        Student* temp = new Student(id, name, gender, age, major);      // 插入对应位置
        temp->_Next = pre->_Next;
        pre->_Next = temp;
    }

}


/*
 * 删除函数
 * 将参数指针对应节点删除
 * */
void StudentDatabase::Delete(Student* target){

    if(target == NULL)      // 处理删除对象为空的情况
        return;

    if(target == _Data){
        _Data = _Data->_Next;          // 处理头节点删除

    }
    else{
        Student* pre = _Data;
        while(pre->_Next != target)     // 找到被删节点前一个位置
            pre = pre->_Next;

        pre->_Next = target->_Next;     // 被删节点出链
    }

    delete target;      // 释放空间

}

/*
 * 查找函数
 * 根据参数的学号查找
 * 返回对象节点指针
 * */
Student* StudentDatabase::Find(string id){
    Student* temp = _Data;

    while(temp != NULL&&temp->_TestID != id)        // 遍历查找
        temp = temp->_Next;

    return temp;

}

/*
 * 修改函数
 * 将参数指针对应节点信息修改为参数内容
 * */
void StudentDatabase::Modify(Student* target, Student info){

    target->_TestID = info._TestID;     // 依次修改对应信息
    target->_Age = info._Age;
    target->_Gender = info._Gender;
    target->_Major = info._Major;
    target->_Name = info._Name;

}

/*
 * 打印函数
 * 输出参数指向节点的信息
 * */
void StudentDatabase::Print(Student* target){
    target->PrintInfo();        // 调用节点自身输出函数
}

/*
 * 展示函数
 * 将数据库中所有信息输出
 * */
void StudentDatabase::Display(){

    if(_Data == NULL){      // 处理数据库为空情况
        cout << "空表！";
        return;
    }

    cout<<"考号   "
        <<"姓名   "
        <<"性别   "
        <<"年龄   "
        <<"报考类型"<<endl;

    Student* temp = _Data;          // 循环依次输出所有节点信息
    while(temp != NULL){
        temp->PrintInfo();
        temp = temp->_Next;
    }

}

/*
 * 计数函数
 * 统计数据库中学生数量
 * */
int StudentDatabase::count() {
    int ans = 0;        //  记录学生数量
    Student* temp = _Data;
    while(temp != NULL){        // 遍历统计
        ++ans;
        temp = temp->_Next;
    }

    return ans;
}