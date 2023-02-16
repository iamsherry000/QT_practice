Results
![image](https://user-images.githubusercontent.com/39553867/219256369-1d05a927-2231-4252-9f22-61e5f462fb08.png)
![image](https://user-images.githubusercontent.com/39553867/219256389-8ecc9bff-53fc-41ac-b6d1-97f5fe6b240c.png)


## 思考

- use wmic instead of QSysInfo
    - wmic could be more useful
- My steps
    - use wmic instead of QSysInfo
    - get cpu and get slots simply by wmic command
    - get banklabel,capacity,manufacturer,partnumber,serialnumber
        - wmic command
        - split by (QRegExp("[\r\n]") into QStringList
        - announce the titles and make it constant
        - from what we get in QStringList and sign to the ram structure
        - qDebug the answer
 - 從header抓出各項名稱(法一)
    - 方法一
        - 用space去計算每個字元中間的空白
        - 用QList<int> value_list 去接每個space有值的位置
- 從header抓出各項名稱(法二 better)
    - 方法二
      - 用.toStdString()把原本的Qstring轉成String
      - 用find()去抓String position
## Notion 紀錄
https://happy-chemistry-9fd.notion.site/Day27-e202f99a6684481bb9bfbc2439992db9
