#pragma once

/* �л��� �ڽ��� �濡 ���� �����ϴ� �Լ� */
void manageBuildingStudent(Admin *admin, Room(*room)[ROOMS], Person *student, TimeCheck *today, char *name);
/* �ش� ���� ������ �����µ��� ����ϴ� �Լ� */
void setStudentAirConditioner(Admin *admin, Room(*room)[ROOMS], int set, int layer, int roomNumber);

void checkMyPost(List *lp,Person *student, TimeCheck *today, char *name); /* �л����� �� �ù� ����Ʈ*/
void checkMyInform(List *lp, Person *student, TimeCheck *today, char *name); /*�л��� �������� ����*/