#include "my_sql.h"
#include "login.h"
#include "admin.h"

MYSQL mysql = {0};
int per = 0;
char username[300] = { 0 };

int main()
{
	InitMysql();
	//��¼
	int err_times = 0;
	while (!per) {
		per = Login();
		if (!per) {
			err_times++;
		}
		if (err_times == 3) {
			printf("����������࣬��5���Ӻ��ٳ��ԣ�\n");
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
