# doodle навчальний... використовую бібліотеку sfml, але там працює все добре
проект лаба 1
лаба 1 1.маю 13+ класів 2.маю 13+ полів та поля з наслідувальних класів 3.маю 20+ нетривіальних функцій і тривілальні є 4. class traps : public Game і class WhitePlatform : virtual public Platform ... 2 ієрархії успадкування ... успадковую Game бо там є координати якими я можу контрольвати об'єкт та успадковую Platform бо там є загальні функції для платформи

class ExtremePlatform : public WhitePlatform, public MovingPlatform наслідує 3 платформи (3-не успадкування ) так як WhitePlatform і MovingPlatform наслідують Platform

// 5. WhitePlatform :: movePlatforms(float dy, int& y,Sprite score[], int fs[], int& sc) -> статичний поліморфізм, перезагрузка -> немає h як у Platform ::movePlatforms,
WhitePlatform :: TouchToPlatform(int x, int y, float& dy, int index) override та MovingPlatform : createPlatform(int count) override динамічні полімофізми 6. інкапсуляцію старався реалізувати правильно 7. Контейнер маю у вигляді вектора std::vector plat;

Усі функції та поля я не перераховував, можете самі побачити у коді що там їх багато.
