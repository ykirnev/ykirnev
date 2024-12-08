import os
import pandas as pd
import matplotlib.pyplot as plt

# Укажите директорию с результатами
RESULTS_DIR = "results"  # Путь к папке с результатами

def analyze_results():
    data = []

    # Рекурсивно проходим по директориям
    for program in os.listdir(RESULTS_DIR):
        program_path = os.path.join(RESULTS_DIR, program)
        if not os.path.isdir(program_path):
            continue

        for size in os.listdir(program_path):
            size_path = os.path.join(program_path, size)
            if not os.path.isdir(size_path):
                continue

            for threads in os.listdir(size_path):
                threads_path = os.path.join(size_path, threads)
                if not os.path.isdir(threads_path):
                    continue

                # Путь к файлу времени
                time_file = os.path.join(threads_path, "time.txt")

                # Если файл существует, читаем его
                if os.path.exists(time_file):
                    try:
                        with open(time_file, "r") as tf:
                            time = float(tf.read().strip())
                    except ValueError:
                        print(f"[ERROR] Invalid time data in {time_file}")
                        continue  # Если данные некорректны, пропускаем

                    # Добавляем данные в таблицу
                    data.append({
                        "Program": program,  # Название программы (test, test1, test2)
                        "Size": int(size),
                        "Threads": int(threads),
                        "Time": time,
                    })
                else:
                    print(f"[WARNING] Missing time file: {time_file}")

    # Создание DataFrame
    df = pd.DataFrame(data)
    print("Collected Results:\n", df.head())  # Вывод первых строк DataFrame для диагностики
    print("Unique Programs Found:", df["Program"].unique())  # Проверяем уникальные программы
    return df

def plot_thread_dependency(df):
    # Уникальные размеры задач (N)
    unique_sizes = df["Size"].unique()

    for size in unique_sizes:
        fig, ax = plt.subplots(figsize=(10, 6))

        # Фильтруем данные по размеру задачи
        size_data = df[df["Size"] == size]

        # Группируем данные по количеству нитей
        for program in size_data["Program"].unique():
            program_data = size_data[size_data["Program"] == program]

            # Строим график зависимости времени от числа нитей для каждой программы
            ax.plot(program_data["Threads"], program_data["Time"], label=program, marker='o')

        # Настройки графика
        ax.set_xlabel('Number of Threads')
        ax.set_ylabel('Execution Time (seconds)')
        ax.set_title(f'Execution Time vs. Threads for N={size}')
        ax.grid(True)
        ax.legend(title="Program")

        # Сохраняем график для каждого размера задачи
        plt.savefig(f'Execution_Time_vs_Threads_N{size}.png')
        plt.close()


df = analyze_results()
plot_thread_dependency(df)
