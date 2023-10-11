# doodle навчальний проект лаба 1
// 1.маю 13 класів
// 2.маю 13+ полів та поля з наслідувальних класів
//3.маю 20 нетривіальних функцій і тривілальні є
4.  class traps : public Game і class WhitePlatform : virtual public Platform  ... 2 ієрархії успадкування ...
успадковую Game бо там є координати якими я можу контрольвати об'єкт та успадковую Platform бо там э загальны функцыю для платформи
// 5.  WhitePlatform ::  movePlatforms(float dy, int& y,Sprite score[], int fs[], int& sc) -> статичний поліморфізм, перезагрузка немає h як у Platform ::movePlatforms,  
        WhitePlatform :: TouchToPlatform(int x, int y, float& dy, int index) override та  MovingPlatform : createPlatform(int count) override динамічні полімофізми
        6. інкапсуляцію старався реалізувати правильно
//
//
