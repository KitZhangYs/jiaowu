#pragma once
#include "mysql/mysql.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

extern MYSQL mysql;
extern int per;
extern char username[300];

extern void InitMysql();
extern void SearchInfo(char *table,char *key,char *index_str);