import numpy as np
import matplotlib.pyplot as plt
import time


class OLS:
    def __init__(self, max_iter=1000, tolerance=.001, learning_rate=.0001):
        self.max_iter = max_iter
        self.tolerance = tolerance
        self.learning_rate = learning_rate
        self.starting_weight = 1
        self.weights = np.ones(shape=(1, 1))
        self.minx, self.maxx, self.miny, self.maxy = 0, 0, 0, 0

    def fit(self, X_train, y_train):

        # adding 1 after last parameter for multiplication with b0
        extended_X_train = np.ones(shape=(X_train.shape[0], X_train.shape[1] + 1))
        extended_X_train[:, :-1] = X_train

        # normalize feature scales for quicker convergence
        X, y = self.feature_scaling(extended_X_train, y_train)

        # starting weight guess
        self.weights = np.zeros(shape=(X.shape[1], 1)) + self.starting_weight
        weights_new = self.weights

        score_history = []
        iters = []
        y_preds = []

        # gradient descent epochs
        for i in range(self.max_iter):
            # compute result prediction as (X * weights)
            y_pred = X.dot(self.weights)
            # compute error function derivation (partial derivation for each weight)
            Derr = derive_error_partially(y, y_pred, X)
            weights_new = self.weights - self.learning_rate * Derr

            # plot
            score_history.append(score(y, y_pred))
            iters.append(i)

            # if weights adjustment < tolerance, we say it converges
            if np.sum((weights_new - self.weights) ** 2) < self.tolerance:
                print('Weights converged!')
                break

            self.weights = weights_new

        plt.figure()
        plt.title("Average squared error overtime")
        plt.plot(iters, score_history, '--')

    # more in sources
    def feature_scaling(self, extended_X_train, y_train):
        Xnorm = extended_X_train.copy()
        self.minx = np.min(Xnorm[:, :-1])
        self.maxx = np.max(Xnorm[:, :-1])
        Xnorm[:, :-1] = (Xnorm[:, :-1] - self.minx) / (self.maxx - self.minx)
        X = Xnorm
        ynorm = y_train.flatten()
        self.maxy = np.max(ynorm)
        self.miny = np.min(ynorm)
        y = ((ynorm - self.miny) / (self.maxy - self.miny)).reshape(-1, 1)
        return X, y

    # value computation with feature scaling
    def predict(self, X):
        xnorm = (X - self.minx) / (self.maxx - self.minx)
        xnorm = np.concatenate((xnorm, np.ones((len(xnorm), 1))), axis=1)
        yprednorm = xnorm.dot(self.weights)
        ypred = yprednorm * (self.maxy - self.miny) + self.miny
        return ypred


# returns partial derivative of each weight
def derive_error_partially(y, y_pred, X_train):
    n = X_train.shape[1]
    derived_results = -1/n * np.sum((y - y_pred) * X_train, axis=0).reshape(-1, 1)
    return derived_results


# computes squared error per test data element
def score(y_test, y_pred):
    errors = np.subtract(y_test, y_pred)
    errors_squared = np.multiply(errors, errors)
    m = y_pred.size
    return (np.sum(errors_squared) / m)
