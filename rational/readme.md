# Рациональное число

Реализуйте класс для хранения рационального числа. 

Рациональное число представляется двумя взаимно простыми целыми числами - числителем и положительным знаменателем. Этот инвариант необходимо поддерживать при выполнении любых операций над объектами класса Rational. 


### Деление на 0

При делении на 0 (в операции деления или при установке знаменателя в 0) программа должна сообщать об ошибке. Для этих целей в C++ есть механизм исключений. Исключение - объект некоторого класса, который унаследован от стандартного класса ошибки библиотеки C++. Если не все ясно сейчас, то это ok, если не все понятно перед зачетом или экзаменом - у вас проблемы.

Класс ошибки RationalDivisionByZero написан за вас, вам лишь требуется в момент, когда происходит деление на ноль, сообщить об ошибке с помощью строки: throw RationalDivisionByZero{};



### Примечание

Конструктор от целых чисел должен быть неявным (чтобы работал код вида `Rational x = 5`.

Кодстайл запрещает неявные конструкторы преобразования (и правильно делает), но в этой задаче неявное преобразование из целых чисел в рациональное вполне осмысленно. Чтобы чекер проигнорировал проверку строки с объявлением такого конструктора, добавьте комментарий // NOLINT к этой строке.
