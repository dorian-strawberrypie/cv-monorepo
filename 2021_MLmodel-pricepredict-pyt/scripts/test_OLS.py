import pytest
import numpy as np
from numpy.testing import assert_equal
from OLS.base import OLS, score, derive_error_partially
from OLS.csv_interface import read_from_csv


@pytest.mark.parametrize(
    'a, b, r_squared',
    [
        (np.arange(-5, 3).reshape((8, 1)), np.arange(8).reshape((8, 1)), 25),
        (np.arange(8).reshape((8, 1)), np.arange(-5, 3).reshape((8, 1)), 25)
    ]
)
def test_score(a, b, r_squared):
    assert_equal(r_squared, score(a, b))


@pytest.mark.parametrize(
    'path, target_name, header_row, indexer_column, expected',
    [
        ('datasets/test_read.csv', 'col2', 0, 0, (np.array([[3, 4], [7, 8], [11, 12]]),
                                                  np.array([[2], [6], [10]]),
                                                  np.array([[15, 16]]),
                                                  np.array(14))),
        ('datasets/test_read.csv', 'col2', 0, None, (np.array([[1, 3, 4], [5, 7, 8], [9, 11, 12]]),
                                                     np.array([[2], [6], [10]]),
                                                     np.array([[13, 15, 16]]),
                                                     np.array(14)))
    ]
)
def test_read_csv(path, target_name, header_row, indexer_column, expected):
    X_train, y_train, X_test, y_test = read_from_csv(path, target_name, header_row, indexer_column)
    assert_equal((X_train, y_train, X_test, y_test), expected)
    model = OLS(max_iter=10000, tolerance=0.001, learning_rate=0.001)
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    squared_error = score(y_test, y_pred)
    print('Squared error: ', squared_error)


@pytest.mark.parametrize(
    'X_train, y_train, expected_weights',
    [
        (np.broadcast_to(np.arange(1, 4), (3, 3)), np.array([1]), np.ones(shape=(4, 1))),
        (np.reshape(np.arange(16), (2, 8)), np.array([1]), np.ones(shape=(9, 1)))
    ]
)
def test_fit(X_train, y_train, expected_weights):
    model = OLS(max_iter=0)
    model.fit(X_train, y_train)
    assert_equal(model.weights, expected_weights)
