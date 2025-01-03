# Matrix Simple Operations
import numpy as np
import pandas as pd

FILE_NAME = "matrix.txt"

def print_matrix(matrix):
    """ Converts Numpy Array to Pandas DataFrame for Printing """
    df = pd.DataFrame(matrix)
    print(df.to_string(index=False, header=False), "\n")

def print_divider():
    print("="*60, "\n")

# a) Read data from file
file_data = np.loadtxt(FILE_NAME, dtype=int)  # creates numpy array (ndarray)
print("a) The Original Matrix:")
print_matrix(file_data)
print_divider()

# b) Submatrix Col [3 1 9] Sorting
print("b) Matrix 1: Sorting Submatrix Columns [3 1 9]")
print("Submatrix Columns [3 1 9]:")
M1_temp = file_data[:, [2, 0, 8]]  # array[row, column], ':' means all rows
print_matrix(M1_temp)
print("Sort Column [3] (ascending):")
M1_sorted_indices = M1_temp[:, 0].argsort()  # get sorted indicies of first col (3)
Matrix1 = M1_temp[M1_sorted_indices]  # M1[0] = row 1, so M1[indices] = rows in order of indices
# Matrix1 = M1_temp[M1_temp[:,0].argsort()]  # 1 liner option
print_matrix(Matrix1)
print_divider()

# c) Submatrix Col [5 2 7] Sorting
print("c) Matrix 2: Sorting Submatrix Columns [5 2 7]")
print("Submatrix Columns [5 2 7]:")
M2_temp = file_data[:, [4, 1, 6]]
print_matrix(M2_temp)
print("Sort Column [5] (decending):")
M2_indices = M2_temp[:, 0].argsort()[::-1] # `[::-1]` reverses order
Matrix2 = M2_temp[M2_indices]
#Matrix2 = M2_temp[ M2_temp[:,0].argsort()[::-1] ]  # 1 liner option
print_matrix(Matrix2)
print_divider()

# d) Sum of Matrix1 and Matrix2
print("d) Matrix 3: Sum of Matrix1 and Matrix2")
print("  Matrix 1\t  Matrix 2\t  Matrix 3")
print("=" * 44)
# Matrix3 = np.add(Matrix1, Matrix2) `+` is overloaded to np.add
Matrix3 = Matrix1 + Matrix2
spacing_column = np.full((Matrix1.shape[0], 1), '')  # for spacing between matrices
# np.full() - returns shape will fill value: np.full((rows, cols), value)
combined_matrix = np.column_stack((Matrix1, spacing_column,
                                   Matrix2, spacing_column,
                                   Matrix3)) # appends each matrix column
df_combined = pd.DataFrame(combined_matrix)
print(df_combined.to_string(index=False, header=False, col_space=3, justify='center'), "\n")
print_divider()

# e) Sum Rows of M3
print("e) Matrix 4: Sum Rows of Matrix3")
Matrix4 = np.sum(Matrix3, axis=1, keepdims=True) # keepdims prevents dim reduction
# '.reshape(-1, 1)' is slow than 'keepdims=True'
print_matrix(Matrix4)
print_divider()

# f) Sort M4 (ascending)
print("f) Matrix 4: Sorting Matrix4 in ascending order:")
Matrix4 = Matrix4[Matrix4[:, 0].argsort()]
#Matrix4 = np.sort(Matrix4, axis=None).reshape(-1, 1) # slower: flatter-sort-reshape operation
print_matrix(Matrix4)
