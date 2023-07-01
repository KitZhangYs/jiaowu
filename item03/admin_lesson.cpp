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

//��ȡȫ���ڿ���Ϣ
void PrintAllTeaching() {
	strcpy(table, "teacher_lessons");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("\n�ڿα��         ��ʦid            �γ�id\n");
	SearchInfo(table, key, index_str);
	return;
}

//��ѯ�ڿ���Ϣ
void SearchTeaching() {
	strcpy(table, "teacher_lessons");
	strcpy(key, "*");
	printf("��ѡ������Ҫ��ѯ�ķ�ʽ(1.��Ų�ѯ 2.��ʦid��ѯ 3.�γ�id��ѯ)��");
	char str[200] = { 0 }, query_str[500] = {0};
	int n = 0;
	scanf_s("%d", &n);
	switch (n) {
	case 1:
		printf("�������ڿα�ţ�");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where id = %s", str);
		printf("\n�ڿα��         ��ʦid            �γ�id\n");
		SearchInfo(table, key, query_str);
		return;
	case 2:
		printf("�������ʦid��");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where teacher_id = %s", str);
		printf("\n�ڿα��         ��ʦid            �γ�id\n");
		SearchInfo(table, key, query_str);
		return;
	case 3:
		printf("������γ�id��");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where lesson_id = %s", str);
		printf("\n�ڿα��         ��ʦid            �γ�id\n");
		SearchInfo(table, key, query_str);
		return;
	}
	printf("������󣬻ص��ϼ��˵�\n");
	return;
}

//�½��ڿ���Ϣ
void CreateTeaching() {
	char lesson[200] = { 0 }, teacher[200] = { 0 }, query_str[500] = { 0 };
	printf("������γ�id��");
	scanf_s("%s", lesson,200);
	//��lessons���в�ѯ�Ƿ���ڸñ��
	sprintf(query_str, "select * from lessons where lesson_id = %s", lesson);
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

	printf("�������ʦid��");
	scanf_s("%s", teacher, 200);
	//��teachers���в�ѯ�Ƿ���ڸñ��
	sprintf(query_str, "select * from teachers where teacher_id = '%s'", teacher);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����\n");
		return;
	}
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("������������Ϣ������\n");
		return;
	}

	sprintf(query_str, "insert into teacher_lessons (teacher_id,lesson_id) values ('%s',%s)", teacher, lesson);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("�½�����ʧ�ܣ�%s\n", mysql_error(&mysql));
		return;
	}

	printf("�½����ݳɹ���\n");
	return;
}

//ɾ���ڿ���Ϣ
void DeleteTeaching() {
	int teaching = 0;
	char query_str[500] = { 0 };
	printf("��������Ҫɾ�����ڿα�ţ�");
	scanf_s("%d", &teaching);

	//��ѯ�Ƿ�ѡ��
	sprintf(query_str, "select * from teacher_lessons where id = %d", teaching);
	int ret=0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
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
	sprintf(query_str, "select * from student_lesson where lesson_id = %s", row[2]);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
		return;
	}
	res = mysql_store_result(&mysql);
	if (mysql_num_rows(res)) {
		printf("�ÿγ�����ѡ��\n");
		return;
	}

	sprintf(query_str, "delete from teacher_lessons where id = %d", teaching);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("ɾ��ʧ�ܣ�%s\n", mysql_error(&mysql));
		return;
	}

	printf("ɾ���ɹ���\n");
	return;
}

//�޸��ڿ���Ϣ
void UpdateTeaching() {
	int teaching = 0;
	char query_str[500] = { 0 };
	printf("��������Ҫ�޸ĵ��ڿα�ţ�");
	scanf_s("%d", &teaching);

	//��ѯ�Ƿ�ѡ��
	sprintf(query_str, "select * from teacher_lessons where id = %d", teaching);
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
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
	sprintf(query_str, "select * from student_lesson where lesson_id = %s", row[2]);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
		return;
	}
	res = mysql_store_result(&mysql);
	if (mysql_num_rows(res)) {
		printf("�ÿγ�����ѡ��\n");
		return;
	}

	printf("��ʦid(%s,�����޸ĸ���������n)��", row[1]);
	char teacher[200] = { 0 };
	scanf_s("%s", teacher, 200);
	
	if (strcmp(teacher, "n")) {
		sprintf(query_str, "select * from teachers where teacher_id = '%s'", teacher);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
			return;
		}
		res = mysql_store_result(&mysql);
		if (!mysql_num_rows(res)) {
			printf("������������Ϣ������\n");
			return;
		}
		sprintf(query_str, "update teacher_lessons set teacher_id = '%s' where id = %d", teacher, teaching);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("����id(%s,�����޸ĸ���������n)��", row[2]);
	char lesson[200] = { 0 };
	scanf_s("%s", lesson, 200);
	
	if (strcmp(lesson, "n")) {
		sprintf(query_str, "select * from lessons where lesson_id = %s", lesson);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
			return;
		}
		res = mysql_store_result(&mysql);
		if (!mysql_num_rows(res)) {
			printf("������������Ϣ������\n");
			return;
		}
		sprintf(query_str, "update teacher_lessons set lesson_id = %s where id = %d", lesson, teaching);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}
}

//չʾȫ��ѡ����Ϣ
void PrintAllLearning() {
	strcpy(table, "student_lesson");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("\nѡ�α��         ѧ��            �γ�id            ����\n");
	SearchInfo(table, key, index_str);
	return;
}

//��ѯѡ����Ϣ
void SearchLearning() {
	strcpy(table, "student_lesson");
	strcpy(key, "*");
	printf("��ѡ������Ҫ��ѯ�ķ�ʽ(1.��Ų�ѯ 2.ѧ�Ų�ѯ 3.�γ�id��ѯ)��");
	char str[200] = { 0 }, query_str[500] = { 0 };
	int n = 0;
	scanf_s("%d", &n);
	switch (n) {
	case 1:
		printf("������ѡ�α�ţ�");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where id = %s", str);
		printf("\nѡ�α��         ѧ��            �γ�id            ����\n");
		SearchInfo(table, key, query_str);
		return;
	case 2:
		printf("������ѧ��id��");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where student_id = %s", str);
		printf("\nѡ�α��         ѧ��            �γ�id            ����\n");
		SearchInfo(table, key, query_str);
		return;
	case 3:
		printf("������γ�id��");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where lesson_id = %s", str);
		printf("\nѡ�α��         ѧ��            �γ�id            ����\n");
		SearchInfo(table, key, query_str);
		return;
	}
	printf("������󣬻ص��ϼ��˵�\n");
	return;
}

//�½�ѡ����Ϣ
void CreateLearning() {
	char lesson[200] = { 0 }, student[200] = { 0 }, query_str[500] = { 0 };
	printf("������γ�id��");
	scanf_s("%s", lesson, 200);
	//��lessons���в�ѯ�Ƿ���ڸñ��
	sprintf(query_str, "select * from lessons where lesson_id = %s", lesson);
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

	printf("������ѧ��id��");
	scanf_s("%s", student, 200);
	//��students���в�ѯ�Ƿ���ڸñ��
	sprintf(query_str, "select * from students where studet_id = '%s'", student);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����\n");
		return;
	}
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("������������Ϣ������\n");
		return;
	}

	sprintf(query_str, "insert into student_lesson (student_id,lesson_id) values ('%s',%s)", student, lesson);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("�½�����ʧ�ܣ�%s\n", mysql_error(&mysql));
		return;
	}

	printf("�½����ݳɹ���\n");
	return;
}

//ɾ��ѡ����Ϣ
void DeleteLearning() {
	int learning = 0;
	char query_str[500] = { 0 };
	printf("��������Ҫɾ����ѡ�α�ţ�");
	scanf_s("%d", &learning);

	//��ѯ�Ƿ�ѡ��
	sprintf(query_str, "select * from student_lesson where id = %d", learning);
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
		return;
	}
	MYSQL_RES* res;
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("������������Ϣ������\n");
		return;
	}

	sprintf(query_str, "delete from student_lesson where id = %d", learning);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("ɾ��ʧ�ܣ�%s\n", mysql_error(&mysql));
		return;
	}

	printf("ɾ���ɹ���\n");
	return;
}

//�޸�ѡ����Ϣ
void UpdateLearning() {
	int learning = 0;
	char query_str[500] = { 0 };
	printf("��������Ҫ�޸ĵ�ѡ�α�ţ�");
	scanf_s("%d", &learning);

	//��ѯ�Ƿ�ѡ��
	sprintf(query_str, "select * from teacher_lessons where id = %d", learning);
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
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

	printf("ѧ��id(%s,�����޸ĸ���������n)��", row[1]);
	char student[200] = { 0 };
	scanf_s("%s", student, 200);

	if (strcmp(student, "n")) {
		sprintf(query_str, "select * from teachers where teacher_id = '%s'", student);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
			return;
		}
		res = mysql_store_result(&mysql);
		if (!mysql_num_rows(res)) {
			printf("������������Ϣ������\n");
			return;
		}
		sprintf(query_str, "update student_lesson set student_id = '%s' where id = %d", student, learning);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("����id(%s,�����޸ĸ���������n)��", row[2]);
	char lesson[200] = { 0 };
	scanf_s("%s", lesson, 200);

	if (strcmp(lesson, "n")) {
		sprintf(query_str, "select * from lessons where lesson_id = %s", lesson);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("��ѯ��Ϣ����%s\n", mysql_error(&mysql));
			return;
		}
		res = mysql_store_result(&mysql);
		if (!mysql_num_rows(res)) {
			printf("������������Ϣ������\n");
			return;
		}
		sprintf(query_str, "update student_lesson set lesson_id = %s where id = %d", lesson, learning);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("�ɼ�(% s, �����޸ĸ���������n)��", row[3]);
	char score[200] = { 0 };
	scanf_s("%s", score, 200);

	if (strcmp(score, "n")) {
		sprintf(query_str, "update student_lesson set teacher_id = '%s' where score = %d", score, learning);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}
}