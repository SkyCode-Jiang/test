#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//最小化相关
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include<QTime>
#include<QDate>
#include<QStandardItemModel>
//翻页用Model
#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <vector>
#include<QMessageBox>

//自定义弹窗
#include "mymessagebox.h"
#include"tablemodel.h"




namespace Ui {
  class Widget;
  class QAbstractTableModel;
}




class CArrayModel : public QAbstractTableModel
{
public:
    CArrayModel(QObject *parent = 0);
    //设置总数据
    void SetArrayData(const std::map<int, QString> &map);


    //获得总数据

    std::map<int, QString> GetArrayData();


    //设置页数据
    void SetCurPage(int iPage);
    //获得当前页
    int GetCurPage();
    //获得总页数
    int GetPageCount();
    //设置每页数据条数
    void SetPageSize(int iPageSize);
    //获得每页数据条数
    int GetPageSize();

    //总行数
    int RowCount() const;
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole);
   // QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void refrushModel();
private:
    QString currencyAt(int offset) const;
    std::map<int, QString> m_mpData;    //总数据
    std::map<int, QString> m_mpPageData;//每页数据
    int m_iPageSize;                    //每页数据条数
    int m_iCurPage;                     //当前页
};




class ReadOnlyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget*parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        return NULL;
    }
};

////值列
//class ValueDelegate : public QItemDelegate
//{
//    Q_OBJECT
//public:
//    ValueDelegate(QObject *parent = 0): QItemDelegate(parent) { }
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,  const QModelIndex &index) const;
//    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const;
//    void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
//    void updateEditorGeometry(QWidget *editor,  const QStyleOptionViewItem &option, const QModelIndex &index) const;
//};






class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QTimer *timer;

    void showAll();
    QStandardItemModel *modelqb;
    QStandardItemModel *modeljc;
    TableModel *modejc;
    QStandardItemModel *modelfzc;


private slots:
    void closeEvent(QCloseEvent *event);
    void changeMboxReturn(int num);
    void on_btn_main_item_1_clicked();
    void on_btn_main_item_2_clicked();
    void on_btn_main_item_3_clicked();
    void on_btn_main_item_4_clicked();
    void on_btn_logout_clicked();
    void on_btn_littleshow_clicked();
     void Data_Show();
     void on_btn_menu_item_1_clicked();

     void on_btn_main_item_5_clicked();

     void on_btn_main_item_6_clicked();

     void on_btn_main_item_7_clicked();

     void on_btn_main_item_8_clicked();

       //首页按钮按下
       //末页按钮按下
       //前一页按钮按下
       //后一页按钮按下
       //转到页按钮按下

     void on_m_pFirstPageBtn_clicked();

     void on_m_pLastPageBtn_clicked();

     void on_prevButton_clicked();

     void on_nextButton_clicked();

     void on_switchPageButton_clicked();

     void on_sgButton_clicked();

     void on_pushButton_clicked();

     void on_btn_menu_item_2_clicked();

     void on_btn_menu_item_3_clicked();

     void on_pushButton_9_clicked();

     void on_pushButton_14_clicked();

     void on_pushButton_10_clicked();

     void on_pushButton_11_clicked();

     void on_pushButton_12_clicked();

     void on_btn_main_item_17_clicked();

     void on_pushButton_15_clicked();



     void on_rfidButton_clicked();

     void on_btn_menu_item_4_clicked();

private:
    Ui::Widget *ui;

    MyMessageBox *myMbox;
    MyMessageBox *wxMbox;
    MyMessageBox *yyMbox;
    //自定义窗口通信参数
    int mbox_return;

    //最小化到托盘
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    //窗口管理动作
    QAction *returnNormal;
    QAction *quitAction;

    void initUi();          //Ui界面初始化函数
    void initMember();      //成员变量初始化函数
    void littleShow();      //最小化显示函数

  //  void MyCreateWindow();                   //创建窗口
    void SetTableView();                     //设置表格
    void UpdateStatus();                     //刷新状态
     CArrayModel       *m_pDataModel;        //数据模型
     TableModel *data;


//     TableModel *m_vData;

};

#endif // WIDGET_H
