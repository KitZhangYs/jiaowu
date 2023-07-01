#include "login.h"

MYSQL_RES* res;
MYSQL_ROW row;

int Login() {
	printf("\n_____________________________________________________\n");
	printf("|                    请您进行登录                   |\n");
	printf("|___________________________________________________|\n");
	//printf("                   请输入您的用户名：");
	//scanf_s("%s", username, 300);
	//printf("                   请输入您的密码：");
	char pwd[255];
	//scanf_s("%s",pwd,255);
	strcpy(username, "jw0001");
	strcpy(pwd, "admin001");
	char query_str[500] = {0};
	sprintf(query_str, "select * from users where user_id = \"%s\" and password = \"%s\"", username, pwd);
	int ret=0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("123123");
		return 0;
	}
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("用户名或密码错误，请重试！\n");
		return 0;
	}
	row=mysql_fetch_row(res);
	int p=0;
	p = atoi(row[2]);
	return p;
}