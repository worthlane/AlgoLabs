import matplotlib.pyplot as plt

def read_data_from_files(file_name1, file_name2):
    with open(file_name1, 'r') as file1, open(file_name2, 'r') as file2:
        lines1 = file1.readlines()
        lines2 = file2.readlines()
        data = [[], [], []]  # [[n_values], [time1_values], [time2_values]]
        for line1, line2 in zip(lines1, lines2):
            n1, time1 = map(float, line1.strip().split())
            n2, time2 = map(float, line2.strip().split())
            if n1 != n2:
                raise ValueError("The values of 'n' do not match between the two files.")
            data[0].append(n1)
            data[1].append(time1)
            data[2].append(time2)
        return data

def plot_data(data):
    plt.figure(figsize=(10, 6))
    plt.plot(data[0], data[1], label='Dynamic array time')
    plt.plot(data[0], data[2], label='List time')
    plt.xlabel('n')
    plt.ylabel('Time')
    plt.title('Time(n)')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    file_name1 = input("Input file name for dynamic array time data: ")
    file_name2 = input("Input file name for list time data: ")
    data = read_data_from_files(file_name1, file_name2)
    plot_data(data)

