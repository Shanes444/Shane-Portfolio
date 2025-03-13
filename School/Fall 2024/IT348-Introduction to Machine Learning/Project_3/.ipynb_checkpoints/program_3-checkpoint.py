# -*- coding: utf-8 -*-
"""
Created on Fri Nov 15 15:21:46 2024

@author: Shane Stevens
"""

import csv

folder = "input_data"

files = ["sampled_2014_benign_api.csv"]

data_set = {}

for file in files:
    with open(folder + "/" + file, mode = 'r') as cur_file:
        csv_file = csv.reader(cur_file)
        for line in csv_file:
            line.pop(0)
            print(line)
            data_set[line] = "benign"


print(data_set)
