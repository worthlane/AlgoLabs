# Cравнение сортировок

## Пункт 0. Подготовка

arraygen.c генерирует массив случайных чисел
```
./arrgen <array_len> <max_num (<0 для RAND_MAX)>
```
arraysort.c сортирует стандартным qsort числа из потока ввода. Формат ввода:
```
<array_len> array[0] array[1] ...
```
testgen.sh генерирует тесты по запросу. Формат запроса:
```
./testgen.sh <from> <to> <step> <max_num> <output_dir>
```

Сгенерируем 4 папки с тестами, very_small_tests, small_tests, big_tests и tests_most_dublicates


## Пункт 1. Квадратичные сортировки

Реализуем сортировки для первого пункта в файле quadratic_sorts.h.
Шаблон для тестирования сортировок программой из testing.h:
```
TestSort(0, 1000, 50, "small_tests/", "1_point_results/[...]_sort.txt", [...]_sort);
```
Формат вывода данных по времени в файл
```
size_1 time_1
size_2 time_2
size_3 time_3
...
```
Время выводится в секундах.


## Пункт 2. Пирамидальная сортировка


## Пункт 3. Сортировка слиянием. Пирамидальная сортировка


## Пункт 4. Быстрые сортировки (партиционирования и оптимизации)

Шаблон для тестирования функций с разными Partition:
big_tests
```
TestSort(0, 1000000, 10000, "big_tests/", "4_point_results/big_tests/[...]_sort.txt", [...]_sort);
```
tests_most_dublicates
```
TestSort(0, 1000000, 10000, "tests_most_dublicates/", "4_point_results/tests_most_dublicates/[...]_sort.txt", [...]_sort);
```


## Пункт 5. Быстрые сортировки (разные стратегии выбора, прочее)

Самая быстрая сортировка - с выбором центрального опорного элемента

## Пункт 6. Выбор размера блоков для Introsort

## Пункт 7. Introspective Sorting

## Пункт 8. Сортировки, основанные не на сравнениях

## Пункт 9. Вывод


