四則運算計算機
===

## 簡述
1. 按下等於鍵，把面板上的數字抓成m_list 
    1. ⇒ original m_list: ("2", "*", "", "-", "3", "/", "", "-", "3")
2. 把數字該是負數的先抓出來，並更新m_list
    1. new m_list: ("2", "*", "-3", "/", "-3")
3. 從 m_list 中抓取總共幾個運算元
    1. m_count: 2
4. 判定: 先乘除，後加減
5. 將答案丟到 label_2 上
- 註:
    - clear 按下，m_list 要清空，m_count 歸零
    - equal 按下，m_list 要清空，再丟值進去
 
## 成果
![Recording 2023-02-08 at 11 29 29](https://user-images.githubusercontent.com/39553867/217428049-fa36aa9e-3e5e-4d4c-93e6-b22d58f0a224.gif)
