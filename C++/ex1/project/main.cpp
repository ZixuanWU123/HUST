#include"E1.h"
extern const char* TestQueue(int& s);
int main() {
	int s = 0;
	const char* e = TestQueue(s);
	printf("�����������ʼ����\n");
	getchar();
	printf("%s\n", e);
	getchar();
	return 0;
}