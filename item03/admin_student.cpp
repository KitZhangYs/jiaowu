#include "admin.h"


//展示全部学生信息
void PrintAllStudents() {
	strcpy(table, "students");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("学号            姓名            性别            班级\n");
	SearchInfo(table, key, index_str);
	return;
}

//查询学生信息
void SearchStudent() {
	char uid[100];
	printf("请输入需要查找的学生id：");
	scanf_s("%s", uid, 100);
	strcpy(table, "students");
	strcpy(key, "*");
	sprintf(index_str, "where student_id = \"%s\"", uid);//拼接where子句
	printf("学号            姓名            性别            班级\n");
	SearchInfo(table, key, index_str);
	return;
}


//创建学生
void CreateStudent() {
	char uid[200], name[200] = { 0 }, pwd[200];
	int p = 3, sex = 0, n = 0;
	printf("请输入新学生的学号:");
	scanf_s("%s", uid, 200);
	printf("请输入新学生的名称：");
	scanf_s("%s", name, 200);
	printf("请输入新学生的密码：");
	scanf_s("%s", pwd, 200);
	printf("请输入新学生的性别(0:男,1:女)：");
	scanf_s("%d", &sex);
	char querry_str[500] = { 0 };
	int Class = 0;
	printf("请输入新用户的班级：");
	scanf_s("%d", &Class);
	sprintf(querry_str, "insert into students (student_id,name,sex,class) values ('%s','%s',%d,%d)", uid, name, sex, Class);//拼接insert语句
	n = mysql_real_query(&mysql, querry_str, strlen(querry_str));
	if (n) {
		printf("%s\n", mysql_error(&mysql));
		return;
	}
	sprintf(querry_str, "insert into users ( user_id, password, per ) VALUES (\"%s\", \"%s\", %d) ", uid, pwd, p);//拼接insert语句
	n = mysql_real_query(&mysql, querry_str, strlen(querry_str));
	if (n) {
		printf("%s\n", mysql_error(&mysql));
		return;
	}
	printf("新建学生成功！\n");
	return;
}

//删除学生
void DeleteStudent() {
	printf("\n请输入要删除的学生id：");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "delete from users where user_id = '%s'", uid);//拼接delete子句
	int n = 0;
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (n) {
		printf("\n删除学生失败：%s\n", mysql_error(&mysql));
		return;
	}
	sprintf(query_str, "delete from students where student_id = '%s'", uid);
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (n) {
		printf("\n删除学生失败：%s\b", mysql_error(&mysql));
		return;
	}
	printf("\n删除成功！\n");
	return;
}

//修改学生信息
void UpdateStudent() {
	printf("\n请输入要修改的学号：");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "select * from students where student_id = '%s'", uid);

	//在users表中查询用户信息存入row中
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
		sprintf(query_str, "update students set name = '%s' where student_id = '%s'", name, uid);
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
		sprintf(query_str, "update students set sex = '%s' where student_id = '%s'", sex, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("班级(%s,放弃修改该项请输入n)：", row[3]);
	char Class[200] = { 0 };
	scanf_s("%s", Class, 200);
	if (strcmp(Class, "n")) {
		sprintf(query_str, "update students set class = '%s' where student_id = '%s'", Class, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("\n修改成功！\n");
	return;
}