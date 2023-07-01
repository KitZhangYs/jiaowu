#include "admin.h"

void AdminHomePage() {
	while (true) {
		printf("\n____________________________教务管理系统管理员版____________________________\n");
		printf("|___________________________1.用户信息管理_________________________________|\n");
		printf("|___________________________2.学生信息管理_________________________________|\n");
		printf("|___________________________3.教师信息管理_________________________________|\n");
		printf("|___________________________4.课程信息管理_________________________________|\n");
		printf("|___________________________5.授课信息管理_________________________________|\n");
		printf("|___________________________6.选课信息管理_________________________________|\n");
		printf("|___________________________7.退出管理系统_________________________________|\n");
		printf("|__________________________________________________________________________|\n");
		printf("请您选择");
		int n = 0;
		scanf_s("%d", &n);
		switch (n) {
		case 1:
			CommandUser();
			break;
		case 2:
			CommandStudent();
			break;
		case 3:
			CommandTeacher();
			break;
		case 4:
			CommandLesson();
			break;
		case 5:
			CommandTeacherANDLesson();
			break;
		case 6:
			CommandStudentANDLesson();
			break;
		case 7:
			return;
		default:
			printf("输入错误！\n");
			break;
		}
	}
}

//用户信息管理界面
void CommandUser() {
	while (true) {
		printf("\n_________用户管理界面_________\n");
		printf("|________1.用户列表________|\n");
		printf("|________2.用户查询________|\n");
		printf("|________3.创建用户________|\n");
		printf("|________4.删除用户________|\n");
		printf("|________5.修改用户________|\n");
		printf("|________6.返回主页________|\n");
		printf("|__________________________|\n");
		printf("请您选择");
		int n = 0;
		scanf_s("%d", &n);
		switch (n) {
		case 1:
			PrintAllUsers();
			break;
		case 2:
			SearchUser();
			break;
		case 3:
			CreateUser();
			break;
		case 4:
			DeleteUser();
			break;
		case 5:
			UpdateUser();
			break;
		case 6:
			return;
		default:
			printf("输入错误！\n");
			break;
		}
	}
}

//学生信息管理界面
void CommandStudent() {
	while (true) {
		printf("\n_________学生管理界面_________\n");
		printf("|________1.学生列表________|\n");
		printf("|________2.学生查询________|\n");
		printf("|________3.创建学生________|\n");
		printf("|________4.删除学生________|\n");
		printf("|________5.修改学生________|\n");
		printf("|________6.返回主页________|\n");
		printf("|__________________________|\n");
		printf("请您选择");
		int n = 0;
		scanf_s("%d", &n);
		switch (n) {
		case 1:
			PrintAllStudents();
			break;
		case 2:
			SearchStudent();
			break;
		case 3:
			CreateStudent();
			break;
		case 4:
			DeleteStudent();
			break;
		case 5:
			UpdateStudent();
			break;
		case 6:
			return;
		default:
			printf("输入错误！\n");
			break;
		}
	}
}

//教师管理界面
void CommandTeacher() {
	while (true){
		printf("\n_________教师管理界面_________\n");
		printf("|________1.教师列表________|\n");
		printf("|________2.教师查询________|\n");
		printf("|________3.创建教师________|\n");
		printf("|________4.删除教师________|\n");
		printf("|________5.修改教师________|\n");
		printf("|________6.返回主页________|\n");
		printf("|__________________________|\n");
		printf("请您选择");
		int n = 0;
		scanf_s("%d", &n);
		switch (n) {
		case 1:
			PrintAllTeachers();
			break;
		case 2:
			SearchTeacher();
			break;
		case 3:
			CreateTeacher();
			break;
		case 4:
			DeleteTeacher();
			break;
		case 5:
			UpdateTeacher();
			break;
		case 6:
			return;
		default:
			printf("输入错误！\n");
			break;
		}
	}
}

//课程管理界面
void CommandLesson() {
	while (true) {
		printf("\n_________课程管理界面_________\n");
		printf("|________1.课程列表________|\n");
		printf("|________2.课程查询________|\n");
		printf("|________3.创建课程________|\n");
		printf("|________4.删除课程________|\n");
		printf("|________5.修改课程________|\n");
		printf("|________6.返回主页________|\n");
		printf("|__________________________|\n");
		printf("请您选择");
		int n = 0;
		scanf_s("%d", &n);
		switch (n) {
		case 1:
			PrintAllLessons();
			break;
		case 2:
			SearchLesson();
			break;
		case 3:
			CreateLesson();
			break;
		case 4:
			DeleteLesson();
			break;
		case 5:
			UpdateLesson();
			break;
		case 6:
			return;
		default:
			printf("输入错误！\n");
			break;
		}
	}
}

//授课管理界面
void CommandTeacherANDLesson() {
	while (true) {
		printf("\n_________授课管理界面_________\n");
		printf("|________1.授课列表________|\n");
		printf("|________2.授课查询________|\n");
		printf("|________3.开始授课________|\n");
		printf("|________4.停止授课________|\n");
		printf("|________5.修改授课________|\n");
		printf("|________6.返回主页________|\n");
		printf("|__________________________|\n");
		printf("请您选择");
		int n = 0;
		scanf_s("%d", &n);
		switch (n) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			return;
		default:
			printf("输入错误！\n");
			break;
		}
	}
}

//选课管理界面
void CommandStudentANDLesson() {
	while (true) {
		printf("\n_________选课管理界面_________\n");
		printf("|________1.选课列表________|\n");
		printf("|________2.选课查询________|\n");
		printf("|________3.系统选课________|\n");
		printf("|________4.系统退课________|\n");
		printf("|________5.返回主页________|\n");
		printf("|__________________________|\n");
		printf("请您选择");
		int n = 0;
		scanf_s("%d", &n);
		switch (n) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			return;
		default:
			printf("输入错误！\n");
			break;
		}
	}
}