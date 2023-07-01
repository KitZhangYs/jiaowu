#include "admin.h"

//չʾ���пγ��б�
void PrintAllTeachers() {
	strcpy(table, "lessons");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("\n�γ̺�          �γ�����            �γ�����            �γ�ѧʱ            ����ѧ��\n");
	SearchInfo(table, key, index_str);
	return;
}

//����ָ���γ�
void SearchTeacher() {
	char uid[100];
	printf("\n��������Ҫ���ҵĿγ̺ţ�");
	scanf_s("%s", uid, 100);
	strcpy(table, "lessons");
	strcpy(key, "*");
	sprintf(index_str, "where lessons = \"%s\"", uid);//ƴ��where�Ӿ�
	printf("\n�γ̺�          �γ�����            �γ�����            �γ�ѧʱ            ����ѧ��\n");
	SearchInfo(table, key, index_str);
	return;
}

//�����¿γ�
void CreateTeacher() {
	char name[200] = { 0 }, contact[200] = {0};
	int learn_time = 0,semester = 0, n = 0;
	printf("�������¿γ̵����ƣ�");
	scanf_s("%s", name, 200);
	char querry_str[500] = { 0 };
	printf("�������¿γ̵����ʣ�");
	scanf_s("%s", contact, 200);
	printf("�������¿γ̵�ѧʱ��");
	scanf_s("%d", &learn_time);
	printf("�������¿γ̵Ŀ���ѧ�ڣ�");
	scanf_s("%d", &semester);
	sprintf(querry_str, "insert into lessons (name,contact,learn_time,semester) VALUES ('%s','%s',%d,%d)",  name, contact, learn_time, semester);//ƴ��insert���
	n = mysql_real_query(&mysql, querry_str, strlen(querry_str));
	if (n) {
		printf("%s\n", mysql_error(&mysql));
		return;
	}
	printf("�½��γ̳ɹ���\n");
	return;
}

//ɾ���γ�
void DeleteTeacher() {
	printf("\n������Ҫɾ���Ŀγ̺ţ�");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	int ret = 0;
	MYSQL_RES *res1,*res2;
	scanf_s("%s", uid, 200);

	sprintf(query_str, "select * from teacher_lessons where lesson_id = '%s'", uid);//ƴ�Ӳ�ѯ�ڿ����
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����\n");
		return;
	}
	res1 = mysql_store_result(&mysql);

	sprintf(query_str,"select * from student_lessons where lesson_id = '%s'",uid);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����\n");
		return;
	}
	res2 = mysql_store_result(&mysql);

	if ((!mysql_num_rows(res1))&&(!mysql_num_rows(res2)) ){
		sprintf(query_str, "delete from lessons where lesson_id = '%s'", uid);//ƴ��delete�Ӿ�
		int n = 0;
		n = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (n) {
			printf("\nɾ���γ�ʧ�ܣ�%s\n", mysql_error(&mysql));
			return;
		}
		printf("\nɾ���ɹ���\n");
		return;
	}
	printf("�ÿγ�����ѡ�޻��ڿΣ�\n");
	return;
}

//�޸Ŀγ���Ϣ
void UpdateTeacher() {
	printf("\n������Ҫ�޸ĵĿγ̺ţ�");
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

	printf("ְ��(%s,�����޸ĸ���������n)��", row[4]);
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