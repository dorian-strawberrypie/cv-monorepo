import pandas as pd


def read_from_csv(filename, target_name=None, header_row=None, indexer_column=None):
    data = pd.read_csv(filename, header=header_row)
    predictives = list(data.columns.values).copy()

    # remove indexer and target from predictives
    if target_name is not None and header_row is not None:
        predictives.remove(target_name)
    if indexer_column is not None:
        predictives.pop(indexer_column)

    X_matrix = data[predictives].to_numpy()
    if target_name is not None and header_row is not None:
        y_vector = data[[target_name, ]].to_numpy()

    # use 80% as training data, 20% as test data
    data_split = int(y_vector.size * 0.8)
    X_train = X_matrix[:data_split]
    X_test = X_matrix[data_split:]
    y_train = y_vector[:data_split]
    y_test = y_vector[data_split:]
    return X_train, y_train, X_test, y_test
