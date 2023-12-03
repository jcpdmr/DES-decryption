import re
import matplotlib.pyplot as plt
import numpy as np

par_bin_file = './output/output_data_parallel_binary.txt'
seq_bin_file = './output/output_data_sequential_binary.txt'

with open(par_bin_file, 'r') as file:
    par_bin_data = file.read()

with open(seq_bin_file, 'r') as file:
    seq_bin_data = file.read()

pattern = re.compile(r'Binary - Attempts (\d+) - (\d+)')

par_bin_matches = pattern.findall(par_bin_data)
seq_bin_matches = pattern.findall(seq_bin_data)

par_bin_data_list = [(int(attempts), int(value)) for attempts, value in par_bin_matches]
par_bin_norm_data_list = [(attempt, (value / attempt)) for attempt, value in par_bin_data_list]

seq_bin_data_list = [(int(attempts), int(value)) for attempts, value in seq_bin_matches]
seq_bin_norm_data_list = [(attempt, (value / attempt)) for attempt, value in seq_bin_data_list]

# Processing parallel binary data
par_bin_data_dict = {}
for attempts, value in par_bin_data_list:
    if attempts not in par_bin_data_dict:
        par_bin_data_dict[attempts] = []
    par_bin_data_dict[attempts].append(value)

# Extracting data
par_bin_attempts_list = []
par_bin_means = []
par_bin_std_devs = []
for attempts, values in par_bin_data_dict.items():
    par_bin_attempts_list.append(attempts)
    par_bin_means.append(np.mean(values))
    par_bin_std_devs.append(np.std(values))

# Computing "normalized" data
par_bin_norm_data_dict = {}
for attempts, value in par_bin_norm_data_list:
    if attempts not in par_bin_norm_data_dict:
        par_bin_norm_data_dict[attempts] = []
    par_bin_norm_data_dict[attempts].append(value)

par_bin_norm_attempts_list = []
par_bin_norm_means = []
par_bin_norm_std_devs = []
for attempts, values in par_bin_norm_data_dict.items():
    par_bin_norm_attempts_list.append(attempts)
    par_bin_norm_means.append(np.mean(values))
    par_bin_norm_std_devs.append(np.std(values))


# Processing sequential binary data
seq_bin_data_dict = {}
for attempts, value in seq_bin_data_list:
    if attempts not in seq_bin_data_dict:
        seq_bin_data_dict[attempts] = []
    seq_bin_data_dict[attempts].append(value)

# Extracting data
seq_bin_attempts_list = []
seq_bin_means = []
seq_bin_std_devs = []
for attempts, values in seq_bin_data_dict.items():
    seq_bin_attempts_list.append(attempts)
    seq_bin_means.append(np.mean(values))
    seq_bin_std_devs.append(np.std(values))

# Computing "normalized" data
seq_bin_norm_data_dict = {}
for attempts, value in seq_bin_norm_data_list:
    if attempts not in seq_bin_norm_data_dict:
        seq_bin_norm_data_dict[attempts] = []
    seq_bin_norm_data_dict[attempts].append(value)

seq_bin_norm_attempts_list = []
seq_bin_norm_means = []
seq_bin_norm_std_devs = []
for attempts, values in seq_bin_norm_data_dict.items():
    seq_bin_norm_attempts_list.append(attempts)
    seq_bin_norm_means.append(np.mean(values))
    seq_bin_norm_std_devs.append(np.std(values))


# Plotting
fig, ax1 = plt.subplots(figsize=(10, 5))
ax1.errorbar(par_bin_attempts_list, par_bin_means, yerr=par_bin_std_devs, fmt='o-', label='Parallel   bitwise', capsize=4, capthick=1)
ax1.errorbar(seq_bin_attempts_list, seq_bin_means, yerr=seq_bin_std_devs, fmt='o-', label='Sequential bitwise', capsize=4, capthick=1)
ax1.set_xscale('log')
ax1.set_yscale('log')
ax1.set_xlabel('attempts')
ax1.set_ylabel('us')
ax1.set_title("Average us per attempts")
ax1.legend()
ax1.grid(True)
plt.savefig('./output/attempts_us')

fig, ax2 = plt.subplots(figsize=(10, 5))
ax2.errorbar(par_bin_norm_attempts_list, par_bin_norm_means, yerr=par_bin_norm_std_devs, fmt='o-', label='Parallel   bitwise', capsize=4, capthick=1)
ax2.errorbar(seq_bin_norm_attempts_list, seq_bin_norm_means, yerr=seq_bin_norm_std_devs, fmt='o-', label='Sequential bitwise', capsize=4, capthick=1)
ax2.set_xscale('log')
ax2.set_xlabel('attempts')
ax2.set_ylabel('Normalized us')
ax2.set_title('"Normalized" us per attempts')
ax2.grid(True)
plt.savefig('./output/normalized_attempts_us')
