#pragma once
#include "my_sql.h"

extern char table[100], index_str[200], key[100];

//����Ա�Ľ���
extern void AdminHomePage(void);
extern void CommandUser(void);
extern void CommandStudent(void);
extern void CommandTeacher(void);
extern void CommandLesson(void);
extern void CommandTeacherANDLesson(void);
extern void CommandStudentANDLesson(void);

//�����û�����
extern void PrintAllUsers(void);//չʾ�����û���Ϣ
extern void SearchUser(void);//����ָ���û���ͨ���û�id��
extern void CreateUser(void);//�������û�
extern void DeleteUser(void);//ɾ���û�
extern void UpdateUser(void);//�޸��û���Ϣ

//����ѧ������
extern void PrintAllStudents(void);//չʾ����ѧ����Ϣ
extern void SearchStudent(void);//����ָ��ѧ����ͨ��ѧ�ţ�
extern void CreateStudent(void);//������ѧ��
extern void DeleteStudent(void);//ɾ��ѧ��
extern void UpdateStudent(void);//�޸�ѧ����Ϣ

//�����ʦ����
extern void PrintAllTeachers(void);//չʾ���н�ʦ��Ϣ
extern void SearchTeacher(void);//����ָ����ʦ��ͨ����ʦ�ţ�
extern void CreateTeacher(void);//�����½�ʦ
extern void DeleteTeacher(void);//ɾ����ʦ
extern void UpdateTeacher(void);//�޸Ľ�ʦ��Ϣ