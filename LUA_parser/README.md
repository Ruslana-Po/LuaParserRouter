# LUA_parser

g++ -std=c++17 main.cpp LuaWrapper.cpp source/parse.cpp source/str.cpp source/tree.cpp source/parse_exception.cpp source/tree_node.cpp source/lua_parser.cpp source/check_funck.cpp -llua5.1 -lm -ldl


*Пример работы программы*
*(ввод названия кода, при ошибке выводится сообщение, номер строки ошибки и указание на ошибку) Далее проводится проверка на зацикливание*
```bash

Проверка на ошибки в коде:

Код l
Ошибка: Неожиданный символ
2:
    z = \"unclosed"
        ^

Код n
OK

Код f
Ошибка: end без if
16:
end
  ^

Код g
Ошибка: Неверное количество аргументов для функции 'math.cos'. Ожидается: 1 аргумент
12:
    value = math.cos(value, 0)
                   ^

Код i
Ошибка: Ожидается аргумент после запятой
15:
elseif type(value, ) == "number" and value < 10 then
                   ^

Код d
Ошибка: ошибка в конструкции elseif then
11:
elseif value == number and value < 10 end then
^

Код a
OK

Код k
Ошибка: Неожиданный символ
2:
    z = \"unclosed"
        ^

Код e
Ошибка: программа не полная

Код h
Ошибка: Незакрытые скобки
12:
    value = 1 + (-4
                  ^

Код p
OK

Код j
Ошибка: Функция 'print' не найдена в библиотеке math и библиотеке кастомных функций
4:
    print("Уровень 1: value > 0")
        ^

Код m
OK

Код o
OK

Код c
Ошибка: Функция 'type' не найдена в библиотеке math и библиотеке кастомных функций
11:
elseif type(value) == "number" and value < 10 then
          ^

Код b
OK


Проверка на зацикливание:

Ошибка: имя m есть в программе o

Ошибка: имя n есть в программе m

Ошибка: имя o есть в программе n

Ошибка: в программе p переменная совпадает с именем программы
```
