#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include<QStandardItemModel>
#include<QVector>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

 public:
    TableModel(QObject *parent = 0);
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);
   // Qt::ItemFlags TableModel::flags(const QModelIndex &index) const;
private:
     QVector<QStringList> m_vData;


};




#endif // TABLEMODEL_H
