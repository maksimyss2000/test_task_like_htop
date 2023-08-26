# test_task_like_htop

Задание:
Написать приложение на c++ для ОС по выбору (Win10/Linux/MacOS) которое выводит в консоли загруженности CPU (общую и по ядрам).
Как пример можно взять утилиту htop.

Требования:
- Для хранения данных графика используется самостоятельно написанный контейнер (т.е. без использования std, boost и другие библиотеки), который использует шаблон для определения типа хранимых в нем данных;
- Память для данных графиков выделяется один раз при запуске приложения;
- Каждый отдельный график обновляется в отдельном потоке (в том числе и общий). Потоки так же должны быть созданы один раз при запуске приложения. Потоки создаются средствами операционной системы (WinAPI/pthread);
- Класс который обновляет конкретный график, наследуется от базового интерфейса Worker (по факту их выходит 2, один для ядер и один для общего);
- Приветствуется использование новых стандартов c++. Но не стоит ими злоупотреблять;
- Минимизировать вызовы API для сбора данных о загруженности CPU;
- Все сторонние библиотеки и включаемые файлы должны быть в проекте, без необходимости их скачивать и устанавливать отдельно;
- Архив с результатами должен содержать исходный код и исполняемый бинарный файл.


# Результат
Пример работы в сравнении с оригинальной программой при нагрузке и в ее отсутствие.
https://github.com/maksimyss2000/test_task_like_htop/assets/60465175/4a159f2f-fd67-44e4-ae24-4fac155199d8



