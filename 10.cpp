/*
 * 数据结构课程设计
 * 项目十  8种排序算法的比较案例
 * 姓名：李向真
 * 学号：1552970
 * */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>

#define MAXNUM 10000    // 生成随机数的最大值
using namespace std;

clock_t start,stop;     // 记录排序起始和终止时间
double time_consuming;  // 排序时间
int swap_num = 0;       // 交换次数

int bubble_sort(int array[],int n);     // 冒泡排序
int select_sort(int array[],int n);     // 选择排序
int insert_sort(int array[],int n);     // 插入排序
int shell_sort(int array[],int n);      // 希尔排序
int quick_sort(int array[],int n);      // 快速排序
int heap_sort(int array[],int n);       // 堆排序
int merge_sort(int array[],int n);      // 归并排序
int radix_sort(int array[],int n);      // 基数排序

void menu();    // 打印主菜单

int main() {

    menu();     // 初始化菜单界面

    srand((unsigned)time(NULL));    // 置随机数种子
    int n;
    cout<<"请输入要产生的随机数的个数：";
    cin>>n;                         // 输入随机数个数

    int* array = new int[n];        // 待排数据的数组
    for(int i = 0;i < n;++i)
        array[i] = rand()%MAXNUM;   // 生成随机数据

    int choice;
    cout<<"请选择排序算法： ";
    cin>>choice;
    while(choice != 9){             // 循环输入用户选择
        int s;
        switch (choice){
            case 1:
                start = clock();
                s = bubble_sort(array,n);
                stop = clock();
                time_consuming = (double)(stop - start)/CLOCKS_PER_SEC;     // 格式化输出排序算法的性能
                cout<<"冒泡排序所用时间： ";
                cout<<time_consuming<<endl;
                cout<<"冒泡排序交换次数： "<<s<<endl<<endl;
                break;
            case 2:
                start = clock();
                s = select_sort(array,n);
                stop = clock();
                time_consuming = (double)(stop - start)/CLOCKS_PER_SEC;
                cout<<"选择排序所用时间： ";
                cout<<time_consuming<<endl;
                cout<<"选择排序交换次数： "<<s<<endl<<endl;
                break;
            case 3:
                start = clock();
                s = insert_sort(array,n);
                stop = clock();
                time_consuming = (double)(stop - start)/CLOCKS_PER_SEC;
                cout<<"直接插入排序所用时间： ";
                cout<<time_consuming<<endl;
                cout<<"直接插入排序交换次数： "<<s<<endl<<endl;
                break;
            case 4:
                start = clock();
                s = shell_sort(array,n);
                stop = clock();
                time_consuming = (double)(stop - start)/CLOCKS_PER_SEC;
                cout<<"希尔排序所用时间： ";
                cout<<time_consuming<<endl;
                cout<<"希尔排序交换次数： "<<s<<endl<<endl;
                break;
            case 5:
                start = clock();
                s = quick_sort(array,n);
                stop = clock();
                time_consuming = (double)(stop - start)/CLOCKS_PER_SEC;
                cout<<"快速排序所用时间： ";
                cout<<time_consuming<<endl;
                cout<<"快速排序交换次数： "<<s<<endl<<endl;
                break;
            case 6:
                start = clock();
                s = heap_sort(array,n);
                stop = clock();
                time_consuming = (double)(stop - start)/CLOCKS_PER_SEC;
                cout<<"堆排序所用时间： ";
                cout<<time_consuming<<endl;
                cout<<"堆排序交换次数： "<<s<<endl<<endl;
                break;
            case 7:
                start = clock();
                s = merge_sort(array,n);
                stop = clock();
                time_consuming = (double)(stop - start)/CLOCKS_PER_SEC;
                cout<<"归并排序所用时间： ";
                cout<<time_consuming<<endl;
                cout<<"归并排序比较次数： "<<s<<endl<<endl;
                break;
            case 8:
                start = clock();
                s = radix_sort(array,n);
                stop = clock();
                time_consuming = (double)(stop - start)/CLOCKS_PER_SEC;
                cout<<"基数排序所用时间： ";
                cout<<time_consuming<<endl;
                cout<<"基数排序交换次数： "<<s<<endl<<endl;
                break;
        }
        cout<<"请选择排序算法： ";
        cin>>choice;
    }

    delete[] array;

    return 0;
}


/*
 * 打印主菜单
 * */
void menu(){

    cout<<"**        排序算法比较           **\n";
    cout<<"=================================\n";
    cout<<"**       1 --- 冒泡排序         **\n";
    cout<<"**       2 --- 选择排序         **\n";
    cout<<"**       3 --- 直接插入排序      **\n";
    cout<<"**       4 --- 希尔排序         **\n";
    cout<<"**       5 --- 快速排序         **\n";
    cout<<"**       6 --- 堆排序           **\n";
    cout<<"**       7 --- 归并排序         **\n";
    cout<<"**       8 --- 基数排序         **\n";
    cout<<"**       9 --- 退出程序         **\n";
    cout<<"=================================\n\n";

}


/*
 * 冒泡排序算法
 * 输入待排数据数组和数据规模
 * 返回排序交换次数
 * 引入了交换标记 flag
 * 及时判断算法的结束
 * */
int bubble_sort(int array[],int n){

    int swap_count = 0;     // 初始化交换次数
    int flag = 0;           // 交换标记
    for(int i = 0; i < n-1; ++i){   // 遍历 n - 1 次
        for(int j = 0;j < n - i - 1; ++j){  // 每次规模减小
            if(array[j] > array[j + 1]){
                int t = array[j];
                array[j] = array[j + 1];    // 交换不满足顺序的元素
                array[j + 1] = t;
                ++swap_count;       // 记录交换次数
                flag  = 1;
            }
        }
        if(flag == 0)       // 未发生交换则提前终止算法
            break;
    }
    return swap_count;
}


/*
 * 选择排序算法
 * 输入待排数据数组和数据规模
 * 返回排序交换次数
 * */
int select_sort(int array[],int n){

    int swap_count = 0;     // 初始化交换次数
    for(int i = 0;i < n-1;++i){
        int mintag = i;         // 最小元素下标
        int min = 100001;       // 初始化最小值
        for(int j = i;j < n;++j){   // 遍历找出最小元素
            if(array[j] < min){
                min = array[j];
                mintag = j;
            }
        }
        int t = array[i];           // 最小元素交换到正确位置
        array[i] = array[mintag];
        array[mintag] = t;
        ++swap_count;           // 记录交换次数
    }

    return swap_count;
}

/*
 * 插入排序算法
 * 输入待排数据数组和数据规模
 * 返回排序交换次数
 * */
int insert_sort(int array[],int n){

    int swap_count = 0;
    for(int i = 1;i < n;++i){
        int current = array[i];
        int j;
        for(j = i;j > 0&&current < array[j - 1];--j){
            array[j] = array[j - 1];
            ++swap_count;
        }
        array[j] = current;
    }

    return swap_count;
}


/*
 * 希尔排序算法
 * 输入待排数据数组和数据规模
 * 返回排序交换次数
 * 自定义了 0，1，5，19 为希尔排序序列数
 * */
int shell_sort(int array[],int n){

    int swap_count = 0;             // 初始化交换次数
    int shell[4] = {19,5,1,0};      // 自定义希尔数
    int beg = 0;
    while(beg < 4&&shell[beg] > n)      // 确定初始希尔数
        ++beg;
    for(;beg < 4;++beg)     // 循环进行希尔排序
        for(int i = 1;i < n;++i){
            int current = array[i];
            int j;
            for(j = i;j > 0&&current < array[j - shell[beg]];j -= shell[beg]){      // 记录交换次数
                array[j] = array[j - shell[beg]];
                ++swap_count;
            }
            array[j] = current;
        }

    return swap_count;
}

/*
 * 中值函数
 * 快速排序算法的辅助函数
 * 将指定序列首，尾，中间三个数排序，并返回中间值
 * 中间值别交换到最右侧元素的左侧
 * 便于后续序列按中值大小划分的执行
 * */
int Median( int A[], int Left, int Right ) {
    int Center = (Left+Right) / 2;      // 序列中值
    if ( A[Left] > A[Center] ){         // 多次比较，交换，使三个数有序
        ++swap_num;
        swap( A[Left], A[Center] );
    }
    if ( A[Left] > A[Right] ){
        ++swap_num;
        swap( A[Left], A[Right] );
    }
    if ( A[Center] > A[Right] ){
        ++swap_num;
        swap( A[Center], A[Right] );
    }
    swap( A[Center], A[Right-1] );      // 中值藏到最右值的左侧
    ++swap_num;
    return  A[Right-1];
}

/*
 * 快速排序算法核心函数
 * 在待排元素少于100时直接执行插入排序
 * 大于100 时，将元素按中值划分，进行快排
 * */
void Qsort( int A[], int Left, int Right ) {
    int tag, Low, High;

    if ( 100 <= Right-Left ) {      // 根据数据规模判读是否需要快排
        tag = Median( A, Left, Right ); // 找出数据中值
        Low = Left; High = Right-1;
        while (1) {                     // 按数据段中值划分元素
            while ( A[++Low] < tag ) ;
            while ( A[--High] > tag ) ;
            if ( Low < High ){
                ++swap_num;
                swap( A[Low], A[High] );
            }
            else break;
        }
        swap( A[Low], A[Right-1] );
        ++swap_num;
        Qsort( A, Left, Low-1 );        // 对中值左右数据段递归执行快排
        Qsort( A, Low+1, Right );
    }
    else insert_sort( A+Left, Right-Left+1 );   // 数据量较小直接执行快排
}

/*
 * 快速排序算法接口
 * 适配其他算法接口
 * 输入待排数据数组和数据规模
 * 返回排序交换次数
 * */
int quick_sort( int array[], int n ) {
    Qsort( array, 0, n-1 );     // 调用快排递归算法
    return swap_num;
}


/*
 * 向下过滤算法
 * 堆排序辅助算法
 * 在左右子树均已经保持的堆序的情况下
 * 调节根节点位置使整棵树保持堆序
 * */
void percdown(int array[], int position, int n){
    int parent,child;

    int current = array[position];      // 记录根元素
    for(parent = position; parent*2 + 1 <n; parent = child){        // 向下过滤寻找插入位置
        child = parent*2 + 1;
        if(child < n-1&&array[child] < array[child + 1])        // 找到左右子女中的较大者
            ++child;
        if(array[child] > current){         // 向下过滤
            array[parent] = array[child];
            ++swap_num;
        }

        else
            break;
    }
    array[parent] = current;    // 插到合适位置
}

/*
 * 堆排序算法
 * 输入待排数据数组和数据规模
 * 返回排序交换次数
 * 内部调用向下过滤算法实现建堆以及删除操作
 * */
int heap_sort(int array[], int n){

    swap_num = 0;       // 初始化交换次数
    for(int i = n/2-1;i >= 0;--i){
        percdown(array,i,n);        // 将数据调整为最大堆
    }
    for(int i = n-1;i > 0;--i){     // 每次删除堆顶元素，将其调到数组尾部
        swap(array[0],array[i]);
        ++swap_num;
        percdown(array,0,i);        // 向下过滤保持堆序
    }
    return swap_num;
}


/*
 * 归并函数
 * 归并排序算法辅助函数
 * 将两个有序序列归并为一个
 * */
void merge(int array[],int temp_array[],int left,int right,int right_end){
    int left_end = right - 1;   // 记录左侧数组终止位置
    int current = left;     // 记录辅助数组中元素位置
    int size = right_end - left + 1;    // 数据规模
    while(left <= left_end&&right <= right_end){        // 从左右两序列头开始比较遍历
        ++swap_num;
        if(array[left] <= array[right])
            temp_array[current++] = array[left++];
        else
            temp_array[current++] = array[right++];

    }

    while (left <= left_end){       // 处理左右数组长度不同的情况
        temp_array[current++] = array[left++];
    }
    while (right <= right_end){
        temp_array[current++] = array[right++];
    }

    for(int i = 0;i < size;++i,--right_end){           // 将排好的序列写入原数组
        array[right_end] = temp_array[right_end];
    }
}
/*
 * 归并排序算法
 * 递归将左右序列排序
 * 然后将其合并
 * 调用 merge 函数
 * */
void msort(int array[],int temp_array[],int left, int right_end){

    if(left < right_end){   // 判断序列合法行
        int center = (left + right_end)/2;
        msort(array,temp_array,left,center);        // 递归处理左右子列
        msort(array,temp_array,center + 1,right_end);
        merge(array,temp_array,left,center + 1,right_end);  // 合并左右子列
    }
}

/*
 * 归并排序算法接口
 * 适配其他排序算法接口
 * 输入待排数据数组和数据规模
 * 返回排序交换次数
 * */
int merge_sort(int array[],int n){
    swap_num = 0;   // 初始化交换次数
    int* temp_array = new int[n + 1];   // 开一个辅助数组，用于合并
    msort(array,temp_array,0,n-1);  // 调用归并算法
    delete[] temp_array;
    return swap_num;
}

/*
 * 基数排序算法
 * 输入待排数据数组和数据规模
 * 返回排序交换次数
 * 按低位到高位的顺序排
 * */
int radix_sort(int array[], int n)
{
    int *temp = new int[n];     // 辅助数组，存储过程中的数据集
    int bucket[10];         // 0-9 十个桶
    int i, j, k;
    int radix = 1;          // 排序位次
    for(i = 1; i <= 5; i++)
    {
        for(j = 0; j < 10; j++)     // 初始化桶
            bucket[j] = 0;
        for(j = 0; j < n; j++)      // 桶排序
        {
            k = (array[j] / radix) % 10;
            bucket[k]++;
        }
        for(j = 1; j < 10; j++)     // 算出个桶元素在辅助数组中的位次
            bucket[j] = bucket[j - 1] + bucket[j];
        for(j = n - 1; j >= 0; j--)     // 桶中数据倒入辅助数组
        {
            k = (array[j] / radix) % 10;
            temp[bucket[k] - 1] = array[j];
            bucket[k]--;
        }
        for(j = 0; j < n; j++)      // 辅助数组数据写回原数据集
            array[j] = temp[j];
        radix = radix * 10;     // 增加排序位次
    }
    delete[]temp;

    return 0;
}







