# Any

В этой задаче вам предстоит реализовать аналог класса [std::any](http://en.cppreference.com/w/cpp/experimental/any) из нового стандарта
C++17. Данный класс позволяет инкапсулировать в себе значение любого типа, например
```
Any a = 5;
Any b = std::string("hello, world");
Any c = std::vector<int>{1, 2, 3};
```

Интерфейс класса приведен в файле `any.h`, некоторые особенности:

* Метод `Empty` должен возвращать true, если объект Any ничем не проинициализирован (конструктор по умолчанию), либо после вызова `Clear`.
* Метод `GetValue` возвращает содержимое `Any`, возвращаемый тип, разумеется, должен указывать сам пользователь.
При этом если запрашиваемый тип не совпадает с тем, который хранится в объекте `Any`, метод должен бросить исключение `std::bad_cast`.
Примеры использования можно посмотреть в тестах.

### Примечания

* Использование `std::any` и `void *` запрещено.
* Напоминаем, что правильно реализовывать оператор присваивания через `Swap`.
* В решении вам понадобится техника type erasure, прочитать о которой можно [здесь](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Type_Erasure).
* Шаблонные методы определяйте в cpp-файле