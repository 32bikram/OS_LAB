import multiprocessing
import random
import time
import argparse

parser = argparse.ArgumentParser(description="Example script")
parser.add_argument("Dimension",type = int, help="Add dimension of matrix")
parser.add_argument("Threads", type=int, help="Parallel Threads")
parser.add_argument("mod_value", type = int, help = "mod_value")
parser.add_argument("print_switch", type = int, help=" this is print switch")
args = parser.parse_args()

def fun(args):
    row_index, row, B = args
    row_length = len(row)
    B_col_len = len(B[0])
    results = []
    temp = 0
    for i in range(B_col_len):
        temp = 0
        for j in range(len(B)):
                temp += (row[j]*B[j][i])
        results.append(temp)
    return (row_index,results)
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


