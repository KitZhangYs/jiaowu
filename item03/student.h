#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#include"my_sql.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//1.�޸��û�����
void Student_ChangePassword(char* ID) {
	char t[] = "users";
	char password[225];
	char new_pass[225];
	char str[300];
	sprintf_s(str, "where user_id ='%s'", ID);
	printf("���������룺");
	scanf("%s", new_pass);
	sprintf_s(password, "password ='%s'", new_pass);
	Change(t, password, str);
	return;
}

//�γ���Ϣ��ѯ
void Lessons_Informations(char* ID) {
	char lesson_id[255];
	char t[] = "lessons";
	char name[] = "*";
	printf("����γ̱�ţ�");
	scanf_s("%s", lesson_id,255);
	char str[300];
	sprintf_s(str, "where lesson_id = %s", lesson_id);
	SearchInfo(t, name, str);
	return;
};

//�ڿ���Ϣ��ѯ
void Teacher_Lessons(char* ID) {
	char id[225];
	char s[] = "teacher_lessons";
	char name[] = "*";
	printf("����γ����");
	scanf_s("%s", id,225);
	char str[300];
	sprintf_s(str, "where lesson_id = %s", id);
	SearchInfo(s, name, str);
	return;
}

//ѡ����Ϣ��ѯ
void Select_Lesson_Information(char* ID) {
	char s[] = "student_lesson";
	char name[] = "*";
	char str[300] = {0};
	sprintf(str, "where student_id = '%s'", ID);
	SearchInfo(s, name, str);
	return;
}

void STUDENTS(char* ID, int* just) {
	while (true){
		int key;
		printf("\n\n--------------------------------ѧ������-----------------------------");
		printf("\n------------------------------1.�޸��û�����---------------------------");
		printf("\n------------------------------2.�γ���Ϣ��ѯ---------------------------");
		printf("\n------------------------------3.�ڿ���Ϣ��ѯ---------------------------");
		printf("\n------------------------------4.ѡ����Ϣ��ѯ---------------------------");
		printf("\n------------------------------5.�˳�ϵͳ-------------------------------");
		printf("\n-------------------------------��ѡ��(1-5): -----------------------------\n");
		scanf_s("%d", &key);
		switch (key) {
		case 1:
			Student_ChangePassword(ID);
			break;
		case 2:
			Lessons_Informations(ID);
			break;
		case 3:
			Teacher_Lessons(ID);
			break;
		case 4:
			Select_Lesson_Information(ID);
			break;
		case 5:
			just = 0;
			return;
		}
	}
}
