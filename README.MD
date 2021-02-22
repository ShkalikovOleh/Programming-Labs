# Programming Labs

Лабораторные работы по дисциплинам, связанным с программированием, 113 специальности ФТИ НТУУ "КПИ им. Игоря Сикорского" за 2018-2020 года.

Дисциплины, которые вошли в этот репозиторий:
1. Программирование 1, 2
2. Веб программирование
3. Алгоритмы и структуры данных
4. Специальные разделы программирования(наука о данных)
5. Математическое моделирование
6. Численные методы

Используйте размещенные здесь материалы **исключительно** для проверки написанных вами решений.

## C++
Курс "Программирование" на C++. Семестры
[1(Структурное)](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/C%2B%2B/part%201) и
[2(ООП)](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/C%2B%2B/part%202) соответственно. Вариант 22 mod n, где n - количество заданий. Также присутствуют дополнительные лабораторные по [Python 3](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/C%2B%2B/part%201/LabsADD).

Сам курс, честно говоря, нельзя назвать С++, так как все, что изучается, не более чем C 98 с классами и дженериками.

Для сборки проектов используется [CMake](https://cmake.org/). В работах 2 семестра проверка работоспособности решений проверяется с помощью [Google Test](https://github.com/google/googletest)(не теряйте время в поисках main ;)).

## Web
Курс "Веб программирование" вскользь охватывает такие технологии как HTML, CSS, JS, PHP, SQL.

Моя реализация работ выполнена в виде единого [приложения](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Web/app), каждая страница которого представляет собой решения одного из заданий какой-либо лабораторной.

В папке [scripts](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Web/app/scripts) находяться скрипты на js, php и sql.
В папке [styles](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Web/app/) - стили html страниц из папки [view](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Web/app/view).

Для избежания проблем с переносимостью и установкой ПО используется [упаковка](https://github.com/ShkalikovOleh/Programming-Labs/blob/master/Web/host/Dockerfile) приложения в [Docker](https://www.docker.com/) контейнер и [запуск](https://github.com/ShkalikovOleh/Programming-Labs/blob/master/Web/docker-compose.yml) его и все необходимой инфраструктуры(веб-сервер, сервер БД) с помощью
[Docker Compose](https://docs.docker.com/compose/).

## Algorithms and data structures

Курс "Алгоритмы и структуры данных". Создание самых базовых структур и алгоритмов. Большая часть работ выполнена на [.Net Core](https://dotnet.microsoft.com/download)(C#), но 3 и 4 реализованы на C++ ввиду требований самих лабораторных.

- [Рекурсия C#](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Algorithms%20and%20data%20structures/Recursion)
- [Сортировки C#](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Algorithms%20and%20data%20structures/Sort%20algorithms)
- [Динамический массив и связный список C++](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Algorithms%20and%20data%20structures/List%20and%20array)
- [Стек и очередь C++](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Algorithms%20and%20data%20structures/Stack%20and%20queue)
- [Бинарное дерево C#](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Algorithms%20and%20data%20structures/Tree)

Почти во всех(кроме 2, там только свой вариант) работах выполнены все задания как базовой так и повышенной сложности + некоторые дополнительные задачи, заданные во время защиты.

## Data Science

Курс "Специальные разделы программирования. Наука о данных". Изучаються базовые инструменты работы с наборами данных в Python, а также GDAL для работы со спутниковыми снимками. Большая часть работ выполнена в интерактивных
[Jupyter Notebook](https://jupyter.org/) для простоты визуализации.

- [Подготовительный этап и получение данных (VHI)](https://github.com/ShkalikovOleh/Programming-Labs/blob/master/Data%20Science/VHI%20Index/VHI%20Index.ipynb)
- [Обмен результатами и первоначальный анализ (Spyre)](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Data%20Science/NOAA%20Web%20Portal)
- Структуры для работы с большими объемами данных в Python
  - [Базовый уровень (Household power consumption)](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Data%20Science/Household%20power%20consumption)
  - [Высокий уровень (Credit Approval)](https://github.com/ShkalikovOleh/Programming-Labs/tree/master/Data%20Science/Credit%20Approval)
- [Работа со спутниковыми снимками](https://github.com/ShkalikovOleh/Programming-Labs/blob/master/Data%20Science/Satellite/Satellite.ipynb)

## Math modeling

Курс "Математическое моделирование". Рассмотрены, имплементированы и реализованы самые простые модели, в большинстве своем, связанные с системами автоматического управления. Работы выполнены в интерактивных [Jupyter Notebook](https://jupyter.org/).

- [Фигуры Лиссажу. Полиномы Чебышева. Годограф Михайлова](https://github.com/ShkalikovOleh/Programming-Labs/blob/master/Math%20modeling/Lab%201.ipynb)
- [LTI. ZPK, TF, SS representation](https://github.com/ShkalikovOleh/Programming-Labs/blob/master/Math%20modeling/Lab%202.ipynb)
- [Nonlinear oscillators](https://github.com/ShkalikovOleh/Programming-Labs/blob/master/Math%20modeling/Lab%203.ipynb)
- [Petri network](https://github.com/ShkalikovOleh/Programming-Labs/blob/master/Math%20modeling/Lab%204/report/report.pdf)

## Numerical methods

Курс численных методов. Рассмотрены, имплементированы и реализованы самые простые алгоритмы численно решения
разного рода уравнений. Часть работ выполнена в интерактивных [Jupyter Notebook](https://jupyter.org/).

- [Polynomial roots](https://github.com/ShkalikovOleh/Programming-Labs/blob/master/Numerical%20methods/Polynomial%20roots/report/report.pdf)

## Ошибки и неточности
Если Вы заметили какую-либо ошибку или неточность, то оставьте пожелуйста сообщений о ней, создав соответвующий issue с точным ее описанием, порядком выполнения действий для воспроизведения и "целевым" файлом.

Более того, буду рад принять ваши исправления и дополнения созданные с помощью механизма Pull Request.