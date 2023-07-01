#include "admin.h"

//չʾ���пγ��б�
void PrintAllLessons() {
	strcpy(table, "lessons");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("\n�γ̺�          �γ�����            �γ�����            �γ�ѧʱ            ����ѧ��\n");
	SearchInfo(table, key, index_str);
	return;
}

//����ָ���γ�
void SearchLesson() {
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
void CreateLesson() {
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
void DeleteLesson() {
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
void UpdateLesson() {
	printf("\n������Ҫ�޸ĵĿγ̺ţ�");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "select * from lessons where lesson_id = '%s'", uid);

	//��lessons���в�ѯ�û���Ϣ����row��
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

	printf("�γ�����(%s,�����޸ĸ���������n)��", row[1]);
	char name[200] = { 0 };
	scanf_s("%s", name, 200);
	if (strcmp(name, "n")) {
		sprintf(query_str, "update lessons set name = '%s' where lesson_id = '%s'", name, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("�γ�����(%s,�����޸ĸ���������n)��", row[2]);
	char contact[200] = { 0 };
	scanf_s("%s", contact, 200);
	if (strcmp(contact, "n")) {
		sprintf(query_str, "update lessons set contact = '%s' where lesson_id = '%s'", contact, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("ѧʱ(%s,�����޸ĸ���������n)��", row[3]);
	char learn_time[200] = { 0 };
	scanf_s("%s", learn_time, 200);
	if (strcmp(learn_time, "n")) {
		sprintf(query_str, "update lessons set learn_time = %s where lesson_id = '%s'", learn_time, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("����ѧ��(%s,�����޸ĸ���������n)��", row[4]);
	char semester[200] = { 0 };
	scanf_s("%s", semester, 200);
	if (strcmp(semester, "n")) {
		sprintf(query_str, "update lessons set semester = %s where lesson_id = '%s'", semester, uid);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("\n�޸ĳɹ���\n");
	return;
}