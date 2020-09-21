#pragma once

/* 학생이 자신의 방에 대해 관리하는 함수 */
void manageBuildingStudent(Admin *admin, Room(*room)[ROOMS], Person *student, TimeCheck *today, char *name);
/* 해당 방의 에어컨 설정온도를 출력하는 함수 */
void setStudentAirConditioner(Admin *admin, Room(*room)[ROOMS], int set, int layer, int roomNumber);

void checkMyPost(List *lp,Person *student, TimeCheck *today, char *name); /* 학생에게 온 택배 프린트*/
void checkMyInform(List *lp, Person *student, TimeCheck *today, char *name); /*학생의 개인정보 관리*/