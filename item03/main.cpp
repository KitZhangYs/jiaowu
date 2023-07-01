#include "my_sql.h"
#include "login.h"
#include "admin.h"

MYSQL mysql = {0};
int per = 0;
char username[300] = { 0 };

int main()
{
	InitMysql();
	//登录
	int err_times = 0;
	while (!per) {
		per = Login();
		if (!per) {
			err_times++;
		}
		if (err_times == 3) {
			printf("错误次数过多，请5分钟后再尝试！\n");
			Sleep(5 * 60000);
			err_times = 0;
		}
	}

	switch (per) {
	case 1:
		AdminHomePage();
		break;
	default:
		break;;
	}
	mysql_close(&mysql);
	mysql_library_end();
	return 0;
}
