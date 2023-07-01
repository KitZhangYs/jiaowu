#include "my_sql.h"

void InitMysql() {
	if (mysql_init(&mysql) == NULL)	//��ʼ�����mysql
	{
		printf("%d : error : %s\n", __LINE__, mysql_error(&mysql));
		exit(1);
	}
	if (mysql_library_init(0, NULL, NULL) != 0) 	//��ʼ��mysql���ݿ�
	{
		fprintf(stderr, "could not initialize MySQL client library\n");
		exit(1);
	}
	if (NULL == mysql_real_connect
		(&mysql,
		"127.0.0.1",
		"root",
		"123456",
		"jiaowu",
		0,
		NULL,
		0)
		)						//��mysql��������������	
	{
		printf("%d : error : %s\n", __LINE__, mysql_error(&mysql));
		exit(1);
	}
	if (mysql_set_character_set(&mysql, "gb2312") != 0)	//���������ַ�����VS�ӿ���̨����ĺ���Ϊgb2312���룬��ʹ��gb2312����ʹ��utf8.
	{
		printf("%d : error : %s\n", __LINE__, mysql_error(&mysql));
		exit(1);
	}
	printf("connect success!\n");
}

void SearchInfo(char *table,char *field_name,char *index_str) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int field = 0;
	char query_str[500] = { 0 };
	sprintf(query_str, "select %s from %s %s", field_name, table,index_str);
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����");
		return;
	}
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("������������Ϣ������\n");
		return;
	}
	field = mysql_num_fields(res);		//������ݱ������
	while (row = mysql_fetch_row(res))
	{
		for (int i = 0; i < field; i++)
		{
			printf("%-20s", row[i]);
		}
		printf("\n");
	}
}