import matplotlib.pyplot as plt

def read_data(file_name):
    with open(file_name, 'r') as file:
        lines = file.readlines()
        data = [tuple(map(float, line.strip().split())) for line in lines]
    return data

def plot_data(file_data):
    plt.figure(figsize=(10, 6))

    for name, data in file_data.items():
        n_values = [item[0] for item in data]
        time_values = [item[1] for item in data]
        plt.plot(n_values, time_values, label=name)

    plt.xlabel('Array size (n)')
    plt.ylabel('Time (s)')
    plt.title('Heapify comparison')
    plt.legend()
    plt.grid(True)
    plt.show()

file_names = ['LinearHeapify.txt', 'StdHeapify.txt']
curve_names = ['Linear', 'Standart']

file_data = {}
for name, file_name in zip(curve_names, file_names):
    file_data[name] = read_data(file_name)

plot_data(file_data)
