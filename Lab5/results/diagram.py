import matplotlib.pyplot as plt

def read_data(filename):
    x_values = []
    y_values = []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.split()
            x_values.append(int(parts[0]))
            y_values.append(int(parts[1]))
    return x_values, y_values

def plot_bar_chart(x_values, y_values):
    plt.figure(figsize=(12, 6))
    plt.bar(x_values, y_values, width=1.0)
    plt.xlabel('Cells')
    plt.ylabel('Collisions')
    plt.title('Mantissa mul exponent hash (float)')
    #plt.ylim(0, 50)
    plt.xlim(0, 1000)

    plt.show()

def main():
    filename = 'float_hash/MantissaMulExponentHash.txt'
    x_values, y_values = read_data(filename)
    plot_bar_chart(x_values, y_values)

if __name__ == "__main__":
    main()
