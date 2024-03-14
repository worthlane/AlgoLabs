import matplotlib.pyplot as plt

# Функция для чтения данных из файла
def read_data(file_name):
    with open(file_name, 'r') as file:
        lines = file.readlines()
        data = [tuple(map(float, line.strip().split())) for line in lines]
    return data

# Функция для построения графика
def plot_data(file_data):
    plt.figure(figsize=(10, 6))

    for name, data in file_data.items():
        n_values = [item[0] for item in data]
        time_values = [item[1] for item in data]
        plt.plot(n_values, time_values, label=name)

    plt.xlabel('Array size (n)')
    plt.ylabel('Time (s)')
    plt.title('Comparison of heapsort speed depending on heap multiplicity')
    plt.legend()
    plt.grid(True)
    plt.show()

# Задаем имена файлов с данными и имена для кривых
file_names = ['2_Pyramid_sort.txt', '6_Pyramid_sort.txt', '10_Pyramid_sort.txt']
curve_names = ['multiplicity 2', 'multiplicity 6', 'multiplicity 10']

# Считываем данные и сохраняем их в словаре с именами кривых
file_data = {}
for name, file_name in zip(curve_names, file_names):
    file_data[name] = read_data(file_name)

# Строим график
plot_data(file_data)
