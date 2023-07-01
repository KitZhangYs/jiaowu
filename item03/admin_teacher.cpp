#include "admin.h"

//展示所有教师
void PrintAllTeachers() {
	strcpy(table, "teachers");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("教师号          姓名            性别            学位            职称\n");
	SearchInfo(table, key, index_str);
	return;
}

//查找指定教师
void SearchTeacher() {
	char uid[100];
	printf("请输入需要查找的教师id：");
	scanf_s("%s", uid, 100);
	strcpy(table, "teachers");
	strcpy(key, "*");
	sprintf(index_str, "where teacher_id = \"%s\"", uid);//拼接where子句
	printf("学号            姓名            性别            班级\n");
	SearchInfo(table, key, index_str);
	return;
}

//创建新教师
void CreateTeacher() {
	char uid[200], name[200] = { 0 }, pwd[200],xw[200],zc[200];
	int p = 2, sex = 0, n = 0;
	printf("请输入新教师的教师号:");
	scanf_s("%s", uid, 200);
	printf("请输入新教师的名称：");
	scanf_s("%s", name, 200);
	printf("请输入新教师的密码：");
	scanf_s("%s", pwd, 200);
	printf("请输入新教师的性别(0:男,1:女)：");
	scanf_s("%d", &sex);
	char querry_str[500] = { 0 };
	printf("请输入新用户的职称：");
	scanf_s("%s", zc, 200);
	printf("请输入新用户的学位：");
	scanf_s("%s", xw, 200);
	sprintf(querry_str, "insert into teachers (teacher_id,name,sex,degree,zhich) VALUES ('%s','%s',%d,'%s','%s')", uid, name, sex, xw, zc);//拼接insert语句
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
	printf("新建教师成功！\n");
	return;
}

//删除教师
void DeleteTeacher() {
	printf("\n请输入要删除的教师id：");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "delete from users where user_id = '%s'", uid);//拼接delete子句
	int n = 0;
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (n) {
		printf("\n删除教师失败：%s\n", mysql_error(&mysql));
		return;
	}
	sprintf(query_str, "delete from teachers where teacher_id = '%s'", uid);
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (n) {
		printf("\n删除教师失败：%s\b", mysql_error(&mysql));
		return;
	}
	printf("\n删除成功！\n");
	return;
}

//修改教师信息
void UpdateTeacher() {
	printf("\n请输入要修改的教师号：");
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

	printf("职称(%s,放弃修改该项请输入n)：",row[4]);
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