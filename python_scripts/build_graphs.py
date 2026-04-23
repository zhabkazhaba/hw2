import matplotlib.pyplot as plt
import csv
import os

def main():
    data_dir = os.path.join(os.path.dirname(__file__), '..', 'data')
    input_file = os.path.join(data_dir, 'out_times.csv')
    output_image_times = os.path.join(data_dir, 'search__plot.png')
    output_image_collisions = os.path.join(data_dir, 'collisions_plot.png')

    if not os.path.exists(input_file):
        print(f"Файл не найден")
        return

    sizes = []
    time_linear = []
    time_bt = []
    time_rbt = []
    time_hash = []
    time_map = []
    collisions = []

    with open(input_file, mode='r', encoding='utf-8') as file:
        reader = csv.reader(file, delimiter=';')
        next(reader)
        for row in reader:
            if not row or len(row) < 7:
                continue
            sizes.append(int(row[0]))
            time_linear.append(int(row[1]))
            time_bt.append(int(row[2]))
            time_rbt.append(int(row[3]))
            time_hash.append(int(row[4]))
            time_map.append(int(row[5]))
            collisions.append(int(row[6]))

    plt.figure(figsize=(10, 6))
    
    plt.plot(sizes, time_linear, label='Linear Search', marker='o', linewidth=2)
    plt.plot(sizes, time_bt, label='BT', marker='s', linewidth=2)
    plt.plot(sizes, time_rbt, label='RBT', marker='^', linewidth=2)
    plt.plot(sizes, time_hash, label='Hash Table', marker='d', linewidth=2)
    plt.plot(sizes, time_map, label='std::multimap', marker='x', linewidth=2)

    plt.title('Зависимость времени поиска от размера массива', fontsize=14)
    plt.xlabel('Количество элементов', fontsize=12)
    plt.ylabel('Время выполнения (мc)', fontsize=12)
    
    plt.yscale('log')

    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(fontsize=11)
    plt.tight_layout()
    plt.savefig(output_image_times)
    
    plt.figure(figsize=(10, 6))
    
    plt.plot(sizes, collisions, label='Коллизии (RSHash)', marker='o', color='crimson', linewidth=2)

    plt.title('Зависимость количества коллизий от размера массива', fontsize=14)
    plt.xlabel('Количество элементов', fontsize=12)
    plt.ylabel('Количество коллизий', fontsize=12)
    
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(fontsize=11)
    plt.tight_layout()
    plt.savefig(output_image_collisions)

    plt.show()

if __name__ == '__main__':
    main()