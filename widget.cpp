#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsDropShadowEffect>


CArrayModel::CArrayModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}




Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setProperty("canMove",true);
    this->initUi();
    this->initMember();


    showAll(); //正常 借出 非正常转移
    SetTableView();

    //当前时间显示
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Data_Show()));
    timer->start(1000);
    ui->widget_4->setStyleSheet("QWidget#widgetMain{border: 1px solid #FF00FF; border-radius: 5px;");



}

Widget::~Widget()
{
    delete ui;
}

/**********************************************************初始化函数****************************************************************/

void Widget::initUi()
{
    //初始化窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(16);
    ui->w_bg->setGraphicsEffect(shadow);
    ui->lay_bg->setMargin(12);

    //Logo
    QPixmap logo(":/icons/logo.png");
    ui->lab_logo->setPixmap(logo);

    //itemLogo
    QPixmap item1(":/icons/item_01.png");
    QPixmap item2(":/icons/item_02.png");
    ui->lab_item_01->setPixmap(item1);
    ui->lab_item_02->setPixmap(item2);
}

void Widget::initMember()
{
    this->myMbox = new MyMessageBox();
    this->wxMbox = new MyMessageBox();
    this->yyMbox = new MyMessageBox();
    connect(myMbox,SIGNAL(btnchicked(int)),this,SLOT(changeMboxReturn(int)));

    //最小化到托盘
    QIcon icon = QIcon(":/icons/logo.png");//设置最小图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("Peach"); //提示文字
    //添加托盘列表项(还原与退出)
    returnNormal = new QAction(" Show", this);
    returnNormal->setFont(QFont("Arial", 9));
    returnNormal->setObjectName("returnNormal");
    returnNormal->setIcon(QIcon(":/icons/show.png"));
    quitAction = new QAction(" Quit", this);
    quitAction->setFont(QFont("Arial", 9));
    quitAction->setObjectName("quitAction");
    quitAction->setIcon(QIcon(":/icons/out.png"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));           //绑定槽函数退出
    connect(returnNormal, SIGNAL(triggered()), this, SLOT(showNormal()));   //绑定槽函数还原界面

    //创建托盘菜单(必须先创建动作，后添加菜单项，还可以加入菜单项图标美化)
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(returnNormal);
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
}

/**********************************************************自定义函数****************************************************************/

void Widget::littleShow()
{
    this->hide();//隐藏主窗口
    trayIcon->show();//显示托盘

    //显示到系统提示框的信息
    QString title="Peach";
    QString text="正自动在后台运行";
    trayIcon->showMessage(title,text,QSystemTrayIcon::Information,3000); //此参数为提示时长
}

/**********************************************************控件槽函数****************************************************************/

void Widget::closeEvent(QCloseEvent *event)
{
    myMbox->setIcon("问题");
    myMbox->setBodyText("您想进行什么操作？");
    myMbox->setButtonText("最小化","退出");
    myMbox->exec();
    if(mbox_return == 0) {
        event->ignore();
    }else if(mbox_return == 1){
        event->ignore();
        littleShow();
    }
}

void Widget::changeMboxReturn(int num)
{
    this->mbox_return = num;
}

void Widget::on_btn_main_item_1_clicked()
{
    ui->sw_main->setCurrentIndex(0);
}

void Widget::on_btn_main_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(1);
}

void Widget::on_btn_main_item_3_clicked()
{
    ui->sw_main->setCurrentIndex(2);
}

void Widget::on_btn_main_item_4_clicked()
{
    ui->sw_main->setCurrentIndex(3);
}

void Widget::on_btn_logout_clicked()
{
    close();
}

void Widget::on_btn_littleshow_clicked()
{
    showMinimized();
}
void Widget::Data_Show()
{
        QTime qtimeObj = QTime::currentTime();
        QString strTime = qtimeObj.toString("hh:mm:ss");
        strTime.prepend("");
        QDate qdateObj = QDate::currentDate();
        QString strDate = qdateObj.toString("dd-MM "); //星期、月份、天、年

        strDate.append(strTime);
        ui->lab_item_value_01->setText(strDate);


}


void Widget::on_btn_menu_item_1_clicked()
{
    ui->sw_main->setCurrentIndex(0);
}
//正常 借出 非正常转移
void Widget::showAll()
{




    //借出界面设置
    //modeljc =new QStandardItemModel();
    data = new TableModel;
    ui->tableView_2->setModel(data);
//    modeljc =new QStandardItemModel();
//    ui->tableView_2->setModel(modeljc);
//    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableView_2->setAlternatingRowColors(true);


//    modeljc->setHorizontalHeaderItem(0, new QStandardItem("设备编号"));
//    modeljc->setHorizontalHeaderItem(1, new QStandardItem("设备名称"));
//    modeljc->setHorizontalHeaderItem(2, new QStandardItem("存放地点"));
//    modeljc->setHorizontalHeaderItem(3, new QStandardItem("设备状态"));
//    modeljc->setHorizontalHeaderItem(4, new QStandardItem("设备属性"));
//    modeljc->setHorizontalHeaderItem(5, new QStandardItem("流转状态"));
//    modeljc->setHorizontalHeaderItem(6, new QStandardItem("设备规格"));



//    ui->tableView_2->setColumnWidth(0,142);
//    ui->tableView_2->setColumnWidth(1,142);
//    ui->tableView_2->setColumnWidth(2,142);
//    ui->tableView_2->setColumnWidth(3,142);
//    ui->tableView_2->setColumnWidth(4,142);
//    ui->tableView_2->setColumnWidth(5,142);
//    ui->tableView_2->setColumnWidth(6,140);



    //非正常转移


    modelfzc =new QStandardItemModel();
    ui->tableView_3->setModel(modelfzc);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_3->setAlternatingRowColors(true);


    modelfzc->setHorizontalHeaderItem(0, new QStandardItem("设备编号"));
    modelfzc->setHorizontalHeaderItem(1, new QStandardItem("设备名称"));
    modelfzc->setHorizontalHeaderItem(2, new QStandardItem("存放地点"));
    modelfzc->setHorizontalHeaderItem(3, new QStandardItem("设备状态"));
    modelfzc->setHorizontalHeaderItem(4, new QStandardItem("设备属性"));
    modelfzc->setHorizontalHeaderItem(5, new QStandardItem("流转状态"));
    modelfzc->setHorizontalHeaderItem(6, new QStandardItem("设备规格"));

    ui->tableView_3->setColumnWidth(0,142);
    ui->tableView_3->setColumnWidth(1,142);
    ui->tableView_3->setColumnWidth(2,142);
    ui->tableView_3->setColumnWidth(3,142);
    ui->tableView_3->setColumnWidth(4,142);
    ui->tableView_3->setColumnWidth(5,142);
    ui->tableView_3->setColumnWidth(6,140);

    modelfzc->setItem(10,0,new QStandardItem("0510010277"));
    modelfzc->setItem(10,1,new QStandardItem("电脑"));
    modelfzc->setItem(20,2,new QStandardItem("图书馆"));
    modelfzc->setItem(20,3,new QStandardItem("非正常转移"));
    modelfzc->setItem(20,4,new QStandardItem("重要"));
    modelfzc->setItem(20,6,new QStandardItem("1000RMB"));

}

void Widget::on_btn_main_item_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void Widget::on_btn_main_item_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_btn_main_item_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_btn_main_item_8_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}

void Widget::on_m_pFirstPageBtn_clicked()
{
    m_pDataModel->SetCurPage(0);
    UpdateStatus();

}

void Widget::on_m_pLastPageBtn_clicked()
{
    m_pDataModel->SetCurPage(m_pDataModel->GetPageCount() - 1);
    UpdateStatus();

}

void Widget::on_prevButton_clicked()
{
    m_pDataModel->SetCurPage(m_pDataModel->GetCurPage() - 1);
    UpdateStatus();
}

void Widget::on_nextButton_clicked()
{
    m_pDataModel->SetCurPage(m_pDataModel->GetCurPage() + 1);
    UpdateStatus();
}

void Widget::on_switchPageButton_clicked()
{
    //得到输入字符串
    QString szText = ui->lineEdit_5->text();
    //数字正则表达式
    QRegExp regExp("-?[0-9]*");
    //判断是否为数字
    if(!regExp.exactMatch(szText))
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请输入数字"));

        return;
    }
    //是否为空
    if(szText.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请输入跳转页面"));

        return;
    }
    //得到页数
    int pageIndex = szText.toInt();
    //判断是否有指定页
    if(pageIndex > m_pDataModel->GetPageCount() || pageIndex < 1)
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("页面超出范围，请重新输入"));

        return;
    }
    //记录查询
    m_pDataModel->SetCurPage(pageIndex - 1);
    //刷新状态
    UpdateStatus();

    return;
}




//设置Model数据
void CArrayModel::SetArrayData(const std::map<int, QString> &map)
{
    m_mpData = map;
}

////获得总数据
std::map<int, QString> CArrayModel::GetArrayData()
{
    return m_mpData;
}

//总行数
int CArrayModel::RowCount() const
{
    return m_mpData.size();
}

//设置页数据
void CArrayModel::SetCurPage(int iPage)
{
    //当前页必须小于总页数
    if (iPage < GetPageCount())
    {
        m_iCurPage = iPage;

        //查询起始索引
        int iStart = m_iPageSize * m_iCurPage;
        //查询结束索引
        int iend = 0;
        //如果本页可以填满
        if (iStart + m_iPageSize < RowCount())
        {
            iend = iStart + m_iPageSize;
        }
        //如果本页不可以填满
        else
        {
            iend = RowCount() - 1;
        }

        //填充当前页数据
        m_mpPageData.clear();
        for (int i = iStart; i <= iend; ++i)
        {
            auto it = m_mpData.find(i);
            if (it == m_mpData.end())
            {
                return;
            }

            m_mpPageData.insert(std::pair<int, QString>(i, it->second));
        }
    }

    return;
}

//获得当前页
int CArrayModel::GetCurPage()
{
    return m_iCurPage;
}

//获得总页数
int CArrayModel::GetPageCount()
{
    return (RowCount() % m_iPageSize == 0)
        ? (RowCount() / m_iPageSize)
        : (RowCount() / m_iPageSize + 1);
}

//设置每页数据条数
void CArrayModel::SetPageSize(int iPageSize)
{
    if (iPageSize <= 0)
    {
        return;
    }

    m_iPageSize = iPageSize;
    SetCurPage(0);

    //刷新Model，否则TableView不会刷新显示
    refrushModel();
}


//获得每页数据条数
int CArrayModel::GetPageSize()
{
    return m_iPageSize;
}

//行数
int CArrayModel::rowCount(const QModelIndex & parent) const
{
    return m_iPageSize;
}

//列数
int CArrayModel::columnCount(const QModelIndex & parent) const
{
    //仅仅有两列数据
    return 7;
}


void CArrayModel::refrushModel()
{
    beginResetModel();
    endResetModel();
}

QVariant CArrayModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole)
    {
        if ( 0 == index.column())
        {
            //如果处于最后一页，索引没必要全部列出，只列出范围内的
            if (index.row() + m_iCurPage * m_iPageSize > this->RowCount())
            {
                return QVariant();
            }

            return index.row() + m_iCurPage * m_iPageSize;
        }
        else if (1 == index.column())
        {
            auto it = m_mpPageData.find(index.row() + m_iCurPage * m_iPageSize);
            if (it != m_mpPageData.end())
            {
                return it->second;
            }
        }
    }

    return QVariant();
}

Qt::ItemFlags CArrayModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CArrayModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        QVariant oldData = data(index, Qt::EditRole);
        QString strold = oldData.toString();
        QString strnew = value.toString();
        //相同则不编辑
        if (strnew.compare(strold) == 0)
        {
            return true;
        }

        //计算实际数据的下标
        int dataindex = index.row() + m_iCurPage * m_iPageSize;

        //改变总数据集
        auto it  = m_mpData.find(dataindex);
        if (it != m_mpData.end())
        {
            it->second = strnew;
        }

        //改变当页数据集
        auto itcur = m_mpPageData.find(dataindex);
        if (itcur != m_mpPageData.end())
        {
            itcur->second = strnew;
        }

        return true;
    }
    return false;
}

//QVariant CArrayModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (role != Qt::DisplayRole)
//    {
//        return QVariant();
//    }

//    if (0 == section)
//    {
//        return QStringLiteral("");
//    }
//    else if (1 == section)
//    {
//        return QStringLiteral("");
//    }

//    return QVariant();
//}


QString CArrayModel::currencyAt(int offset) const
{
    auto it = m_mpData.find(offset);
    if (it != m_mpData.end())
    {
        return it->second;
    }

    return QString();
}

void Widget::SetTableView()
{
    //声明查询模型
    m_pDataModel = new CArrayModel;


    std::map<int, QString> map;


    //修改数据
    for (int i = 0; i < 10000; ++i)
    {
        QString str = QString("%1").arg(QString::number(i+2));  //数据
        map.insert(std::pair<int, QString>(i, str));

    }

    m_pDataModel->SetArrayData(map);

    //设置每页数据条数
    m_pDataModel->SetPageSize(17);

    //设置模型
    ui->tableView_1->setModel(m_pDataModel);
    ui->tableView_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_1->setAlternatingRowColors(true);

        //m_pDataModel->setHorizontalHeaderItem(0, new QStandardItem("设备编号"));
//        modelqb->setHorizontalHeaderItem(1, new QStandardItem("设备名称"));
//        modelqb->setHorizontalHeaderItem(2, new QStandardItem("存放地点"));
//        modelqb->setHorizontalHeaderItem(3, new QStandardItem("设备状态"));
//        modelqb->setHorizontalHeaderItem(4, new QStandardItem("设备属性"));
//        modelqb->setHorizontalHeaderItem(5, new QStandardItem("流转状态"));
//        modelqb->setHorizontalHeaderItem(6, new QStandardItem("设备规格"));


    ui->tableView_1->setColumnWidth(0,142);
    ui->tableView_1->setColumnWidth(1,142);
    ui->tableView_1->setColumnWidth(2,142);
    ui->tableView_1->setColumnWidth(3,142);
    ui->tableView_1->setColumnWidth(4,142);
    ui->tableView_1->setColumnWidth(5,142);
    ui->tableView_1->setColumnWidth(6,140);


    //设置委托
    ui->tableView_1->setItemDelegateForColumn(0, new ReadOnlyDelegate(this));
//    tableView->setItemDelegateForColumn(1, new ValueDelegate(this));

    //刷新状态
    UpdateStatus();

    return;
}

//刷新界面状态
void Widget::UpdateStatus()
{
    //刷新表格
    ui->tableView_1->reset();

    //总页数
    QString szPageCountText = QString(QStringLiteral("总共%1页")).arg(QString::number(m_pDataModel->GetPageCount()));
    ui->totalPageLabel->setText(szPageCountText);

    //设置当前页文本
    int iCurPage = m_pDataModel->GetCurPage() + 1;
    QString szCurrentText = QString(QStringLiteral("当前第%1页")).arg(QString::number(iCurPage));
    ui->currentPageLable->setText(szCurrentText);

    //每页显示行数
//    QString strPerPageCount = QString(QStringLiteral("%1")).arg(QString::number(m_pDataModel->GetPageSize()));
//    m_pPerPageCountEdit->setText(strPerPageCount);

    //当前第一页，且总共只有一页
    if (1 == iCurPage && 1 == m_pDataModel->GetPageCount())
    {
        ui->m_pFirstPageBtn->setEnabled(false);
        ui->m_pLastPageBtn->setEnabled(false);
        ui->prevButton->setEnabled(false);
        ui->nextButton->setEnabled(false);

    }
    //当前第一页，且总页数大于1页
    else if(1 == iCurPage && m_pDataModel->GetPageCount() > 1)
    {
        ui->m_pFirstPageBtn->setEnabled(false);
        ui->m_pLastPageBtn->setEnabled(true);
        ui->prevButton->setEnabled(false);
        ui->nextButton->setEnabled(true);
    }
    //当前是最后一页
    else if(iCurPage == m_pDataModel->GetPageCount())
    {
        ui->m_pFirstPageBtn->setEnabled(true);
        ui->m_pLastPageBtn->setEnabled(false);
        ui->prevButton->setEnabled(true);
        ui->nextButton->setEnabled(false);
    }
    //中间页
    else
    {
        ui->m_pFirstPageBtn->setEnabled(true);
        ui->m_pLastPageBtn->setEnabled(true);
        ui->prevButton->setEnabled(true);
        ui->nextButton->setEnabled(true);
    }

    return;
}

void Widget::on_sgButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Widget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Widget::on_btn_menu_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(1);
}

void Widget::on_btn_menu_item_3_clicked()
{
    ui->sw_main->setCurrentIndex(3);
}

void Widget::on_pushButton_9_clicked()
{

    wxMbox->setIcon("维修状态");
    wxMbox->setBodyText("正在维修，两星期完成");
    wxMbox->setButtonText("退出","确定");
    wxMbox->exec();
}



void Widget::on_pushButton_14_clicked()
{
    yyMbox->setIcon("预约情况");
    yyMbox->setBodyText("恭喜您预约成功");
    yyMbox->setButtonText("返回","确定");
    yyMbox->exec();
}

void Widget::on_pushButton_10_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

void Widget::on_pushButton_11_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}

void Widget::on_pushButton_12_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(2);
}

void Widget::on_btn_main_item_17_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(3);
}

void Widget::on_pushButton_15_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(3);
}



void Widget::on_rfidButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}

void Widget::on_btn_menu_item_4_clicked()
{
    ui->sw_main->setCurrentIndex(5);
}
