#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Queue {
    int* const  elems;	   	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	  	//elems��������Ԫ�ظ���max
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
};