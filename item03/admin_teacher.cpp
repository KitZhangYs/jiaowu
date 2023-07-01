#include "admin.h"

//չʾ���н�ʦ
void PrintAllTeachers() {
	strcpy(table, "teachers");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("��ʦ��          ����            �Ա�            ѧλ            ְ��\n");
	SearchInfo(table, key, index_str);
	return;
}

//����ָ����ʦ
void SearchTeacher() {
	char uid[100];
	printf("��������Ҫ���ҵĽ�ʦid��");
	scanf_s("%s", uid, 100);
	strcpy(table, "teachers");
	strcpy(key, "*");
	sprintf(index_str, "where teacher_id = \"%s\"", uid);//ƴ��where�Ӿ�
	printf("ѧ��            ����            �Ա�            �༶\n");
	SearchInfo(table, key, index_str);
	return;
}

//�����½�ʦ
void CreateTeacher() {
	char uid[200], name[200] = { 0 }, pwd[200],xw[200],zc[200];
	int p = 2, sex = 0, n = 0;
	printf("�������½�ʦ�Ľ�ʦ��:");
	scanf_s("%s", uid, 200);
	printf("�������½�ʦ�����ƣ�");
	scanf_s("%s", name, 200);
	printf("�������½�ʦ�����룺");
	scanf_s("%s", pwd, 200);
	printf("�������½�ʦ���Ա�(0:��,1:Ů)��");
	scanf_s("%d", &sex);
	char querry_str[500] = { 0 };
	printf("���������û���ְ�ƣ�");
	scanf_s("%s", zc, 200);
	printf("���������û���ѧλ��");
	scanf_s("%s", xw, 200);
	sprintf(querry_str, "insert into teachers (teacher_id,name,sex,degree,zhich) VALUES ('%s','%s',%d,'%s','%s')", uid, name, sex, xw, zc);//ƴ��insert���
	n = mysql_real_query(&mysql, querry_str, strlen(querry_str));
	if (n) {
		printf("%s\n", mysql_error(&mysql));
		return;
	}
	sprintf(querry_str, "insert into users ( user_id, password, per ) VALUES (\"%s\", \"%s\", %d) ", uid, pwd, p);//ƴ��insert���
	n = mysql_real_query(&mysql, querry_str, strlen(querry_str));
	if (n) {
		printf("%s\n", mysql_error(&mysql));
		return;
	}
	printf("�½���ʦ�ɹ���\n");
	return;
}

//ɾ����ʦ
void DeleteTeacher() {
	printf("\n������Ҫɾ���Ľ�ʦid��");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "delete from users where user_id = '%s'", uid);//ƴ��delete�Ӿ�
	int n = 0;
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (n) {
		printf("\nɾ����ʦʧ�ܣ�%s\n", mysql_error(&mysql));
		return;
	}
	sprintf(query_str, "delete from teachers where teacher_id = '%s'", uid);
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (n) {
		printf("\nɾ����ʦʧ�ܣ�%s\b", mysql_error(&mysql));
		return;
	}
	printf("\nɾ���ɹ���\n");
	return;
}

//�޸Ľ�ʦ��Ϣ
void UpdateTeacher() {
	printf("\n������Ҫ�޸ĵĽ�ʦ�ţ�");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "select * from teachers where teacher_id = '%s'", uid);

	//��teachers���в�ѯ�û���Ϣ����row��
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����\n");
		return;
	}
	MYSQL_RES* res;
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("������������Ϣ������\n");
		return;
	}
	MYSQL_ROW row;
	row = mysql_fetch_row(res);

	printf("����(%s,�����޸ĸ���������n)��", row[1]);
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

	printf("�Ա�(%s,�����޸ĸ���������n)��", row[2]);
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

	printf("ѧ��(%s,�����޸ĸ���������n)��", row[3]);
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

	printf("ְ��(%s,�����޸ĸ���������n)��",row[4]);
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

	printf("\n�޸ĳɹ���\n");
	return;
}