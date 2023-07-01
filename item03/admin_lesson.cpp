#include "admin.h"

//展示所有课程列表
void PrintAllTeachers() {
	strcpy(table, "lessons");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("\n课程号          课程名称            课程性质            课程学时            开课学期\n");
	SearchInfo(table, key, index_str);
	return;
}

//查找指定课程
void SearchTeacher() {
	char uid[100];
	printf("\n请输入需要查找的课程号：");
	scanf_s("%s", uid, 100);
	strcpy(table, "lessons");
	strcpy(key, "*");
	sprintf(index_str, "where lessons = \"%s\"", uid);//拼接where子句
	printf("\n课程号          课程名称            课程性质            课程学时            开课学期\n");
	SearchInfo(table, key, index_str);
	return;
}

//创建新课程
void CreateTeacher() {
	char name[200] = { 0 }, contact[200] = {0};
	int learn_time = 0,semester = 0, n = 0;
	printf("请输入新课程的名称：");
	scanf_s("%s", name, 200);
	char querry_str[500] = { 0 };
	printf("请输入新课程的性质：");
	scanf_s("%s", contact, 200);
	printf("请输入新课程的学时：");
	scanf_s("%d", &learn_time);
	printf("请输入新课程的开课学期：");
	scanf_s("%d", &semester);
	sprintf(querry_str, "insert into lessons (name,contact,learn_time,semester) VALUES ('%s','%s',%d,%d)",  name, contact, learn_time, semester);//拼接insert语句
	n = mysql_real_query(&mysql, querry_str, strlen(querry_str));
	if (n) {
		printf("%s\n", mysql_error(&mysql));
		return;
	}
	printf("新建课程成功！\n");
	return;
}

//删除课程
void DeleteTeacher() {
	printf("\n请输入要删除的课程号：");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	int ret = 0;
	MYSQL_RES *res1,*res2;
	scanf_s("%s", uid, 200);

	sprintf(query_str, "select * from teacher_lessons where lesson_id = '%s'", uid);//拼接查询授课语句
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息出错！\n");
		return;
	}
	res1 = mysql_store_result(&mysql);

	sprintf(query_str,"select * from student_lessons where lesson_id = '%s'",uid);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息出错！\n");
		return;
	}
	res2 = mysql_store_result(&mysql);

	if ((!mysql_num_rows(res1))&&(!mysql_num_rows(res2)) ){
		sprintf(query_str, "delete from lessons where lesson_id = '%s'", uid);//拼接delete子句
		int n = 0;
		n = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (n) {
			printf("\n删除课程失败：%s\n", mysql_error(&mysql));
			return;
		}
		printf("\n删除成功！\n");
		return;
	}
	printf("该课程正被选修或授课！\n");
	return;
}

//修改课程信息
void UpdateTeacher() {
	printf("\n请输入要修改的课程号：");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "select * from teachers where teacher_id = '%s'", uid);

	//在teachers表中查询用户信息存入row中
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息出错\n");
		return;
	}
	MYSQL_RES* res;
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("符合条件的信息不存在\n");
		return;
	}
	MYSQL_ROW row;
	row = mysql_fetch_row(res);

	printf("姓名(%s,放弃修改该项请输入n)：", row[1]);
	char name[200] = { 0 };
	scanf_s("%s", name, 200);
	if (strcmp(name, "n")) {
		sprintf(query_str, "update teachers set name = '%s' where teacher_id = '%s'", name, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("性别(%s,放弃修改该项请输入n)：", row[2]);
	char sex[200] = { 0 };
	scanf_s("%s", sex, 200);
	if (strcmp(sex, "n")) {
		sprintf(query_str, "update teachers set sex = '%s' where teacher_id = '%s'", sex, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("学历(%s,放弃修改该项请输入n)：", row[3]);
	char xw[200] = { 0 };
	scanf_s("%s", xw, 200);
	if (strcmp(xw, "n")) {
		sprintf(query_str, "update teachers set degree = '%s' where teacher_id = '%s'", xw, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("职称(%s,放弃修改该项请输入n)：", row[4]);
	char zc[200] = { 0 };
	scanf_s("%s", zc, 200);
	if (strcmp(zc, "n")) {
		sprintf(query_str, "update teachers set zhich = '%s' where teacher_id = '%s'", zc, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("\n修改成功！\n");
	return;
}