# OperatingSystems_HW_3
# Чечуров Владимир Сергеевич, ОС ДЗ-3

Данная работа выполнялась согласно критериям на 10 баллов. Выполнено создание процесса ребенка, в котором выполняется поиск факториала переданного числа, а в потоке родителе - поиск числа Фибоначчи (оба переданных числа равны друг другу и получаются в качестве аргументов). В консоль выводятся результаты работы поиска чисел и информация об ID потоков, которые производили их вычисления, ID их родителей.

Родительский поток ожидание завершения потока ребенка, после этого создает новый поток, который вводит в консоль имена всех файлов в текущей директории (где находится исполняемый файл). После этого программа завершает выполнение.

Код программы подробно прокомментирован. 
