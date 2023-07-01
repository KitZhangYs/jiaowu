#pragma once
#include "my_sql.h"

extern char table[100], index_str[200], key[100];

//管理员的界面
extern void AdminHomePage(void);
extern void CommandUser(void);
extern void CommandStudent(void);
extern void CommandTeacher(void);
extern void CommandLesson(void);
extern void CommandTeacherANDLesson(void);
extern void CommandStudentANDLesson(void);

//管理用户函数
extern void PrintAllUsers(void);//展示所有用户信息
extern void SearchUser(void);//查找指定用户（通过用户id）
extern void CreateUser(void);//创建新用户
extern void DeleteUser(void);//删除用户
extern void UpdateUser(void);//修改用户信息

//管理学生函数
extern void PrintAllStudents(void);//展示所有学生信息
extern void SearchStudent(void);//查找指定学生（通过学号）
extern void CreateStudent(void);//创建新学生
extern void DeleteStudent(void);//删除学生
extern void UpdateStudent(void);//修改学生信息

//管理教师函数
extern void PrintAllTeachers(void);//展示所有教师信息
extern void SearchTeacher(void);//查找指定教师（通过教师号）
extern void CreateTeacher(void);//创建新教师
extern void DeleteTeacher(void);//删除教师
extern void UpdateTeacher(void);//修改教师信息

//管理课程函数
extern void PrintAllLessons(void);//展示所有课程信息
extern void SearchLesson(void);//查找指定课程（通过课程号）
extern void CreateLesson(void);//创建新课程
extern void DeleteLesson(void);//删除课程
extern void UpdateLesson(void);//修改课程信息

//管理授课函数
extern void PrintAllTeaching(void);//展示所有授课信息
extern void SearchTeaching(void);//查找指定课程（通过授课编号，教师id或课程id）
extern void CreateTeaching(void);//创建新授课
extern void DeleteTeaching(void);//删除授课
extern void UpdateTeaching(void);//修改授课信息

//管理选课函数
extern void PrintAllLearning(void);//展示所有选课信息
extern void SearchLearning(void);//查找指定课程（通过选课编号，学生id或课程id）
extern void CreateLearning(void);//创建新选课
extern void DeleteLearning(void);//删除选课
extern void UpdateLearning(void);//修改选课信息