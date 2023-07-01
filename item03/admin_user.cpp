#include "admin.h"

char table[100],  index_str[200],  key[100];

//展示所有用户信息
void PrintAllUsers() {
	strcpy(table, "users");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("用户名              密码                权限\n");
	SearchInfo(table, key, index_str);
	return;
}

//查询用户
void SearchUser() {
	char uid[100];
	printf("请输入需要查找的用户id：");
	scanf_s("%s", uid, 100);
	strcpy(table, "users");
	strcpy(key, "*");
	sprintf(index_str, "where user_id = \"%s\"", uid);//拼接where子句
	printf("用户名              密码                权限\n");
	SearchInfo(table, key, index_str);
	return;
}

//创建用户并同步到教师和学生表中
void CreateUser() {
	char uid[200], name[200] = {0}, pwd[200];
	int p = 0,sex = 0,n=0;
	printf("请输入新用户的用户名:");
	scanf_s("%s", uid, 200);
	printf("请输入新用户的权限(2:教师,3:学生)：");
	scanf_s("%d", &p);
	printf("请输入新用户的名称：");
	scanf_s("%s", name, 200);
	printf("请输入新用户的密码：");
	scanf_s("%s", pwd, 200);
	printf("请输入新用户的性别(0:男,1:女)：");
	scanf_s("%d", &sex);	
	char querry_str[500] = { 0 };
	sprintf(querry_str, "insert into users ( user_id, password, per ) VALUES (\"%s\", \"%s\", %d) ", uid, pwd, p);//拼接insert语句
	n = mysql_real_query(&mysql, querry_str, strlen(querry_str));
	if (n) {
		printf("%s\n",mysql_error(&mysql));
		return;
	}
	if (p == 2) {
		char zc[200] = { 0 }, xw[200] = {0};
		printf("请输入新用户的职称：");
		scanf_s("%s", zc, 200);
		printf("请输入新用户的学位：");
		scanf_s("%s", xw, 200);
		sprintf(querry_str, "insert into teachers (teacher_id,name,sex,degree,zhich) VALUES ('%s','%s',%d,'%s','%s')", uid, name, sex, xw, zc);//拼接insert语句
		n = mysql_real_query(&mysql, querry_str,strlen(querry_str));
		if (n) {
			printf("%s\n",mysql_error(&mysql));
			return;
		}
	}

	if (p == 3) {
		int Class = 0;
		printf("请输入新用户的班级：");
		scanf_s("%d", &Class);
		sprintf(querry_str, "insert into students (student_id,name,sex,class) values ('%s','%s',%d,%d)", uid, name, sex, Class);//拼接insert语句
		int n = 0;
		n = mysql_real_query(&mysql, querry_str, strlen(querry_str));
		if (n) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("创建用户成功！\n");
	return;
}

//删除用户
void DeleteUser() {
	printf("请输入要删除的用户id：");
	char uid[200]={0}, query_str[500] = {0};
	scanf_s("%s", uid, 200);
	sprintf(query_str, "delete from users where user_id = '%s'", uid);//拼接delete子句
	int n = 0;
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (n) {
		printf("删除用户失败：%s\n", mysql_error(&mysql));
		return;
	}
	sprintf(query_str, "delete from students where student_id = '%s'", uid);
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	sprintf(query_str, "delete from teachers where teacher_id = '%s'", uid);
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	printf("删除用户成功！\n");
	return;

}

//修改用户信息
void UpdateUser() {
	printf("请输入要修改的用户名：");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "select * from users where user_id = '%s'", uid);

	//在users表中查询用户信息存入row中
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息出错");
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

	printf("密码(%s,放弃修改该项请输入n)：", row[1]);
	char pwd[200] = { 0 };
	scanf_s("%s", pwd, 200);
	if (strcmp(pwd, "n")) {
		sprintf(query_str, "update users set password = '%s'where user_id = '%s'", pwd,uid);
		ret = mysql_real_query(&mysql, query_str,strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}
	printf("修改成功！\n");
	return;
}