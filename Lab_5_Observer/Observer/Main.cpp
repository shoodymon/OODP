#include "Includes.hpp"

int main() {
    setlocale(0, "");

    // Создаём объект издателя
    PostSaver postSaver;

    // Создаем несколько объектов наблюдателя
    NotificationObserver* notificationObserver1 = new NotificationObserver();
    NotificationObserver* notificationObserver2 = new NotificationObserver();
    NotificationObserver* notificationObserver3 = new NotificationObserver();

    // Добавляем подписчиков для нашего издателя
    postSaver.Add(notificationObserver1);
    postSaver.Add(notificationObserver2);
    postSaver.Add(notificationObserver3);
    // Сообщение, которое мы хотим отправить всем подписчикам (наблюдателям)
    string msg = "Всех поздравляю с 8 марта!";

    // Отправляем всем наблюдателям
    postSaver.Send(msg);
    return 0;
}
