#include "Includes.hpp"

int main() {
    setlocale(0, "");

    // ������ ������ ��������
    PostSaver postSaver;

    // ������� ��������� �������� �����������
    NotificationObserver* notificationObserver1 = new NotificationObserver();
    NotificationObserver* notificationObserver2 = new NotificationObserver();
    NotificationObserver* notificationObserver3 = new NotificationObserver();

    // ��������� ����������� ��� ������ ��������
    postSaver.Add(notificationObserver1);
    postSaver.Add(notificationObserver2);
    postSaver.Add(notificationObserver3);
    // ���������, ������� �� ����� ��������� ���� ����������� (������������)
    string msg = "���� ���������� � 8 �����!";

    // ���������� ���� ������������
    postSaver.Send(msg);
    return 0;
}
