#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qstringlistmodel.h"
#include <QMainWindow>
#include <QListView>
#include <QMessageBox>
#include <QColumnView>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

private:
    void listRemove(QAbstractItemView * target,QStringList *lst,QString str){
        if(str==" "){
            str="_";
        }
        if(lst->isEmpty()){
            logError("Cant remove in empty list"+str);
            return;
        }
        if(!lst->contains(str)){
            logError("Not in list:"+str);
            return;
        }
         logError("Removed :"+str);
         lst->removeAt(lst->indexOf(str));
          updateList(target,*lst);
    }
    void listAdd(QAbstractItemView * target,QStringList *lst,QString str,bool singleChar=1){
        if(str.isEmpty()){
    logError("Empty");
    return;
    }
        if(str.size()>1&&singleChar){
    logError("Chars only");
    return;
    }
        if(lst->contains(str)){
    logError("Already in aplhabet");
    return;
    }
         lst->append(str);
         logError("Done!");
          updateList(target,*lst);
    }
    void updateList(QAbstractItemView * target,QStringList *lst){
        if(lst->isEmpty()){
    logError("Empty");
    return;}

         logError("Done!");
          updateList(target,*lst);
    }
    QStringList al_t;
    QStringList al_n;
    QString target;
    QStringList rules;
    QStringList result;
    QStringList log;
    Ui::MainWindow *ui;
    QStringList FixedChain;
    qint8 mod;
    void logError(QString str,QListView * target=nullptr){

        QString temp=QString(QString::number(log.size()+1)+"-"+str);
           log.append(temp);
           if(target!=nullptr){
              QStringListModel *model=new QStringListModel(this);
                model->setStringList(log);
                target->setModel(model);}

    }
    void updateList(QAbstractItemView * target,QStringList lst){
        QStringListModel *model=new QStringListModel(this);
          model->setStringList(lst);

          target->setModel(model);
          target->scrollToBottom();


    }

    QString ChainGen(QStringList rules,QString startChar,QStringList *result,int size=2){
    //  QString Chain=rules.join(",");
        result->clear();
        QString chain;
        QString logChain;
        int count=0;
        qDebug()<<FixedChain.size();
        count+=FixedChain.size();
      while(count<=size){
          count+=FixedChain.size();
      for(auto &i:rules){
          for(auto &j:i){
              if(j.isLower()){
              chain.append(j);
              }else if(j!='|'&&j!='`'&&j!='_'){
                  logChain.append(j);
              }
          }
           logChain.append(" ");
      }
     // qDebug()<<Chain;
      if(chain.size()<=size){
      result->append(chain);
      log.append(logChain);
      }
      }
       qDebug()<<count;
     // qDebug()<<Chain;

       result->removeDuplicates();
         return "";
    }
    QStringList ChainList(QStringList rules,QString sChar){
        QStringList tempLst;
        QString tempStr;
        for(auto &i:rules){
            if(i.at(0)==sChar){
                tempStr=i;
                break;
            }
        }
        if(tempStr.isEmpty()){
            return {""};
        }
        tempLst=tempStr.remove(0,3).split('|');

       return {tempLst};
    }
    QStringList RuleGen(){
        al_n.clear();
        al_n.append(target);
        if(mod==0){
            return {};
        }
        qDebug()<<FixedChain;
        int size;
        size=(FixedChain.size()*mod);


        for(int i=1;i<size;i++){
            char c=char('A' + rand() % 26);
            while(al_n.contains(QChar(c))){
               c=char('A' + rand() % 26);
            }

          al_n.append(QChar(c));
        }

        QStringList tempRule;
        QString tempString;
        tempString=target+"->"+FixedChain.at(0)+al_n.at(1)+"|_`";
        tempRule.append(tempString);
        for(int i=1;i<al_n.size();i++){
            if((i+1)==al_n.size()){
                tempString=al_n.at(i)+"->"+FixedChain.at(i%FixedChain.size())+target;
                tempRule.append(tempString);
            }
            else{
            tempString=al_n.at(i)+"->"+FixedChain.at(i%FixedChain.size())+al_n.at(i+1);
            tempRule.append(tempString);
        }}



      rules.append(tempRule);
qDebug()<<rules;
    }

};

#endif // MAINWINDOW_H
