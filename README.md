# Тестовое задание для ГК YADRO

- Тестировалось на Ubuntu 22.04 и Windows 10

## Сборка и запуск на __Linux__

- требует установленные ```make``` и ```gcc(g++)```

- Система сборки - ```make``` 
- ```make run``` соберёт и запустит программу с тестовыми данными из задания
  
- ```make build``` соберёт программу, название исполняемого файла по умолчанию - ```CompClub```

- ```make memcheck``` проверка программы на утечки памяти

- в папке datasets прикладываются тестовые данные которые вызывают различные события ошибок, а также сортировку клиентов и их удаление при закрытии компьютерного клуба. 

- _дополнительно:_ ```make style``` - запуск линтера, в мейкфайле можно изменить параметры изменить параметры если неудобно читать код. Параметр ```Google```, например, можно изменить на ```Microsoft```, тогда фигурные скобки будут расположены на новой строке.

## Сборка и запуск на __Windows__

- Требует установленный ```MinGw``` и ```mingw32-make```(входит в пакет установки MinGw)

- запускать через cmd или powershell 

- _чтобы быстро зайти в cmd с нужной директорией, можно ввести cmd.exe в проводнике вместо пути находясь в папке с исходным кодом_

- Система сборки - ```make (mingw32-make)``` 

- ```mingw32-make run``` соберёт и запустит программу с тестовыми данными из задания

- ```mingw32-make build``` соберёт программу, название исполняемого файла по умолчанию - ```CompClub.exe```

- ```mingw32-make memcheck``` проверка программы на утечки памяти

- в папке datasets прикладываются тестовые данные которые вызывают различные события ошибок, а также сортировку клиентов и их удаление при закрытии компьютерного клуба. Поменять dataset можно в makefile(первая строка) или передавать вручную первым аргументом при запуске программы.

- _дополнительно:_ ```make style``` - запуск линтера, в мейкфайле можно изменить параметры изменить параметры если не удобно читать код. Параметр ```Google```, например, можно изменить на ```Microsoft```, тогда фигурные скобки будут расположены на новой строке.

## Поведение 

- Программа принимает адрес файла с входными данными первым аргументом. Вывод по умолчанию производится на stdout. Если возникли проблемы с открытием файла бросается стандартное библиотечное исключение.

- Если формат входных данных несоответсвует заявленным, программа выводит строку в которой возникла ошибка, после чего бросает user-defined исключение CompClubException унаследованное от std::exception.

_Василий Алексеевич Позднышев @tg: hidtl  
github: https://github.com/htwelve_  



