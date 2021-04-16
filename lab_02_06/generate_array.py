from random import randint

array_size = input("Введите желаемый размер массива: ")

try:
    array_size = int(array_size)
except ValueError:
    print("Ошибка: размером массива может быть только целое число.")
else:
    if array_size <= 0:
        print("Ошибка: размер массива должен быть положителен.")
    else:
        file = open("array.txt", "wt")

        for i in range(array_size):
            file.write(str(randint(-array_size, array_size)) + " ")

        print("Файл с данными массива успешно создан.")
        file.close()
