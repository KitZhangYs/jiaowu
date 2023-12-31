#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#include"my_sql.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//1.修改用户密码
void Student_ChangePassword(char* ID) {
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
}

//课程信息查询
void Lessons_Informations(char* ID) {
	char lesson_id[255];
	char t[] = "lessons";
	char name[] = "*";
	printf("输入课程编号：");
	scanf_s("%s", lesson_id,255);
	char str[300];
	sprintf_s(str, "where lesson_id = %s", lesson_id);
	SearchInfo(t, name, str);
	return;
};

//授课信息查询
void Teacher_Lessons(char* ID) {
	char id[225];
	char s[] = "teacher_lessons";
	char name[] = "*";
	printf("输入课程序号");
	scanf_s("%s", id,225);
	char str[300];
	sprintf_s(str, "where lesson_id = %s", id);
	SearchInfo(s, name, str);
	return;
}

//选课信息查询
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
		printf("\n\n--------------------------------学生界面-----------------------------");
		printf("\n------------------------------1.修改用户密码---------------------------");
		printf("\n------------------------------2.课程信息查询---------------------------");
		printf("\n------------------------------3.授课信息查询---------------------------");
		printf("\n------------------------------4.选课信息查询---------------------------");
		printf("\n------------------------------5.退出系统-------------------------------");
		printf("\n-------------------------------请选择(1-5): -----------------------------\n");
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
