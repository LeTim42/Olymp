# Полезные вещи для олимпиадного программиирования

## 0.cpp — шаблон
##### Здесь есть:
- поиски на монотонных/унимодальных функциях
- работа с модульной арифметикой
- умножение с помощью БПФ
- работа с графами
- генерация случайных объектов
- работа с геометрией
- суффиксный автомат
- работа со строками
- свой bitset
- длинная арифметика
- класс рациональных чисел
- система непересекающихся множеств
- разреженная таблица
- дерево отрезков (без и с lazy propagation)
- локальный ввод/вывод через файлы
- быстрый ввод/вывод и мультитест
- шаблон для стресс-теста
- макросы для дебага (в т.ч. в рекурсивных функциях)

## cpy.cpp — дублирование шаблона для контеста
##### Использование: `cpy directory last_problem`
- `directory` – папка, в которую дублировать шаблон
- `last_problem` – буква, обозначающая последнюю задачу

Например, `cpy contest H` продублирует шаблон *0.cpp* в папку *contest* как *A.cpp, B.cpp, ..., H.cpp*, а также скопирует сам шаблон *0.cpp*, файл ввода *input.txt* и скрипт *run.bat*

## clean.cpp — очистка неиспользуемого кода
##### Использование: `clean input [output]`
- `input` – название входного файла с кодом (можно без расширения *.cpp*)
- `output` – название выходного файла с очищенным кодом (можно без расширения *.cpp*)
Если `output` не указан, то очищенный код копируется в буфер обмена

##### Что делает эта программа
- Убирает неиспользуемые `#define`, `typedef`, `using`, `namespace`, `class`, `struct`, функции и переменные **построчно**
- **Не убирает** лишние `#include`
- Содержимое функций оставляет **неизменным**
- Так как парсер не идеальный, **может оставить** часть неиспользуемого кода
- Гарантированно **не уберет** используемый код

## run.bat — компиляция и запуск кода
##### Использование: `run input`
- `input` – название файла с кодом без расширения *.cpp*

##### Что делает этот скрипт
- Удаляет исполняемый файл *a.exe*
- Компилирует файл с кодом *input.cpp*
- Запускает программу *clean* для файла *input.cpp*
- Запускает скомпилированную программу *a.exe*
