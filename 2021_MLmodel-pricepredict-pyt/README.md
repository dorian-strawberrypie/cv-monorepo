Assignment:

"
Vaším úkolem je naimplementovat modul, který implementuje hledání vah pomocí OLS s SGD a pro nová data predikuje výstupní hodnoty. Modul následně otestujte pomocí unit testů a použijte na hledání modelu pro zadaná data (boston.csv, popis dat https://scikit-learn.org/stable/datasets/index.html#boston-dataset) v jupyter notebooku. Data načtěte pomocí pandas, poté najděte koeficienty na základě 80% náhodných vzorků. Zbylých 20% vzorků použijte na testování modelu, tj. spočtěte jak se liší Vaše predikce a naměřené hodnoty. Kromě toho implementujte několik visualizací
"

summary: Implement a deep learning algorithm that predicts for example housing prices in Boston


My solution contains:\
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
