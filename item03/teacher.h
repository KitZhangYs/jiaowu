#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 


#include"my_sql.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void Change(char* table, char* field_name, char* index_str) {
	int field = 0;
	char query_str[500] = { 0 };
	sprintf_s(query_str, "UPDATE %s SET %s %s", table, field_name, index_str);
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("修改信息出错：%s\n",mysql_error(&mysql));
		return;
	}
	printf("修改成功！\n");
	return;
}

//修改用户密码

void Teacher_ChangePassword(char* ID) {
	char t[] = "users";
	char password[225];
	char new_pass[225];
	char str[300];
	sprintf_s(str, "where user_id ='%s'", ID);
	printf("输入新密码：");
	scanf("%s", new_pass);
	sprintf_s(password, "password ='%s'", new_pass);
	Change(t, password, str);
	return;
};


//教师信息查询
void Teacher_Information(char* ID) {
	char t[] = "teachers";
	char name[] = "*";
	char str[300];
	sprintf_s(str, "where teacher_id ='%s'", ID);

	SearchInfo(t, name, str);
	return;
}


///课程信息查询
void Lessons_Information(char* ID) {
	char lesson_id[255];
	char t[] = "lessons";
	char name[] = "*";
	printf("输入课程编号：");
	scanf("%s", lesson_id);
	char str[300];
	sprintf_s(str, "where lesson_id = %s", lesson_id);

	SearchInfo(t, name, str);
	return;
};


//学生信息查询
void Students_Information(char* ID) {
	char studentid[225];
	char s[] = "students";
	char name[] = "*";
	printf("输入学生ID:  ");
	scanf("%s", studentid);
	char str[300];
	strcat(str, studentid);
	sprintf_s(str, "where student_id ='%s'", studentid);
	SearchInfo(s, name, str);
	return;
}


//选课管理（查询选课信息，修改学生成绩，返回主菜单）
void Select_Lesson_Information() {
	char id[225];
	char s[] = "student_lesson";
	char name[] = "*";
	char str[300];
	printf("输入课程序号");
	scanf("%s", id);
	sprintf_s(str, "where lesson_id = %s", id);
	SearchInfo(s, name, str);
	return;
}

void Change_Stuent_Grade() {
	char t[] = "student_lesson";
	char score[225];
	char new_score[225];
	char str[300];
	char ID[225];
	printf("输入选课序号：");
	scanf("%s", ID);
	sprintf_s(str, "where id = %s", ID);
	printf("输入成绩：");
	scanf("%s", new_score);
	sprintf_s(score, "score = %s", new_score);
	Change(t, score, str);
	return;
}


void TEACHER(char* ID, int* just) {
	while (true){
		int key;
		printf("\n\n--------------------------------教师界面-----------------------------");
		printf("\n------------------------------1.修改用户密码---------------------------");
		printf("\n------------------------------2.教师信息查询---------------------------");
		printf("\n------------------------------3.课程信息查询---------------------------");
		printf("\n------------------------------4.学生信息查询---------------------------");
		printf("\n----5.选课管理（查询选课信息，修改学生成绩，返回主菜单）-----");
		printf("\n-------------------------------请选择(1-5): -----------------------------\n");
		scanf_s("%d", &key);
		switch (key) {
		case 1:
			Teacher_ChangePassword(ID);
			break;
		case 2:
			Teacher_Information(ID);
			break;
		case 3:
			Lessons_Information(ID);
			break;
		case 4:
			Students_Information(ID);
			break;
		case 5:
			printf("\n\n----------------教师界面-------------");
			printf("\n		 1.查询选课信息");
			printf("\n		 2.修改学生成绩");
			printf("\n		 3.返回主菜单");
			printf("\n		 请选择(1-3):   ");
			scanf_s("%d", &key);
			switch (key) {
			case 1:
				Select_Lesson_Information();
				break;
			case 2:
				Change_Stuent_Grade();
				break;
			case 3:
				just = 0;
				return;
			}
		}
	}
}
