import re
import matplotlib.pyplot as plt
import numpy as np

file_path = './output/output_data.txt'

with open(file_path, 'r') as file:
    data = file.read()

pattern = re.compile(r'Binary - Attempts (\d+) - (\d+)')

matches = pattern.findall(data)

data_list = [(int(attempts), int(value)) for attempts, value in matches]
norm_data_list = [(attempt, (value / attempt)) for attempt, value in data_list]

data_dict = {}
for attempts, value in data_list:
    if attempts not in data_dict:
        data_dict[attempts] = []
    data_dict[attempts].append(value)

attempts_list = []
means = []
std_devs = []
for attempts, values in data_dict.items():
    attempts_list.append(attempts)
    means.append(np.mean(values))
    std_devs.append(np.std(values))

# Plotting
fig, ax1 = plt.subplots(figsize=(10, 5))
ax1.errorbar(attempts_list, means, yerr=std_devs, fmt='o-', label='Mean ± Std Dev', capsize=4, capthick=1)
# ax1.plot(average_data.keys(), average_data.values(), marker='o', linestyle='-')
ax1.set_xscale('log')
ax1.set_yscale('log')
ax1.set_xlabel('attempts')
ax1.set_ylabel('us')
ax1.set_title("Average us per attempts")
ax1.grid(True)
plt.savefig('./output/attempts_us')

norm_data_dict = {}
for attempts, value in norm_data_list:
    if attempts not in norm_data_dict:
        norm_data_dict[attempts] = []
    norm_data_dict[attempts].append(value)

attempts_list = []
means = []
std_devs = []
for attempts, values in norm_data_dict.items():
    attempts_list.append(attempts)
    means.append(np.mean(values))
    std_devs.append(np.std(values))


fig, ax2 = plt.subplots(figsize=(10, 5))
ax2.errorbar(attempts_list, means, yerr=std_devs, fmt='o-', label='Mean ± Std Dev', capsize=4, capthick=1)
ax2.set_xscale('log')
ax2.set_xlabel('attempts')
ax2.set_ylabel('Normalized us')
ax2.set_title('"Normalized" us per attempts')
ax2.grid(True)
plt.savefig('./output/normalized_attempts_us')
