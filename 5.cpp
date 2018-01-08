/*
 * 数据结构课程设计
 * 题目五  单词检索统计系统
 * 姓名：李向真
 * 学号：1552970
 * */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;

void split_line( const string & str, vector<string> & words );   //单词拆分
void menu1();   //打印菜单1
void menu2();   //打印菜单2
void create_TXT(); //新建文本
void word_list(string name);  //建立单词汇总信息列表
int word_count(vector<vector<int>>& list); //单词计数
void word_locate(vector<vector<int>>& list);  //单词定位
void word_analyse(string f,string word,vector<vector<int>>& ans);  //单词分析

int main() {

    menu1();     //菜单初始化
    int choice;
    cout<<"请选择<1~4>:";
    cin>>choice;      //输入操作
    string fname;

    while(choice != 4){    //根据操作号选择操作
        switch (choice){
            case 1:
                create_TXT();    //新建文件
                break;
            case 2:
                cout<<"请输入文件名：";
                cin>>fname;
                word_list(fname);   //制作单词汇总表
                break;
            case 3:
                menu2();
                string word;

                cout<<"请输入a或b：";
                char c;
                cin>>c;
                if(c == 'a'){
                    cout<<"请输入文件名：";
                    cin>>fname;
                    cout<<"请输入要统计计数的单词：";
                    cin>>word;
                    vector<vector<int>> ans;    //记录对该单词的分析结果
                    word_analyse(fname,word,ans);
                    cout<<"单词"<<word<<"在文本文件"<<fname<<"中共出现"
                        <<word_count(ans)<<"次\n";
                }
                else if(c == 'b'){
                    cout<<"请输文件名：";
                    cin>>fname;
                    cout<<"请输入要检索的单词：";
                    cin>>word;
                    vector<vector<int>> ans;   //记录单词分析结果
                    word_analyse(fname,word,ans);
                    word_locate(ans);
                }
                else{
                    cout<<"非法输入！\n";
                }
                break;
        }
        menu1();
        cout<<"请选择<1~4>:";
        cin>>choice;
    }
    return 0;
}

/*
 * 将一行string类数据切分为单词数组
 * */
void split_line( const string & str, vector<string> & words )
{
    int i = 0;

    while( i != str.size() )
    {
        while( i != str.size() && !isalpha( str[i] ) )   //跳过非字母类型
            ++i;

        int j = i;
        while( j != str.size() && isalpha(str[j]))    //记录单词跨度
            ++j;
        if( i != j )
        {
            words.emplace_back(str.substr( i, j - i ));  //将单词记录进数组
            i = j;
        }
    }
}

/*
 * 新建txt文件
 * 文件名和文件内容由用户输入
 * */
void create_TXT(){
    string name;
    cout<<"输入要建立的文件名：";
    cin>>name;
    getchar();
    ofstream txt(name);  //新建文件
    while(1){              //循环输入文件内容
        cout<<"请输入一行文本：";
        string line;
        getline(cin,line);
        for(int i = 0;i < line.size();++i)  //全部转化为小写字母，解决大小写问题
            if(isalpha(line[i]))
                line[i] = tolower(line[i]);
        txt<<line<<endl;
        cout<<"输入结束吗？y or n :";
        char choice;
        cin>>choice;
        if(choice == 'y')
            break;
        getchar();
    }
    txt.close();        //文件建立完毕，关闭文件流
    cout<<"建立文件结束!\n";
}

/*
 * 统计文件中单词的种类以及各个单词出现的次数
 * */
void word_list(string name){
    ifstream file(name);
    string line;
    map<string,int> list;
    set<char> st;       //建立集合类型统计非文本的种类，保证无重复
    while (getline(file,line)){     //每次从文件中读入一行
        vector<string> words;
        split_line(line,words);     //调用分词函数处理改行
        for(int i = 0;i < line.size();++i){     //记录非文本种类
            if(!isalpha(line[i])&&!isspace(line[i]))
                st.insert(line[i]);
        }
        for(int i = 0;i < words.size();++i){
            if(list.find(words[i]) == list.end())   //记录新出现的单词
                list.insert(make_pair(words[i],1));
            else
                ++list[words[i]];   //统计已有单词的数量
        }

    }
    int count = 0;

    /*
     * 对统计情况进行标准化输出
     * */
    cout<<">>>>>>>>>>>"<<"单词"<<"<<<>>>>"<<"个数"<<"<<<<<<<<"<<endl;
    for(auto i = list.begin(); i != list.end(); ++i){
        for(int j = 0;j < 13-(i->first).size();++j)
            cout<<" ";
        cout<<i->first <<"         "<<i->second<<endl;
        count += i->second;
    }
    cout<<"\n>>>>>>>>>>>>>>"<<name<<"的单词个数为"<<count<<"个\n\n";
    cout<<">>>>>>>>>>>>>>"<<name<<"的非单词个数为"<<st.size()<<"种\n";

}

/*
 * 分析该单词在文件中出现的情况
 * 记录该单词在各行出现的次数
 * */
void word_analyse(string f,string word,vector<vector<int>>& ans){
    ifstream file(f);
    string line;
    vector<int> positions; //记录每个单词出现的所有位置

    while (getline(file,line)){
        int beg = 0;
        int pos = 0;
        positions.clear();
        while(beg != string::npos){ //循环查找该行中该单词的所有出现情况
            beg = line.substr(pos).find(word);
            if(beg != string::npos){
                pos += beg;
                positions.emplace_back(pos); //记录下每个出现位置
                pos += word.size();
            }
        }
        ans.emplace_back(positions);    //将该行的出现位置记录
    }
}

/*
 * 统计该单词在文件中出现次数
 * */
int word_count(vector<vector<int>>& list){
    int count = 0;
    for(int i = 0;i < list.size();++i){     //统计单词在各行数显次数，并累加
        count += list[i].size();
    }

    return count;
}

/*
 * 格式化输出单词在各行出现的情况
 * */
void word_locate(vector<vector<int>>& list){
    if(word_count(list) == 0){       //处理单词不存在的情况
        cout<<"单词不存在！\n";
        return;
    }
    for(int i = 0;i < list.size();++i){     //格式化输出单词出现情况
        if(list[i].size() != 0){
            cout<<"行号："<<i+1<<"，次数："<<list[i].size()<<"，起始位置分别为：";
            for(int j = 0;j < list[i].size();++j){
                cout<<"第 "<<list[i][j]<<"个字符 ";
            }
            cout<<endl;
        }
    }
}

/*
 * 打印主菜单
 * */
void menu1(){
    cout<<"*****************************\n";
    cout<<"****文本文件单词的检索与计数****\n"
        <<"=============================\n"
        <<"*    【1】建立文本文档        *\n"
        <<"*    【2】文本单词汇总        *\n"
        <<"*    【3】单词定位            *\n"
        <<"*    【4】退出               *\n"
        <<"=============================\n";
}

/*
 * 打印功能3的菜单
 * */
void menu2(){
    cout<<"==================================\n"
        <<"||文本文件单词字符串的统计定位及定位||\n"
        <<"||================================||\n"
        <<"||    a.   单词出现的次数           ||\n"
        <<"||                                ||\n"
        <<"||                                ||\n"
        <<"||    b.   单词出现的位置           ||\n"
        <<"||                                ||\n"
        <<"====================================\n";
}