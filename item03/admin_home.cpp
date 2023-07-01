#include "admin.h"

void AdminHomePage() {
	while (true) {
		printf("\n____________________________�������ϵͳ����Ա��____________________________\n");
		printf("|___________________________1.�û���Ϣ����_________________________________|\n");
		printf("|___________________________2.ѧ����Ϣ����_________________________________|\n");
		printf("|___________________________3.��ʦ��Ϣ����_________________________________|\n");
		printf("|___________________________4.�γ���Ϣ����_________________________________|\n");
		printf("|___________________________5.�ڿ���Ϣ����_________________________________|\n");
		printf("|___________________________6.ѡ����Ϣ����_________________________________|\n");
		printf("|___________________________7.�˳�����ϵͳ_________________________________|\n");
		printf("|__________________________________________________________________________|\n");
		printf("����ѡ��");
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
			printf("�������\n");
			break;
		}
	}
}

//�û���Ϣ�������
void CommandUser() {
	while (true) {
		printf("\n_________�û��������_________\n");
		printf("|________1.�û��б�________|\n");
		printf("|________2.�û���ѯ________|\n");
		printf("|________3.�����û�________|\n");
		printf("|________4.ɾ���û�________|\n");
		printf("|________5.�޸��û�________|\n");
		printf("|________6.������ҳ________|\n");
		printf("|__________________________|\n");
		printf("����ѡ��");
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
			printf("�������\n");
			break;
		}
	}
}

//ѧ����Ϣ�������
void CommandStudent() {
	while (true) {
		printf("\n_________ѧ���������_________\n");
		printf("|________1.ѧ���б�________|\n");
		printf("|________2.ѧ����ѯ________|\n");
		printf("|________3.����ѧ��________|\n");
		printf("|________4.ɾ��ѧ��________|\n");
		printf("|________5.�޸�ѧ��________|\n");
		printf("|________6.������ҳ________|\n");
		printf("|__________________________|\n");
		printf("����ѡ��");
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
			printf("�������\n");
			break;
		}
	}
}

//��ʦ�������
void CommandTeacher() {
	while (true){
		printf("\n_________��ʦ�������_________\n");
		printf("|________1.��ʦ�б�________|\n");
		printf("|________2.��ʦ��ѯ________|\n");
		printf("|________3.������ʦ________|\n");
		printf("|________4.ɾ����ʦ________|\n");
		printf("|________5.�޸Ľ�ʦ________|\n");
		printf("|________6.������ҳ________|\n");
		printf("|__________________________|\n");
		printf("����ѡ��");
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
			printf("�������\n");
			break;
		}
	}
}

//�γ̹������
void CommandLesson() {
	while (true) {
		printf("\n_________�γ̹������_________\n");
		printf("|________1.�γ��б�________|\n");
		printf("|________2.�γ̲�ѯ________|\n");
		printf("|________3.�����γ�________|\n");
		printf("|________4.ɾ���γ�________|\n");
		printf("|________5.�޸Ŀγ�________|\n");
		printf("|________6.������ҳ________|\n");
		printf("|__________________________|\n");
		printf("����ѡ��");
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
			printf("�������\n");
			break;
		}
	}
}

//�ڿι������
void CommandTeacherANDLesson() {
	while (true) {
		printf("\n_________�ڿι������_________\n");
		printf("|________1.�ڿ��б�________|\n");
		printf("|________2.�ڿβ�ѯ________|\n");
		printf("|________3.��ʼ�ڿ�________|\n");
		printf("|________4.ֹͣ�ڿ�________|\n");
		printf("|________5.�޸��ڿ�________|\n");
		printf("|________6.������ҳ________|\n");
		printf("|__________________________|\n");
		printf("����ѡ��");
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
			printf("�������\n");
			break;
		}
	}
}

//ѡ�ι������
void CommandStudentANDLesson() {
	while (true) {
		printf("\n_________ѡ�ι������_________\n");
		printf("|________1.ѡ���б�________|\n");
		printf("|________2.ѡ�β�ѯ________|\n");
		printf("|________3.ϵͳѡ��________|\n");
		printf("|________4.ϵͳ�˿�________|\n");
		printf("|________5.������ҳ________|\n");
		printf("|__________________________|\n");
		printf("����ѡ��");
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
			printf("�������\n");
			break;
		}
	}
}