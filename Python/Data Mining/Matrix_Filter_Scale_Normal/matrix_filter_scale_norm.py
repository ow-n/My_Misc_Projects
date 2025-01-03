# Matrix Filtering / Scaling / Normalization
import pandas as pd

FILE_NAME = "dataset.txt"

print("Matrix 0: Original Matrix")
Matrix0 = pd.read_csv(FILE_NAME, dtype=str, delimiter='\t')
print(Matrix0, "\n","="*80, "\n")
Matrix0 = Matrix0.apply(pd.to_numeric, errors='coerce')  # Convert dtype=numeric, invalid->NaN(not a num)

print("Matrix1: Remove Cols (All 0 || At least 5 junk) from M0")
all_zero_cols = (Matrix0 == 0).all()    # Mask: any in column is non-zero
nan_cols = Matrix0.isna().sum() >= 5    # Mask: 5 or more NaNs in column
invalid_cols = all_zero_cols | nan_cols # Combine Masks
Matrix1 = Matrix0.loc[:, ~invalid_cols] # Filter cols using Mask (loc=explicit index labels)
print(Matrix1, "\n","="*80, "\n")

print("Matrix 2: Remove Rows (All 0 | At least 5 junk) from M1")
zero_rows = (Matrix1 == 0).all(axis=1)      # Mask: any in row is non-zero
nan_rows = Matrix1.isna().sum(axis=1) >= 5  # Mask: less than 5 NaNs in row
invalid_rows = zero_rows | nan_rows         # Combine Masks
Matrix2 = Matrix1.loc[~invalid_rows]        # Filter rows using Mask
print(Matrix2, "\n","="*80, "\n")

print("Matrix 3: Replace Col junk values its column's mean")
col_means = Matrix2.mean(axis=0, skipna=True)  # Calculate column means
Matrix3 = Matrix2.fillna(col_means)            # Replace NaN->Means (auto aligns)
print(Matrix3, "\n","="*80, "\n")

print("Matrix 4: Replace Row junk values with its row's mean")  # redundant as no NaNs
row_means = Matrix3.mean(axis=1, skipna=True)                   # Calculate row means
Matrix4 = Matrix3.fillna(row_means)                             # Replace NaN->Means (auto aligns)
print(Matrix4, "\n","="*80, "\n")

print("Matrix5 = Rescale each column (Z-score standardization)")
''' Z-score standardization: (x - mean) / std
    std(ddof=0) = population std, whereas ddof=1 is sample std
    Pandas Vectoriation allows easy column-wise operations
    Pandas default Arithmetic Operations to apply it Element-Wise'''
Matrix5 = (Matrix4 - Matrix4.mean()) / Matrix4.std(ddof=0)
print(Matrix5, "\n","="*80, "\n")

print("Matrix6: Normalize the standardized matrix (Min-Max Normalization)")
''' Min-Max Normalization: (x - min(X)) / (max(X) - min(X))
    This scales all values to be between 0 and 1 '''
Matrix6 = (Matrix5 - Matrix5.min()) / (Matrix5.max() - Matrix5.min())
print(Matrix6)
