import paramiko

# Настройка подключения
hostname = 'polus.hpc.cs.msu.ru'
username = 'edu-cmc-skpod24-321-12'
private_key_path = '/Users/ykirnev/.ssh/id_rsa'

try:
    client = paramiko.SSHClient()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    private_key = paramiko.RSAKey(filename=private_key_path)
    client.connect(hostname=hostname, username=username, pkey=private_key)
    print(f"Подключение к {hostname} успешно.")
except Exception as e:
    print(f"Ошибка подключения: {e}")
    exit(1)

# Функция выполнения команды с выводом stdout и stderr
def exec_cmd(client, cmd):
    try:
        stdin, stdout, stderr = client.exec_command(cmd)
        stdout_result = stdout.read().decode()
        stderr_result = stderr.read().decode()
        
        if stdout_result:
            print(f"STDOUT для '{cmd}':\n{stdout_result}")
        if stderr_result:
            print(f"STDERR для '{cmd}':\n{stderr_result}")
        
        return stdout_result, stderr_result
    except Exception as e:
        print(f"Ошибка выполнения команды '{cmd}': {e}")
        return None, str(e)

# Проверяем, доступны ли папки
exec_cmd(client, "ls -l")

# Проверка команд mpisubmit.pl
martr_multipliers = [1, 2, 3]  # Пример значений
num_of_processors = [1, 2, 4]  # Пример значений
pat = '/path/to/working/dir/'  # Укажите путь

for i in martr_multipliers:
    stdout, stderr = exec_cmd(client, f'mpisubmit.pl -p 1 -w 00:05 {pat}var35.out {i} {pat}time/var35_{i}.txt {pat}tests/var35_{i}.txt')
    if "ERROR" in stderr or not stdout:
        print(f"Ошибка при запуске для множителя {i}. Проверьте команду.")

    for prc in num_of_processors:
        stdout, stderr = exec_cmd(client, f'mpisubmit.pl -p {prc} {pat}var35-for_1.out {i} {prc} {pat}time/var35_f1_{i}_{prc}.txt {pat}tests/var35-for_1_{i}_{prc}.txt')
        if "ERROR" in stderr or not stdout:
            print(f"Ошибка при запуске для множителя {i} и процессоров {prc}. Проверьте команду.")

        stdout, stderr = exec_cmd(client, f'mpisubmit.pl -p {prc} {pat}var35-for_2.out {i} {prc} {pat}time/var35_f2_{i}_{prc}.txt {pat}tests/var35-for_2_{i}_{prc}.txt')
        if "ERROR" in stderr or not stdout:
            print(f"Ошибка при запуске для множителя {i} и процессоров {prc}. Проверьте команду.")

# Закрытие соединения
client.close()
print("Соединение закрыто.")