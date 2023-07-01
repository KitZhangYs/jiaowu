#include "admin.h"

//展示所有课程列表
void PrintAllLessons() {
	strcpy(table, "lessons");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("\n课程号          课程名称            课程性质            课程学时            开课学期\n");
	SearchInfo(table, key, index_str);
	return;
}

//查找指定课程
void SearchLesson() {
	char uid[100];
	printf("\n请输入需要查找的课程号：");
	scanf_s("%s", uid, 100);
	strcpy(table, "lessons");
	strcpy(key, "*");
	sprintf(index_str, "where lessons = \"%s\"", uid);//拼接where子句
	printf("\n课程号          课程名称            课程性质            课程学时            开课学期\n");
	SearchInfo(table, key, index_str);
	return;
}

//创建新课程
void CreateLesson() {
	char name[200] = { 0 }, contact[200] = {0};
	int learn_time = 0,semester = 0, n = 0;
	printf("请输入新课程的名称：");
	scanf_s("%s", name, 200);
	char querry_str[500] = { 0 };
	printf("请输入新课程的性质：");
	scanf_s("%s", contact, 200);
	printf("请输入新课程的学时：");
	scanf_s("%d", &learn_time);
	printf("请输入新课程的开课学期：");
	scanf_s("%d", &semester);
	sprintf(querry_str, "insert into lessons (name,contact,learn_time,semester) VALUES ('%s','%s',%d,%d)",  name, contact, learn_time, semester);//拼接insert语句
	n = mysql_real_query(&mysql, querry_str, strlen(querry_str));
	if (n) {
		printf("%s\n", mysql_error(&mysql));
		return;
	}
	printf("新建课程成功！\n");
	return;
}

//删除课程
void DeleteLesson() {
	printf("\n请输入要删除的课程号：");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	int ret = 0;
	MYSQL_RES *res1,*res2;
	scanf_s("%s", uid, 200);

	sprintf(query_str, "select * from teacher_lessons where lesson_id = '%s'", uid);//拼接查询授课语句
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息出错！\n");
		return;
	}
	res1 = mysql_store_result(&mysql);

	sprintf(query_str,"select * from student_lessons where lesson_id = '%s'",uid);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息出错！\n");
		return;
	}
	res2 = mysql_store_result(&mysql);

	if ((!mysql_num_rows(res1))&&(!mysql_num_rows(res2)) ){
		sprintf(query_str, "delete from lessons where lesson_id = '%s'", uid);//拼接delete子句
		int n = 0;
		n = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (n) {
			printf("\n删除课程失败：%s\n", mysql_error(&mysql));
			return;
		}
		printf("\n删除成功！\n");
		return;
	}
	printf("该课程正被选修或授课！\n");
	return;
}

//修改课程信息
void UpdateLesson() {
	printf("\n请输入要修改的课程号：");
	char uid[200] = { 0 }, query_str[500] = { 0 };
	scanf_s("%s", uid, 200);
	sprintf(query_str, "select * from lessons where lesson_id = '%s'", uid);

	//在lessons表中查询用户信息存入row中
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

	printf("课程名称(%s,放弃修改该项请输入n)：", row[1]);
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

	printf("课程性质(%s,放弃修改该项请输入n)：", row[2]);
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

	printf("学时(%s,放弃修改该项请输入n)：", row[3]);
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

	printf("开课学期(%s,放弃修改该项请输入n)：", row[4]);
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

	printf("\n修改成功！\n");
	return;
}

//获取全部授课信息
void PrintAllTeaching() {
	strcpy(table, "teacher_lessons");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("\n授课编号         教师id            课程id\n");
	SearchInfo(table, key, index_str);
	return;
}

//查询授课信息
void SearchTeaching() {
	strcpy(table, "teacher_lessons");
	strcpy(key, "*");
	printf("请选择您需要查询的方式(1.编号查询 2.教师id查询 3.课程id查询)：");
	char str[200] = { 0 }, query_str[500] = {0};
	int n = 0;
	scanf_s("%d", &n);
	switch (n) {
	case 1:
		printf("请输入授课编号：");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where id = %s", str);
		printf("\n授课编号         教师id            课程id\n");
		SearchInfo(table, key, query_str);
		return;
	case 2:
		printf("请输入教师id：");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where teacher_id = %s", str);
		printf("\n授课编号         教师id            课程id\n");
		SearchInfo(table, key, query_str);
		return;
	case 3:
		printf("请输入课程id：");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where lesson_id = %s", str);
		printf("\n授课编号         教师id            课程id\n");
		SearchInfo(table, key, query_str);
		return;
	}
	printf("输入错误，回到上级菜单\n");
	return;
}

//新建授课信息
void CreateTeaching() {
	char lesson[200] = { 0 }, teacher[200] = { 0 }, query_str[500] = { 0 };
	printf("请输入课程id：");
	scanf_s("%s", lesson,200);
	//在lessons表中查询是否存在该编号
	sprintf(query_str, "select * from lessons where lesson_id = %s", lesson);
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

	printf("请输入教师id：");
	scanf_s("%s", teacher, 200);
	//在teachers表中查询是否存在该编号
	sprintf(query_str, "select * from teachers where teacher_id = '%s'", teacher);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息出错\n");
		return;
	}
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("符合条件的信息不存在\n");
		return;
	}

	sprintf(query_str, "insert into teacher_lessons (teacher_id,lesson_id) values ('%s',%s)", teacher, lesson);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("新建数据失败：%s\n", mysql_error(&mysql));
		return;
	}

	printf("新建数据成功！\n");
	return;
}

//删除授课信息
void DeleteTeaching() {
	int teaching = 0;
	char query_str[500] = { 0 };
	printf("请输入您要删除的授课编号：");
	scanf_s("%d", &teaching);

	//查询是否被选修
	sprintf(query_str, "select * from teacher_lessons where id = %d", teaching);
	int ret=0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息错误！%s\n", mysql_error(&mysql));
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
	sprintf(query_str, "select * from student_lesson where lesson_id = %s", row[2]);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息错误！%s\n", mysql_error(&mysql));
		return;
	}
	res = mysql_store_result(&mysql);
	if (mysql_num_rows(res)) {
		printf("该课程正被选修\n");
		return;
	}

	sprintf(query_str, "delete from teacher_lessons where id = %d", teaching);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("删除失败！%s\n", mysql_error(&mysql));
		return;
	}

	printf("删除成功！\n");
	return;
}

//修改授课信息
void UpdateTeaching() {
	int teaching = 0;
	char query_str[500] = { 0 };
	printf("请输入您要修改的授课编号：");
	scanf_s("%d", &teaching);

	//查询是否被选修
	sprintf(query_str, "select * from teacher_lessons where id = %d", teaching);
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息错误！%s\n", mysql_error(&mysql));
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
	sprintf(query_str, "select * from student_lesson where lesson_id = %s", row[2]);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息错误！%s\n", mysql_error(&mysql));
		return;
	}
	res = mysql_store_result(&mysql);
	if (mysql_num_rows(res)) {
		printf("该课程正被选修\n");
		return;
	}

	printf("教师id(%s,放弃修改该项请输入n)：", row[1]);
	char teacher[200] = { 0 };
	scanf_s("%s", teacher, 200);
	
	if (strcmp(teacher, "n")) {
		sprintf(query_str, "select * from teachers where teacher_id = '%s'", teacher);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("查询信息错误！%s\n", mysql_error(&mysql));
			return;
		}
		res = mysql_store_result(&mysql);
		if (!mysql_num_rows(res)) {
			printf("符合条件的信息不存在\n");
			return;
		}
		sprintf(query_str, "update teacher_lessons set teacher_id = '%s' where id = %d", teacher, teaching);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("课堂id(%s,放弃修改该项请输入n)：", row[2]);
	char lesson[200] = { 0 };
	scanf_s("%s", lesson, 200);
	
	if (strcmp(lesson, "n")) {
		sprintf(query_str, "select * from lessons where lesson_id = %s", lesson);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("查询信息错误！%s\n", mysql_error(&mysql));
			return;
		}
		res = mysql_store_result(&mysql);
		if (!mysql_num_rows(res)) {
			printf("符合条件的信息不存在\n");
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

//展示全部选课信息
void PrintAllLearning() {
	strcpy(table, "student_lesson");
	strcpy(key, "*");
	strcpy(index_str, "");
	printf("\n选课编号         学号            课程id            分数\n");
	SearchInfo(table, key, index_str);
	return;
}

//查询选课信息
void SearchLearning() {
	strcpy(table, "student_lesson");
	strcpy(key, "*");
	printf("请选择您需要查询的方式(1.编号查询 2.学号查询 3.课程id查询)：");
	char str[200] = { 0 }, query_str[500] = { 0 };
	int n = 0;
	scanf_s("%d", &n);
	switch (n) {
	case 1:
		printf("请输入选课编号：");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where id = %s", str);
		printf("\n选课编号         学号            课程id            分数\n");
		SearchInfo(table, key, query_str);
		return;
	case 2:
		printf("请输入学生id：");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where student_id = %s", str);
		printf("\n选课编号         学号            课程id            分数\n");
		SearchInfo(table, key, query_str);
		return;
	case 3:
		printf("请输入课程id：");
		scanf_s("%s", str, 200);
		sprintf(query_str, "where lesson_id = %s", str);
		printf("\n选课编号         学号            课程id            分数\n");
		SearchInfo(table, key, query_str);
		return;
	}
	printf("输入错误，回到上级菜单\n");
	return;
}

//新建选课信息
void CreateLearning() {
	char lesson[200] = { 0 }, student[200] = { 0 }, query_str[500] = { 0 };
	printf("请输入课程id：");
	scanf_s("%s", lesson, 200);
	//在lessons表中查询是否存在该编号
	sprintf(query_str, "select * from lessons where lesson_id = %s", lesson);
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

	printf("请输入学生id：");
	scanf_s("%s", student, 200);
	//在students表中查询是否存在该编号
	sprintf(query_str, "select * from students where studet_id = '%s'", student);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息出错\n");
		return;
	}
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("符合条件的信息不存在\n");
		return;
	}

	sprintf(query_str, "insert into student_lesson (student_id,lesson_id) values ('%s',%s)", student, lesson);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("新建数据失败：%s\n", mysql_error(&mysql));
		return;
	}

	printf("新建数据成功！\n");
	return;
}

//删除选课信息
void DeleteLearning() {
	int learning = 0;
	char query_str[500] = { 0 };
	printf("请输入您要删除的选课编号：");
	scanf_s("%d", &learning);

	//查询是否被选修
	sprintf(query_str, "select * from student_lesson where id = %d", learning);
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息错误！%s\n", mysql_error(&mysql));
		return;
	}
	MYSQL_RES* res;
	res = mysql_store_result(&mysql);
	if (!mysql_num_rows(res)) {
		printf("符合条件的信息不存在\n");
		return;
	}

	sprintf(query_str, "delete from student_lesson where id = %d", learning);
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("删除失败！%s\n", mysql_error(&mysql));
		return;
	}

	printf("删除成功！\n");
	return;
}

//修改选课信息
void UpdateLearning() {
	int learning = 0;
	char query_str[500] = { 0 };
	printf("请输入您要修改的选课编号：");
	scanf_s("%d", &learning);

	//查询是否被选修
	sprintf(query_str, "select * from teacher_lessons where id = %d", learning);
	int ret = 0;
	ret = mysql_real_query(&mysql, query_str, strlen(query_str));
	if (ret) {
		printf("查询信息错误！%s\n", mysql_error(&mysql));
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

	printf("学生id(%s,放弃修改该项请输入n)：", row[1]);
	char student[200] = { 0 };
	scanf_s("%s", student, 200);

	if (strcmp(student, "n")) {
		sprintf(query_str, "select * from teachers where teacher_id = '%s'", student);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("查询信息错误！%s\n", mysql_error(&mysql));
			return;
		}
		res = mysql_store_result(&mysql);
		if (!mysql_num_rows(res)) {
			printf("符合条件的信息不存在\n");
			return;
		}
		sprintf(query_str, "update student_lesson set student_id = '%s' where id = %d", student, learning);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("课堂id(%s,放弃修改该项请输入n)：", row[2]);
	char lesson[200] = { 0 };
	scanf_s("%s", lesson, 200);

	if (strcmp(lesson, "n")) {
		sprintf(query_str, "select * from lessons where lesson_id = %s", lesson);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("查询信息错误！%s\n", mysql_error(&mysql));
			return;
		}
		res = mysql_store_result(&mysql);
		if (!mysql_num_rows(res)) {
			printf("符合条件的信息不存在\n");
			return;
		}
		sprintf(query_str, "update student_lesson set lesson_id = %s where id = %d", lesson, learning);
		ret = mysql_real_query(&mysql, query_str, strlen(query_str));
		if (ret) {
			printf("%s\n", mysql_error(&mysql));
			return;
		}
	}

	printf("成绩(% s, 放弃修改该项请输入n)：", row[3]);
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