#pragma once
#include "timecheck.h"

#define LAYERS 4 // 건물 층수 4층
#define ROOMS 7 // 층 당 방수(6) + 복도(1)
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

/* 관리자가 설정할 최소 온도, 시작 시간, 종료 시간 */
typedef struct admin {
	int min, startTime, endTime; // 에어컨 최소 온도, 시작/종료 시간
	int lightStartTime, lightEndTime; // 조명 시작/종료시간
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

/* manageBuilding - 건물 관리 메뉴 출력하는 함수 */
void manageBuilding(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name);
/* 프로그램 시작 시 각 방의 모든 스위치 OFF로 초기화 및 최소온도를 관리자가 설정한 최소 온도(18도)로 설정 */
void initRoom(Admin *admin, Room(*room)[ROOMS]);
/* 건물관리에서 메뉴를 출력하고 메뉴 번호를 입력 받는 함수 */
int menuControl(const char **menuList, int menuCnt);
/* 해당하는 곳의 조명 ON/OFF 여부를 출력하는 함수 */
void printLight(Room(*room)[ROOMS], int layer, int roomNum);
/* 해당하는 곳의 환풍기 ON, OFF 여부 출력하는 함수 */
void printVentilator(Room(*room)[ROOMS], int layer, int roomNum);
/* 해당하는 곳의 에어컨 ON/OFF 여부를 출력하는 함수*/
void printAirConditioner(Room(*room)[ROOMS], int layer, int roomNum);
/* 건물 내 모든 방과 복도의 조명, 에어컨, 환풍기 ON, OFF 여부 출력 */
void printWholeConditon(Room(*room)[ROOMS], TimeCheck *today, char *name);
/* 에어컨 ON, OFF 조절하는 함수
category -1일 경우 ON/OFF 반전, 0일 경우 OFF, 1일 경우 ON */
void airConditionerSwitchONOFF(Room(*room)[ROOMS], int roomNumber, int category);
/* 조명 ON, OFF 조절하는 함수
category -1일 경우 ON/OFF 반전, 0일 경우 OFF, 1일 경우 ON */
void lightSwitchONOFF(Room(*room)[ROOMS], int roomNumber, int category);
/* 환풍기 ON, OFF 조절하는 함수
category -1일 경우 ON/OFF 반전, 0일 경우 OFF, 1일 경우 ON */
void ventilatorSwitchONOFF(Room(*room)[ROOMS], int roomNumber, int category);
/* 에어컨, 환풍기, 조명 중 하나에 대해 전체 출력하고, 조절할 방이나 복도를 입력하는 함수 */
void switching(Room(*room)[ROOMS], void(*dataPrint)(Room(*)[ROOMS], int, int), void(*switchOnOff)(Room(*)[ROOMS], int, int), TimeCheck *today, char *name);
/* 냉방 시작시 방의 설정 온도가 최소 온도보다 낮을 경우 관리자가 설정한 최소 온도로 설정 */
void checkTemperature(Admin *admin, Room(*room)[ROOMS]);
/* 관라자가 냉방 시 최소 온도 설정하는 함수 */
void setMinimalTemperature(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name);
/* 해당하는 기능을 건물 전체 ON/OFF하는 함수 */
void switchWholeONOFF(Room(*room)[ROOMS], SWITCH OnOff, void(*switchONOFF)(Room(*)[ROOMS], int, int));
/* 현재 시간과 가동 가능 시간 비교 하는 함수 */
SWITCH checkTime(int s, int e, double h);
/* 시간과 분을 입력 받아 해당 시간 조명과 에어컨을 ON/OFF하는 함수??? */
void checkUptime(Admin *admin, Room(*room)[ROOMS], char* hour, char* min);
/* 관리자가 냉방 시작 시간과 종료 시간을 설정하는 함수 */
void setAirConditionerUptime(Admin *admin, TimeCheck *today, char *name);
/* 관리자 모드-건물 관리-냉방 관리의 메뉴 출력 및 입력 받는 함수 */
void airConditionerControl(Admin *admin, Room(*room)[ROOMS], TimeCheck *today, char *name);
/* 정수값 입력 받는 함수 */
int inputInt(int *roomNumber);
/* 입력받은 값 숫자인지 체크하는 함수 */
int checkInt(char *temp, int size);
/* 커서 이동 함수 */
void gotoxy(int x, int y);
/* 한 줄 지우는 함수 */
void clearLine(int y);
/* 글자, 배경색 변경 함수 */
void textcolor(int foreground, int background);
/* 입력버퍼 비우는 함수 */
void myflush(void);