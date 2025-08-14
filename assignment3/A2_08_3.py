"""
************************************************************************
DATE: 14-08-2025
Assignment-3
Group:A2
Team:08

Name: Partha Roy ,      Roll-302411001004 
Name: Bikram Sarkar ,   Roll-302411001008
Name: Bikram Dutta,     Roll-002311001071

# What this Program Does-
    parallel program in Python which will do Matrix Multiplication between
    two large Square Matrices with unsigned integer elements.

# Sample Execution Command-
   python A2_08_3.py <Dimension> <Threads> <mod_value> <print_switch>
# Actual Execution Command-
   python A2_08_3.py 5 4 10 1

# Sample Output-
    generating 2, n X n matrix
    Starting parallel matrix multiplication...
    Starting The Timer
    [PID xx ] Processing row xx
    [PID xx ] Processing row xx
    [PID xx ] Processing row xx
    [PID xx ] Processing row xx
    [PID xx ] Processing row xx
    Matrix multiplication completed in xx.xx seconds
    HERE IS RESULT MATRIX:
    [xx, xx, .......]
    [xx, xx, .......]
    [xx, xx, .......]
    [xx, xx, .......]
    [xx, xx, .......]
    [...............]
    [...............]

# Actual Output-
    generating 2, 5 X 5 matrix
    Starting parallel matrix multiplication...
    Starting The Timer
    [PID 18545] Processing row 0
    [PID 18546] Processing row 1
    [PID 18547] Processing row 2
    [PID 18548] Processing row 3
    [PID 18549] Processing row 4
    Matrix multiplication completed in 0.13 seconds
    HERE IS RESULT MATRIX:
    [86, 28, 80, 49, 55]
    [107, 7, 86, 99, 121]
    [127, 13, 100, 115, 136]
    [175, 42, 151, 111, 132]
    [154, 33, 130, 118, 129]

# System Command used-
    cpustat - used to monitor CPU utilization over time, to show process ID
# Output of 'cpustat'-
    %CPU   %USR   %SYS     PID S  CPU    Time Task
    91.00  91.00   0.00   18549 R    6   1.14s python
    91.00  89.00   2.00   18548 R    0   1.14s python
    91.00  91.00   0.00   18547 R    5   1.14s python
    90.00  89.00   1.00   18546 R    2   1.14s python
    5.00   5.00   0.00   18545 S    5   0.23s python
    4.00   3.00   1.00     946 S    1   3.23m /home/kiertolainen/.vscode-server/bin/488a1f239235055e34e673291fb8d8c810886f81/node
    3.00   1.00   2.00   17516 S    6   9.87s /home/kiertolainen/.vscode-server/bin/488a1f239235055e34e673291fb8d8c810886f81/node
    2.00   1.00   1.00    5435 S    1   0.35s /init
    1.00   1.00   0.00   17716 R    2   0.14s cpustat
***********************************************************************************************************************************
"""

import multiprocessing
import random
import time
import argparse
import os

parser = argparse.ArgumentParser(description="Example script")
parser.add_argument("Dimension",type = int, help="Add dimension of matrix")
parser.add_argument("Threads", type=int, help="Parallel Threads")
parser.add_argument("mod_value", type = int, help = "mod_value")
parser.add_argument("print_switch", type = int, help=" this is print switch")
args = parser.parse_args()


def fun(args):
    row_index, row, B = args
    
    # Print the PID of the process running this function
    print(f"[PID {os.getpid()}] Processing row {row_index}")

    row_length = len(row)
    B_col_len = len(B[0])
    results = []
    
    for i in range(B_col_len):
        temp = 0
        for j in range(len(B)):
            temp += (row[j] * B[j][i])
        results.append(temp)
    
    return (row_index, results)

def generate_matrix(n, mod_val):
    return[[random.randint(0, 2**31-1) % mod_val for _ in range(n)] for _ in range(n)]
if __name__ == "__main__":
    n = args.Dimension
    mod_val = args.mod_value
    print("generating 2,",args.Dimension,"X",args.Dimension,"matrix")
    A = generate_matrix(n, mod_val)
    B= generate_matrix(n, mod_val)
    
    print("Starting parallel matrix multiplication...")
    print("Starting The Timer")
    start_time = time.time()
    
    with multiprocessing.Pool(processes=args.Threads) as pool:
        tasks = []
        for i,row in enumerate(A):
            tasks.append((i, row, B))
        results = pool.map(fun, tasks)
        
    end_time = time.time()
    print("Matrix multiplication completed in {:.2f} seconds".format(end_time - start_time))


    results.sort(key = lambda x: x[0])
    C = [row for idx, row in results]
    
    if(args.print_switch==1):
        print("HERE IS RESULT MATRIX: ")
        for row in C:
            print (row)


