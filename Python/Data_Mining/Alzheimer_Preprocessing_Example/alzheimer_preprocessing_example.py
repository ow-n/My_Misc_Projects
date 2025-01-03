"""Small-Scale Alzheimer data cleaning"""
import pandas as pd
from sklearn.preprocessing import MinMaxScaler, StandardScaler

SEPARATOR_LINE = "=" * 82

def main():
    DATASET_NAME = 'Alzheimer2.csv'
    OUTPUT_EXCEL_NAME = 'Alzheimer2_Processed.xlsx'
    IC50_COL_INDEX = 0  # Assume IC50 in first col

    processor = DataProcessor()

    print("Dataset: Alzheimer2.csv")
    df_ori = pd.read_csv(DATASET_NAME, dtype=str, header=None)
    print(df_ori)
    print("Data Column Names: ", df_ori.columns)
    print("\n", SEPARATOR_LINE, "\n")
    df = df_ori.apply(pd.to_numeric, errors='coerce')

    print("Removing Junk Cols: if num junk is >= 70% of col")
    processor.remove_junk_columns(df)
    print("\n", SEPARATOR_LINE, "\n")

    print("Removing Zero Cols: if num zeros >= 90% of col")
    df = processor.remove_zero_columns(df)
    print("\n", SEPARATOR_LINE, "\n")

    print("Removing Junk Rows: if num junk < 70% of row")
    df = processor.remove_low_junk_rows(df)
    print("\n", SEPARATOR_LINE, "\n")

    print("Removing Rows without value in IC50 Column")
    df = processor.remove_rows_without_value(df, IC50_COL_INDEX)
    print("\n", SEPARATOR_LINE, "\n")

    print("Replacing Junk Vals with Col Median")
    df_cleaned = processor.replace_junk_with_col_median(df)  # Cleaned
    print("\n", SEPARATOR_LINE, "\n")

    print("Rescaling the cleaned array")
    df_rescaled = processor.rescale_data(df)  # Rescaled
    print("\n", SEPARATOR_LINE, "\n")

    print("Normalizing the cleaned array")
    df_norm = processor.normalize_data(df_rescaled)  # Normalized
    print("\n", SEPARATOR_LINE, "\n")

    print("Creating Excel file with all data versions")
    processor.create_excel_file(df_ori, df_cleaned, df_rescaled, df_norm, OUTPUT_EXCEL_NAME)
    print("\n", SEPARATOR_LINE, "\n")


class DataProcessor:
    """Interface for Data Processing Operations"""

    def remove_junk_columns(self, df):
        """Remove Columns with >= 70% Junk Data"""
        junk_cols_percent = df.isna().mean()  # create pd Series of col %'s of NaNs
        junk_cols = junk_cols_percent >= 0.7  # Bool Mask: cols less than 70% junk

        junk_col_indices = (df.columns[junk_cols] + 1).astype(str)  # get indices to drop
        junk_col_names = "X" + junk_col_indices  # col name format: X10, X11, ...
        df = df.drop(columns=df.columns[junk_cols])  # cols=indices to drop
        print("Deleted Cols: ", ", ".join(junk_col_names))
        return df

    def remove_zero_columns(self, df):
        """Remove columns with at least 90% zeros and print columns with more than 250 zeros"""
        zero_col_percent = (df == 0).mean()  # create pd Series of col %'s of zeros
        zero_cols = zero_col_percent >= 0.9  # Bool Mask: cols less than 90% zeros

        zero_col_indices = (df.columns[zero_cols] + 1).astype(str)  # get indices to drop
        zero_col_names = "X" + zero_col_indices  # col name format: X10, X11, ...
        df = df.drop(columns=df.columns[zero_cols])
        print("Deleted Cols: ", ", ".join(zero_col_names))

        print("\nPrinting cols with more than 250 zeros")
        cols_with_many_zeros_mask = (df == 0).sum() > 250  # get indices with > 250 zeros
        cols_with_many_zeros = (df.columns[cols_with_many_zeros_mask] + 1).astype(str)
        cols_with_many_zeros_names = "X" + cols_with_many_zeros
        print("Cols with 250 Zeroes: ", ", ".join(cols_with_many_zeros_names))
        return df

    def remove_low_junk_rows(self, df):
        """
        "Remove rows with less than 70% junk data"
        Or in other words, keep only rows with >= 70% junk data
        Or remove rows with less than 30% valid data
        Rows_to_remove = x < 0.7
        This keeps rows with more than 70% junk ??? Strange
        """
        junk_row_percent = df.isna().mean(axis=1)  # create pd Series of row %'s of zeroes
        junk_rows = junk_row_percent < 0.7  # Bool Mask: rows with >= 70% junk

        junk_row_indices = (df.index[junk_rows] + 1).astype(str)  # get indices to drop
        junk_row_names = "Y" + junk_row_indices  # col name format: X10, X11, ...
        df = df[~junk_rows]
        print("Deleted Cols:", ", ".join(junk_row_names))
        return df

    def remove_rows_without_value(self, df, col_idx):
        """Remove rows without a value in the specified column"""
        rows_without_value = df.iloc[:, col_idx].isna()  # Bool Mask: rows with missing values in col
        deleted_row_indices = (df.index[rows_without_value] + 1).astype(str)  # get indices for name
        deleted_row_names = "Y" + deleted_row_indices  # row name format: Y10, Y11, ...

        df = df[~rows_without_value]  # remove rows with missing values in col
        print("Deleted Rows:", ", ".join(deleted_row_names))
        return df

    def replace_junk_with_col_median(self, df):
        """Replace any remaining NaN values with the median of their columns"""
        col_medians = df.median(numeric_only=True)  # get col medians
        nan_locations = df.isna()  # get NaN locations
        df = df.fillna(col_medians)  # fill NaNs

        # New df with same shape: filled with col medians
        median_values = pd.DataFrame().reindex_like(df).fillna(col_medians)
        replaced_values = median_values[nan_locations]  # get replaced vals with bool index/NaN loc

        # Create string representation of the replaced cells
        replaced_cells = replaced_values.stack().reset_index()
        replaced_cells.columns = ['Row', 'Column', 'Median']
        replaced_cells['Row'] = replaced_cells['Row'] + 1  # fix 0-based indexing
        replaced_cells['Column'] = replaced_cells['Column'].astype(int) + 1  # fix 0-based indexing
        replaced_cells = replaced_cells[replaced_cells['Median'] != 0]

        print("Replaced Cells:")
        print(replaced_cells.to_string(index=False))        
        return df

    def rescale_data(self, df):
        """Rescale data between 0 and 1 using MinMaxScaler"""
        scaler = MinMaxScaler()
        df = pd.DataFrame(scaler.fit_transform(df), columns=df.columns, index=df.index)
        print("The Alzheimer's Data have been rescaled")
        return df

    def normalize_data(self, df):
        """Normalize data using Z-score standardization"""
        scaler = StandardScaler()
        df_normalized = pd.DataFrame(scaler.fit_transform(df), columns=df.columns, index=df.index)
        print("The Alzheimer's Data have been normalized")
        return df_normalized

    def create_excel_file(self, original_df, cleaned_df, rescaled_df, normalized_df, filename):
        """Create Excel file with four tabs for each data preprocessing step"""
        with pd.ExcelWriter(filename, engine='openpyxl') as writer:
            original_df.to_excel(writer, sheet_name='Original Data', index=False)
            cleaned_df.to_excel(writer, sheet_name='Cleaned Data', index=False)
            rescaled_df.to_excel(writer, sheet_name='Rescaled Data', index=False)
            normalized_df.to_excel(writer, sheet_name='Normalized Data', index=False)

        print(f"Excel file '{filename}' has been created with the following tabs:")
        print("1. Original Data")
        print("2. Cleaned Data")
        print("3. Rescaled Data")
        print("4. Normalized Data")

if __name__ == "__main__":
    main()
