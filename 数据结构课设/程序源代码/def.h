//���ļ�Ϊͷ�ļ����������������Ͷ���
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<ctype.h>

#define status int
#define MaxLitNum 4000
#define OK 1
#define NOPE 0
#define TRUE 1
#define FALSE 0
#define pos 1
#define neg -1

typedef struct LNode {//���ֵĽ��ṹ
	int sta;//���ֵı��
	struct LNode *next;
}LNode,*lit;
typedef struct CNode {//�Ӿ�Ľṹ
	struct CNode *next;
	struct LNode *first_l;//ָ���Ӿ��еĵ�һ������
}CNode,*cla;
typedef struct CNFG {//��ȡ��ʽCNF�ṹ
	struct CNode *root;//��һ���Ӿ�
	int c_num, l_num;//�Ӿ�����ֵ�����
}*cnf;
typedef struct Ans {//SAT�������Ĵ�
	int time, state, num;//DPLL������ʱ��SAT����Ŀɷ����ԣ����ֵĸ���
	int LiteralState[MaxLitNum+1];//�ɷ���ʱ�������ֵ�����״̬
};

//�����Ƕ�һЩ���ݵ�����
extern Ans ans;
extern int digcount;

//�����Ƕ���SAT�ĺ�������
cnf OperateCNF(FILE* fp,cnf S);
status AnswerFile(char* filename);
status DPLL(cnf S,int flag);//DPLL�㷨����
void TraverseCNF(cnf S);
status FreeCNF(cnf S);

//�����Ƕ��������ĺ�������
void PrintSudoku(int a[][9]);
void CreateSudoku(int a[][9]);
status DigHole(int a[][9], int n);
status JudgeNumber(int a[][9], int row, int col, int n);