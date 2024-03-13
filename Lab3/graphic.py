import matplotlib.pyplot as plt

# Функция для чтения данных из файла
def read_data(file_name):
    with open(file_name, 'r') as file:
        lines = file.readlines()
        data = [tuple(map(float, line.strip().split())) for line in lines]
    return data

def plot_data(file_names):
    plt.figure(figsize=(10, 6))

    for file_name in file_names:
        data = read_data(file_name)
        n_values = [item[0] for item in data]
        time_values = [item[1] for item in data]
        plt.plot(n_values, time_values, label=file_name)

    plt.xlabel('Array Size (n)')
    plt.ylabel('Time (s)')
    plt.title('Time(array size)')
    plt.legend()
    plt.grid(True)
    plt.show()

file_names = ['CentralPivot_sort.txt', 'Shell_sort.txt']

plot_data(file_names)
