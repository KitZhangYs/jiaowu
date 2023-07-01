#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 


#include"my_sql.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void Change(char* table, char* field_name, char* index_str) {

	MYSQL_RES* res;
	MYSQL_ROW row;
	int field = 0;
	char query_str[500] = { 0 };
	sprintf_s(query_str, "UPDATE %s SET %s %s", table, field_name, index_str);
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("�޸��������");
		return;
	}
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("������������Ϣ������\n");
		return;
	}
}

//�޸��û�����

void Teacher_ChangePassword(char* ID) {
	char t[] = "users";
	char password[225];
	char new_pass[225];
	char str[300];
	sprintf_s(str, "where user_id ='%s'", ID);
	printf("���������룺");
	scanf("%s", new_pass);
	sprintf_s(password, "password ='%s'", new_pass);
	Change(t, password, str);

};


//��ʦ��Ϣ��ѯ
void Teacher_Information(char* ID) {
	char t[] = "teachers";
	char name[] = "*";
	char str[300];
	sprintf_s(str, "where teacher_id ='%s'", ID);

	SearchInfo(t, name, str);
}


///�γ���Ϣ��ѯ
void Lessons_Information(char* ID) {
	char lesson_id[255];
	char t[] = "lessons";
	char name[] = "*";
	printf("����γ̱�ţ�");
	scanf("%s", lesson_id);
	char str[300];
	sprintf_s(str, "where lesson_id ='%s'", lesson_id);

	SearchInfo(t, name, str);
};


//ѧ����Ϣ��ѯ
void Students_Information(char* ID) {
	char studentid[225];
	char s[] = "students";
	char name[] = "*";
	printf("����ѧ��ID:  ");
	scanf("%s", studentid);
	char str[300];
	strcat(str, studentid);
	sprintf_s(str, "where student_id ='%s'", studentid);
	SearchInfo(s, name, str);
}


//ѡ�ι�����ѯѡ����Ϣ���޸�ѧ���ɼ����������˵���
void Select_Lesson_Information() {
	char id[225];
	char s[] = "student_lesson";
	char name[] = "*";
	char str[300];
	printf("����γ����");
	scanf("%s", id);
	sprintf_s(str, "where id ='%s'", id);
	SearchInfo(s, name, str);
}

void Change_Stuent_Grade() {
	char t[] = "student_lesson";
	char score[225];
	char new_score[225];
	char str[300];
	char ID[225];
	printf("����ѧ��ѧ�ţ�");
	scanf("%s", ID);
	sprintf_s(str, "student_id ='%s'", ID);
	printf("����ɼ���");
	scanf("%s", new_score);
	sprintf_s(score, "score ='%s'", new_score);
	Change(t, score, str);

}


void TEACHER(char* ID, int* just) {
	char key;
	printf("\n\n--------------------------------��ʦ����-----------------------------");
	printf("\n------------------------------1.�޸��û�����---------------------------");
	printf("\n------------------------------2.��ʦ��Ϣ��ѯ---------------------------");
	printf("\n------------------------------3.�γ���Ϣ��ѯ---------------------------");
	printf("\n------------------------------4.ѧ����Ϣ��ѯ---------------------------");
	printf("\n----5.ѡ�ι�����ѯѡ����Ϣ���޸�ѧ���ɼ����������˵���-----");
	printf("\n-------------------------------��ѡ��(1-5): -----------------------------\n");
	scanf_s("%c", &key);
	getchar();//���ջس�
	switch (key) {
	case '1':Teacher_ChangePassword(ID);
		break;
	case'2':Teacher_Information(ID);
		break;
	case'3':Lessons_Information(ID);
		break;
	case'4':Students_Information(ID);
		break;
	case'5':
		printf("\n\n----------------��ʦ����-------------");
		printf("\n		 1.��ѯѡ����Ϣ");
		printf("\n		 2.�޸�ѧ���ɼ�");
		printf("\n		 3.�������˵�");
		printf("\n		 ��ѡ��(1-3):   ");
		scanf_s("%c", &key);
		switch (key) {
		case'1':Select_Lesson_Information();
			break;
		case'2':Change_Stuent_Grade();
			break;
		case'3':just = 0;
			break;
		}
	}
}
