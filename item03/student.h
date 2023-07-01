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
}

//课程信息查询
void Lessons_Informations(char* ID) {
	char lesson_id[255];
	char t[] = "lessons";
	char name[] = "*";
	printf("输入课程编号：");
	scanf_s("%s", lesson_id);
	char str[300];
	sprintf_s(str, "where lesson_id ='%s'", lesson_id);
	SearchInfo(t, name, str);
};

//授课信息查询
void Teacher_Lessons(char* ID) {
	char id[225];
	char s[] = "teacher_lessons";
	char name[] = "*";
	printf("输入课程序号");
	scanf_s("%s", id);
	char str[300];
	sprintf_s(str, "where id ='%s'", id);
	SearchInfo(s, name, str);
}

//选课信息查询
void Select_Lesson_Information(char* ID) {
	char s[] = "Student_Lessons";
	char name[] = "*";
	char str[300] = "where id = ";
	strcat(str, ID);
	SearchInfo(s, name, str);
}

void STUDENTS(char* ID, int* just) {
	char key;
	printf("\n\n--------------------------------学生界面-----------------------------");
	printf("\n------------------------------1.修改用户密码---------------------------");
	printf("\n------------------------------2.课程信息查询---------------------------");
	printf("\n------------------------------3.授课信息查询---------------------------");
	printf("\n------------------------------4.选课信息查询---------------------------");
	printf("\n------------------------------5.返回主菜单------------------------------");
	printf("\n-------------------------------请选择(1-5): -----------------------------\n");
	scanf_s("%c", &key);
	getchar();//吸收回车
	switch (key) {
	case '1':Student_ChangePassword(ID);
		break;
	case'2':Lessons_Informations(ID);
		break;
	case'3':Teacher_Lessons(ID);
		break;
	case'4':Select_Lesson_Information(ID);
		break;
	case'5':just = 0;
		break;
	}

}
