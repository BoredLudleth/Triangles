# Triangles
### Дисклеймер
Всем привет!
Данный проект выполнен в учебных целях в рамках курса по C++. 

Целью данного проекта является написание Triangles.

## Компиляция
```
cd Triangles/
cmake -S ./ -B build/
cmake --build build
cd build/
```
Для запуска проекта требуется:

```
./trg < path_to_data_file
./trg_test
```

## Ввод/вывод
На вход программа принимает n - количество треугольников и координаты их точек.

На выходе мы получим номера треугольников, которые пересекаются с друг с другом.