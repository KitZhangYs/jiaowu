#include "admin.h"


//չʾȫ��ѧ����Ϣ
void PrintAllStudents() {
	strcpy(table, "students");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("ѧ��            ����            �Ա�            �༶\n");
	SearchInfo(table, key, index_str);
	return;
}

//��ѯѧ����Ϣ
void SearchStudent() {
	char uid[100];
	printf("��������Ҫ���ҵ�ѧ��id��");
	scanf_s("%s", uid, 100);
	strcpy(table, "students");
	strcpy(key, "*");
	sprintf(index_str, "where student_id = \"%s\"", uid);//ƴ��where�Ӿ�
	printf("ѧ��            ����            �Ա�            �༶\n");
	SearchInfo(table, key, index_str);
	return;
}


//����ѧ��
void CreateStudent() {
	char uid[200], name[200] = { 0 }, pwd[200];
	int p = 3, sex = 0, n = 0;
	printf("��������ѧ����ѧ��:");
	scanf_s("%s", uid, 200);
	printf("��������ѧ�������ƣ�");
	scanf_s("%s", name, 200);
	printf("��������ѧ�������룺");
	scanf_s("%s", pwd, 200);
	printf("��������ѧ�����Ա�(0:��,1:Ů)��");
	scanf_s("%d", &sex);
	char querry_str[500] = { 0 };
	int Class = 0;
	printf("���������û��İ༶��");
	scanf_s("%d", &Class);
	sprintf(querry_str, "insert into students (student_id,name,sex,class) values ('%s','%s',%d,%d)", uid, name, sex, Class);//ƴ��insert���
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
	printf("�½�ѧ���ɹ���\n");
	return;
}

//ɾ��ѧ��
void DeleteStudent() {
	printf("\n������Ҫɾ����ѧ��id��");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "delete from users where user_id = '%s'", uid);//ƴ��delete�Ӿ�
	int n = 0;
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (n) {
		printf("\nɾ��ѧ��ʧ�ܣ�%s\n", mysql_error(&mysql));
		return;
	}
	sprintf(query_str, "delete from students where student_id = '%s'", uid);
	n = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (n) {
		printf("\nɾ��ѧ��ʧ�ܣ�%s\b", mysql_error(&mysql));
		return;
	}
	printf("\nɾ���ɹ���\n");
	return;
}

//�޸�ѧ����Ϣ
void UpdateStudent() {
	printf("\n������Ҫ�޸ĵ�ѧ�ţ�");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "select * from students where student_id = '%s'", uid);

	//��users���в�ѯ�û���Ϣ����row��
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
		sprintf(query_str, "update students set name = '%s' where student_id = '%s'", name, uid);
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
		sprintf(query_str, "update students set sex = '%s' where student_id = '%s'", sex, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("�༶(%s,�����޸ĸ���������n)��", row[3]);
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

	printf("\n�޸ĳɹ���\n");
	return;
}