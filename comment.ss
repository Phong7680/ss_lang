(def x 1) // xの定義
(def y 2) // yの定義
(fun (min x y) (if (< x y) x y)) //　最初値
(fun (fact n) (if (= n 0) 1 (* n (fact (- n 1)))))) // 階乗
(min x y)
(fact y)
