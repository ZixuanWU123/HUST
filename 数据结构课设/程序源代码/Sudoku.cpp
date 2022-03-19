//Sudoku.cpp�����ļ��Ƕ�������ʵ��
#include"def.h"
#define MaxLit 729
#define CORRECT 0
#define WRONG -1
#define COL 9
#define ROW 9
#define tran(i,j,k) i*81+j*9+k
//int Digged[ROW][COL];

void PrintSudoku(int a[9][9]){//�������
    int i, j;
    printf("\n\n\t\t\t\t��������:\n");
    printf("\t\t\t-------------------------------\n");
	for (i = 0; i < 9; i++) {
		printf("\t\t\t");
		for (j = 0; j < 9; j++) {
			if (j % 3 == 0) { printf("|"); }
			if (a[i][j]) { printf("%2d ", a[i][j]); }
			else { printf(" _ "); }
		}
		printf("|\n");
		if ((i + 1) % 3 == 0) { printf("\t\t\t-------------------------------\n"); }
	}
}

status JudgeNumber(int a[][COL], int row, int col, int n){//�ж���������Ƿ����Ҫ��
    int i, j;
    // �ж����Ƿ��ظ�
    for (i = 0; i < 9; i++) {
        if (a[row][i] == n) { return FALSE; }
    }
    // �ж����Ƿ��ظ�
    for (j = 0; j < 9; j++) {
        if (a[j][col] == n) { return FALSE; }
    }
    // �ж�����С�Ź����Ƿ��ظ�
    int x = (row / 3) * 3;
    int y = (col / 3) * 3;
    for (i = x; i < x + 3; i++) {
        for (j = y; j < y + 3; j++) {
            if (a[i][j] == n) { return FALSE; }
        }
    }
    return OK;
}

int Fill(int a[][COL], int i, int j) {//�ݹ��������Ԫ��
	if (i < ROW && j < COL) {
		int x, y, k, flag = 0;
		int temp[COL + 1] = { CORRECT };
		for (x = 0; x < i; x++) { temp[a[x][j]] = WRONG; }
		for (x = 0; x < j; x++) { temp[a[i][x]] = WRONG; }
		for (x = i / 3 * 3; x <= i; x++) {
			if (x == i) {
				for (y = j / 3 * 3; y < j; y++) { temp[a[x][y]] = WRONG; }
			}
			else {
				for (y = j / 3 * 3; y < j / 3 * 3 + 3; y++) { temp[a[x][y]] = WRONG; }
			}	
		}
		for (k = 1; k <= COL && flag == 0; k++) {
			if (temp[k] == CORRECT) {
				flag = 1;
				a[i][j] = k;
				if (j == COL - 1 && i != ROW - 1) {
					if (Fill(a, i + 1, 0) == CORRECT) { return CORRECT; }
					else { flag = 0; }
				}
				else if (j != COL - 1) {
					if (Fill(a, i, j + 1) == CORRECT) { return CORRECT; }
					else { flag = 0; }
				}
			}
		}
		if (!flag) {
			a[i][j] = 0;
			return WRONG;
		}
	}
	return CORRECT;
}

void CreateSudoku(int a[][COL]) { //��������
	//������ɵ�һ��
	int i, j;
	srand((unsigned)time(nullptr));
	for (i = 0; i < COL; i++) {
		a[0][i] = rand() % 9 + 1;
		j = 0;
		while (j < i) {
			if (a[0][i] == a[0][j]) {
				a[0][i] = rand() % 9 + 1;
				j = 0;
			}
			else j++;
		}
	}
	//�ݹ����ɺ�i��
	Fill(a, 1, 0);
}

cnf AddSew(cnf s, int i) {//��i��Ϊ���Ӿ���뵽S��
	cla c = (cla)malloc(sizeof(CNode));
	lit l = (lit)malloc(sizeof(LNode));
	l->sta = i; l->next = NULL;
	c->first_l = l;
	c->next = s->root;
	s->root = c;
	s->c_num++;
	return s;
}

cnf SudokuToCNF(int a[][COL]) {//��������ת��Ϊcnf
	FILE* fp;
	cnf c;
	fp = fopen("D:\SudokuRule.cnf", "r");
	c = (cnf)malloc(sizeof(CNFG));
	c->root = NULL;
	OperateCNF(fp, c);
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (a[i][j]) { c = AddSew(c, tran(i, j, a[i][j])); }
		}
	}
	return c;
}

status CertainAnwser(int a[][COL]) {//�ж��ڶ���������Ƿ��н�
    cnf s = SudokuToCNF(a);
    return DPLL(s, 1);
}

status WhetherToDig(int a[][COL], int n, int m, int k) {//�ж��ڿպ��Ƿ���Ψһ��
	for (int i = 1; i <= 9; i++) {
		if (i != k && JudgeNumber(a, n, m, i)) {
			a[n][m] = i;
			if (CertainAnwser(a)) {
				a[n][m] = k;
				return NOPE;
			}
		}
	}
	a[n][m] = 0;
	return OK;
}

status DigHole(int a[][COL],int n) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (!n) { return OK; }
			if (WhetherToDig(a, i, j, a[i][j])) { n--; }
		}
	}
	if (n) { return NOPE; }
}