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

    plt.xlabel('Load factor (n)')
    plt.ylabel('Time for 10^6 operations (s)')
    plt.title('Opened hashtables')
    plt.legend()
    plt.grid(True)
    plt.show()

file_names = ['load_factor/DoubleOpenedMap.txt', 'load_factor/QuadraticOpenedMap.txt', 'load_factor/LinearOpenedMap.txt']
curve_names = ['Double hashing', 'Quadratic hashing', 'Linear hashing']

file_data = {}
for name, file_name in zip(curve_names, file_names):
    file_data[name] = read_data(file_name)

plot_data(file_data)
