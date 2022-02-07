Program that uses OLS with SGD\


Repo contains:\
    -Pytest\
    -Environment\
    -csv interface\
    -jupyter notebook\

Create own interface or use csv_inteface.py to load dataset from .csv files\
base.py model should then learn and predict next values

Usage:\
    model = OLS(max_iter, tolerance=0.001, learning_rate=0.1)\
    model.fit(X_train,y_train)\
    y_pred = model.predict(X_test)\
    score(y_test, y_pred)\
