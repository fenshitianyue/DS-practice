#include <stdio.h>
#include <string.h>
#include <math.h>

int top = -1;//top变量时刻表示栈顶元素所在位置

void push(char * a, char elem){
	a[++top] = elem;
}
void pop(char * a){
	if (top == -1) {
		return;
	}
	//输出时要按照正确的格式显示给用户
	if (a[top] >= 10) {
		printf("%c", a[top] + 55);
	}
	else{
		printf("%d", a[top]);
	}
	top--;
}
//将各进制数转换成十进制数
int scaleFun(char * data, int system){
	int size = (int)strlen(data) - 1;
	int scale_10_data = 0;
	int i;
	for (i = size; i >= 0; i--) {
		int temp;
		//如果是字符0~9，则-48后刚好为数字0~9
		if (data[i] >= 48 && data[i] <= 57) {
			temp = data[i] - 48;
		}
		//否则则为字母，'A'- 55 = 10,以此类推
		else{
			temp = data[i] - 55;
		}
		scale_10_data += temp * pow(system, size - i);
	}
	return scale_10_data;
}
int main() {
	char data[100];
	printf("---进制转换器---\n");
	printf("请输入原数据的进制（2-36）:");
	int system;
	scanf("%d", &system);
	getchar();//清空输入缓冲区中的'\n'
	printf("请输入要转换的数据：");
	scanf("%s", data);
	getchar();//清空输入缓冲区中的'\n'
	int system_10_data = scaleFun(data, system);
	printf("请输入转换后的数据的进制：");
	int newSystem;
	scanf("%d", &newSystem);
	getchar();//同理
	while (system_10_data / newSystem) {
		push(data, system_10_data%newSystem);
		system_10_data /= newSystem;
	}
	push(data, system_10_data%newSystem);
	printf("转换后的结果为：");
	while (top != -1) {
		pop(data);
	}
	return 0;
}