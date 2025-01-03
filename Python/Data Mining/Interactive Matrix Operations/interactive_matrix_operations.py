# Interactive OO Matrix Operations
import numpy as np
import pandas as pd

SEPARATOR_LINE = "=" * 82

def main():
    MIN_MATRIX_DIMS = 3
    MAX_MATRIX_DIMS = 8
    FILE_1 = 'file1.txt'
    FILE_2 = 'file2.txt'

    # Get Matrix Dimensions from User
    try:
        dims = int(input("Enter matrix dimension: "))

        error_messages = {  # Dimension boundary 3 - 8
            (dims < MIN_MATRIX_DIMS): "Error: This dimension is out of bound.",
            (dims > MAX_MATRIX_DIMS): "Error: We can only handle up to 8 dimensions at this time."
        }
        error_message = error_messages.get(True, "")
        assert not error_message, error_message
    except AssertionError as e:
        print(str(e))
        print("(*********************** End of the Program ************************)")
        return

    my_matrix = Matrix()

    try:
        # Get square matrices (size = dims^2)
        matrix_1 = my_matrix.get_matrix(dims, FILE_1)
        matrix_2 = my_matrix.get_matrix(dims, FILE_2)
        print("Matrix 1:")
        my_matrix.print_matrix(matrix_1)
        print(SEPARATOR_LINE)
        print("Matrix 2:")
        my_matrix.print_matrix(matrix_2)
        print(SEPARATOR_LINE)

        # Matrix Operations
        print("Multiply | Matrix 1 * Matrix 2:")
        matrices_product = my_matrix.product(matrix_1, matrix_2)
        my_matrix.print_matrix(matrices_product)
        print(SEPARATOR_LINE)

        print("Dot Product | Matrix 1 . Matrix 2:")
        matrices_dot_product = my_matrix.dot_product(matrix_1, matrix_2)
        my_matrix.print_matrix(matrices_dot_product)
        print(SEPARATOR_LINE)

        print("Divide | Matrix 1 / Matrix 2:")
        matrices_division = my_matrix.division(matrix_1, matrix_2)
        my_matrix.print_matrix(matrices_division)
        print(SEPARATOR_LINE)

    except ValueError:
        print("Error: Please enter a valid integer.")

class Matrix:
    """ Matrix class to handle matrix operations """
    def get_matrix(self, dims, filename) -> np.ndarray:
        return np.loadtxt(filename, usecols=range(dims), max_rows=dims, dtype=int)

    def product(self, matrix_1, matrix_2) -> np.ndarray:
        return np.matmul(matrix_1, matrix_2)

    def dot_product(self, matrix_1, matrix_2) -> np.ndarray:
        return np.dot(matrix_1, matrix_2)

    def division(self, matrix_1, matrix_2) -> np.ndarray:
        with np.errstate(divide='ignore', invalid='ignore'):
            result = np.divide(matrix_1, matrix_2)
        result = np.round(result, 2)
        result = np.where(np.isinf(result) | np.isnan(result), "undef", result)
        return result

    def print_matrix(self, matrix) -> None:
        df = pd.DataFrame(matrix)
        print(df.to_string(index=False, header=False), "\n")

if __name__ == "__main__":
    main()
