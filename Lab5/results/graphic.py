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

    plt.xlabel('Operations amount (n)')
    plt.ylabel('Time (s)')
    plt.title('Operations with hashtables (not equal probability)')
    plt.legend()
    plt.grid(True)
    plt.show()

file_names = ['not_equ_requests/DoubleOpenedMap.txt', 'not_equ_requests/QuadraticOpenedMap.txt', 'not_equ_requests/LinearOpenedMap.txt', 'not_equ_requests/ListedMap.txt']
curve_names = ['Double hashing (opened)', 'Quadratic hashing (opened)', 'Linear hashing (opened)', 'Listed map']

file_data = {}
for name, file_name in zip(curve_names, file_names):
    file_data[name] = read_data(file_name)

plot_data(file_data)
