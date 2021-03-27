//数据model部分
#include "tablemodel.h"

TableModel::TableModel(QObject *parent):
    QAbstractTableModel(parent)
{


    for(int j=0;j<35;j++){
        QStringList list;
        list.append(QString::number(j));
        list.append("FK"+QString::number(j));
        list.append("V"+QString::number(j));
        list.append(QString::fromUtf8("修模"));
        list.append(QString::fromUtf8("加工中"));
        list.append(QString::fromUtf8("90%"));
        list.append(QString::fromUtf8("江苏"));
        list.append(QString::fromUtf8("75"));


        m_vData.append(list);
    }
}


int TableModel::columnCount(const QModelIndex &parent) const
{

    return m_vData.at(0).size();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return m_vData.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(Qt::TextAlignmentRole == role)
        return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
    if(Qt::DisplayRole == role)
        return m_vData.value(index.row()).value(index.column());

    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.column() == 5 && role == Qt::EditRole){
        QStringList list = m_vData.at(index.row());
        list.replace(index.column(),value.toString());
        m_vData.replace(index.row(),list);
        emit dataChanged(index,index);
        return true;
    }
    return QAbstractTableModel::setData(index,value,role);
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QStringList list;
    list.append(QString::fromUtf8("序号"));
    list.append(QString::fromUtf8("模具编号"));
    list.append(QString::fromUtf8("版本号"));
    list.append(QString::fromUtf8("类型"));
    list.append(QString::fromUtf8("状态"));
    list.append(QString::fromUtf8("合格率"));
    list.append(QString::fromUtf8("地区"));
    list.append(QString::fromUtf8("进度"));


    if(orientation == Qt::Horizontal)
    {
        switch(role)
        {
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

        case Qt::DisplayRole:
            return list.at(section);
        default:
            return QVariant();
        }
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    return QAbstractTableModel::setHeaderData(section,orientation,value,role);
}


