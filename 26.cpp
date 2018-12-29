#include <stdio.h>
#include <assert.h>

#define SIZE 26 //方便以后修改容量
typedef char DataType;  //方便以后修改存储类型(不用宏是因为宏没有类型检查)

/*定义顺序表的元素类型
*分为数据域和标志域两部分，数据域存储字母
*标志位为1，表示该字母有效；为0则反之
*/
typedef struct ElemType{
  DataType _data;
  int _flag;
}ElemType;

/*定义顺序表类型*/
typedef struct Node{
  ElemType _elem[SIZE];
}Table;

/*顺序表的初始化
*这里直接将顺序表的数据与填充上字母
*将标志位都设置为无效
*/
void Init(Table* table){
  assert(table);
  for(int i = 0; i < 26; ++i){
    table->_elem[i]._data = 'a' + i; //填充数据域
    table->_elem[i]._flag = 0; //将标志位置 0
  }
}
//添加字母
void Add(Table* table, DataType ch){
  assert(table); 
  table->_elem[ch-'a']._flag = 1; 
}
//删除字母
void Del(Table* table, DataType ch){
  assert(table);
  table->_elem[ch-'a']._flag = 0;
}
//打印顺序表
void Print(const Table* table){
  assert(table);
  for(int i = 0; i < 26; ++i){
    if(table->_elem[i]._flag != 0){
      printf("%c ", table->_elem[i]._data);
    }
  }
  printf("\n");
}

//测试用例
int main() {
  Table table;
  Init(&table);
  Add(&table, 'a');
  Add(&table, 'b');
  Add(&table, 'c');
  Add(&table, 'd');
  Del(&table, 'a');
  Del(&table, 'b');
  Del(&table, 'c');
  Del(&table, 'd');
  Print(&table);
  return 0;
}