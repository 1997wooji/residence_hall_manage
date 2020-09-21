#pragma once
#include "timecheck.h"

#define LAYERS 4 // �ǹ� ���� 4��
#define ROOMS 7 // �� �� ���(6) + ����(1)
#define BACK 27
#define BACKSPACE 8
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

enum SWITCH { OFF, ON };

/* �����ڰ� ������ �ּ� �µ�, ���� �ð�, ���� �ð� */
typedef struct admin {
	int min, startTime, endTime; // ������ �ּ� �µ�, ����/���� �ð�
	int lightStartTime, lightEndTime; // ���� ����/����ð�
}Admin;

typedef struct _airConditioner {
	char switchOn;
	int set;
}AirConditioner;

typedef struct _ventilator {
	char switchOn;
}Ventilator;

typedef struct _light {
	char switchOn;
}Light;

typedef struct room {
	AirConditioner airConditioner;
	Ventilator ventilator;
	Light light;
}Room;

/* manageBuilding - �ǹ� ���� �޴� ����ϴ� �Լ� */
void manageBuilding(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name);
/* ���α׷� ���� �� �� ���� ��� ����ġ OFF�� �ʱ�ȭ �� �ּҿµ��� �����ڰ� ������ �ּ� �µ�(18��)�� ���� */
void initRoom(Admin *admin, Room(*room)[ROOMS]);
/* �ǹ��������� �޴��� ����ϰ� �޴� ��ȣ�� �Է� �޴� �Լ� */
int menuControl(const char **menuList, int menuCnt);
/* �ش��ϴ� ���� ���� ON/OFF ���θ� ����ϴ� �Լ� */
void printLight(Room(*room)[ROOMS], int layer, int roomNum);
/* �ش��ϴ� ���� ȯǳ�� ON, OFF ���� ����ϴ� �Լ� */
void printVentilator(Room(*room)[ROOMS], int layer, int roomNum);
/* �ش��ϴ� ���� ������ ON/OFF ���θ� ����ϴ� �Լ�*/
void printAirConditioner(Room(*room)[ROOMS], int layer, int roomNum);
/* �ǹ� �� ��� ��� ������ ����, ������, ȯǳ�� ON, OFF ���� ��� */
void printWholeConditon(Room(*room)[ROOMS], TimeCheck *today, char *name);
/* ������ ON, OFF �����ϴ� �Լ�
category -1�� ��� ON/OFF ����, 0�� ��� OFF, 1�� ��� ON */
void airConditionerSwitchONOFF(Room(*room)[ROOMS], int roomNumber, int category);
/* ���� ON, OFF �����ϴ� �Լ�
category -1�� ��� ON/OFF ����, 0�� ��� OFF, 1�� ��� ON */
void lightSwitchONOFF(Room(*room)[ROOMS], int roomNumber, int category);
/* ȯǳ�� ON, OFF �����ϴ� �Լ�
category -1�� ��� ON/OFF ����, 0�� ��� OFF, 1�� ��� ON */
void ventilatorSwitchONOFF(Room(*room)[ROOMS], int roomNumber, int category);
/* ������, ȯǳ��, ���� �� �ϳ��� ���� ��ü ����ϰ�, ������ ���̳� ������ �Է��ϴ� �Լ� */
void switching(Room(*room)[ROOMS], void(*dataPrint)(Room(*)[ROOMS], int, int), void(*switchOnOff)(Room(*)[ROOMS], int, int), TimeCheck *today, char *name);
/* �ù� ���۽� ���� ���� �µ��� �ּ� �µ����� ���� ��� �����ڰ� ������ �ּ� �µ��� ���� */
void checkTemperature(Admin *admin, Room(*room)[ROOMS]);
/* �����ڰ� �ù� �� �ּ� �µ� �����ϴ� �Լ� */
void setMinimalTemperature(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name);
/* �ش��ϴ� ����� �ǹ� ��ü ON/OFF�ϴ� �Լ� */
void switchWholeONOFF(Room(*room)[ROOMS], SWITCH OnOff, void(*switchONOFF)(Room(*)[ROOMS], int, int));
/* ���� �ð��� ���� ���� �ð� �� �ϴ� �Լ� */
SWITCH checkTime(int s, int e, double h);
/* �ð��� ���� �Է� �޾� �ش� �ð� ����� �������� ON/OFF�ϴ� �Լ�??? */
void checkUptime(Admin *admin, Room(*room)[ROOMS], char* hour, char* min);
/* �����ڰ� �ù� ���� �ð��� ���� �ð��� �����ϴ� �Լ� */
void setAirConditionerUptime(Admin *admin, TimeCheck *today, char *name);
/* ������ ���-�ǹ� ����-�ù� ������ �޴� ��� �� �Է� �޴� �Լ� */
void airConditionerControl(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name);
/* ������ �Է� �޴� �Լ� */
int inputInt(int *roomNumber);
/* �Է¹��� �� �������� üũ�ϴ� �Լ� */
int checkInt(char *temp, int size);
/* Ŀ�� �̵� �Լ� */
void gotoxy(int x, int y);
/* �� �� ����� �Լ� */
void clearLine(int y);
/* ����, ���� ���� �Լ� */
void textcolor(int foreground, int background);
/* �Է¹��� ���� �Լ� */
void myflush(void);