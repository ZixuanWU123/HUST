#include"E4.h"
extern const char* TestMAT(int& s);
int main(int argc, char* argv[])
{
	int s = 0;
	const char* e = TestMAT(s);
	printf("�����������ʼ����\n");
	getchar();
	printf("%s\n", e);
	getchar();
	return 0;
}
