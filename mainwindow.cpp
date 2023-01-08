#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->logList->setAutoScroll(true);
    al_n.append("S");
    updateList(ui->nonTermList,al_n);
    al_t.append({"w","r","q"});
    updateList(ui->termList,al_t);
    target="S";
    ui->label_2->setText(target);
    FixedChain=ui->lineEdit_4->text().split("");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //    if(ui->lineEdit->text().isEmpty()){
    //logError("Empty",ui->logList);
    //return;
    //}
    //    if(ui->lineEdit->text().size()>1){
    //logError("Chars only",ui->logList);
    //return;
    //}
    //    if(al_t.contains(ui->lineEdit->text())){
    //logError("Already in aplhabet",ui->logList);
    //return;
    //}
    //    al_t.append(ui->lineEdit->text());
    //    updateList(ui->termList,al_t);
    //    logError("Added to terminal :"+ui->lineEdit->text(),ui->logList);
    if(!ui->lineEdit->text().isLower()&&ui->lineEdit->text()!=" "&&ui->lineEdit->text()!="`"){
        logError("Only lower in terminal:");
        updateList(ui->logList,log);
        return;
    }
    logError("Add to terminal :"+ui->lineEdit->text());
    if(ui->lineEdit->text()==" "){
        listAdd(ui->termList,&al_t,"_");
    }else
        listAdd(ui->termList,&al_t,ui->lineEdit->text());

    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
    updateList(ui->logList,log);

}


void MainWindow::on_pushButton_2_clicked()
{

    //    if(al_t.isEmpty()){
    //        logError("Cant remove in empty list"+ui->lineEdit->text(),ui->logList);
    //        return;
    //    }
    //    if(!al_t.contains(ui->lineEdit->text())){
    //        logError("Not in list:"+ui->lineEdit->text(),ui->logList);
    //        return;
    //    }
    //     logError("Removed :"+ui->lineEdit->text(),ui->logList);
    //     al_t.removeAt(al_t.indexOf(ui->lineEdit->text()));
    //      updateList(ui->termList,al_t);
    listRemove(ui->termList,&al_t,ui->lineEdit->text());
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
    updateList(ui->logList,log);
}








void MainWindow::on_pushButton_7_clicked()

{
    R_mode=ui->radioButton->isChecked();
    qDebug()<<R_mode;
    rules.clear();
    mod=ui->spinModulus->value();
    if(FixedChain.isEmpty()){
        return;}
    if(FixedChain.contains(""))
        FixedChain.removeAll("");

    RuleGen();
    qDebug()<<"RuleGen out";
    qDebug()<<rules;
    updateList(ui->nonTermList,&al_n);
    updateList(ui->rulesList,&rules);
    //  updateList(ui->logList,rules);

}


void MainWindow::on_pushButton_10_clicked()
{
    logError("Gen size"+ui->spinBox->text());
    updateList(ui->logList,log);
    // qDebug()<<ChainGen(rules,target,&result,ui->spinBox->text().toInt());
    ChainGen(rules,target,&result,ui->spinBox->text().toInt());
    updateList(ui->logList,log);
    updateList(ui->listView,result);
}


void MainWindow::on_pushButton_8_clicked()
{   rules.clear();
    updateList(ui->rulesList,rules);
}


void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    FixedChain.clear();
    QStringList temp=arg1.split("");
    for(auto &i:temp){
        if(al_t.contains(i)){
            FixedChain.append(i);
        }
    }
    ui->lineEdit_4->setText(FixedChain.join(""));
}



void MainWindow::on_action_triggered()
{
    QMessageBox msg;
    QString temp="ИП-913 Жиляков Е.А \n Вариант 5";
    temp+="";
    msg.setWindowTitle("Автор");
    msg.setText(temp);
    msg.exec();

}


void MainWindow::on_action_2_triggered()
{
    QMessageBox msg;
    QString temp="Написать программу, которая по предложенному описанию языка построит регулярную грамматику (ЛЛ или ПЛ – по заказу пользователя),задающую этот язык, и позволит сгенерировать с её помощью все цепочки языка в заданном диапазоне длин. Предусмотреть возможностьпоэтапного отображения на экране процесса генерации цепочек. Варианты задания языка:\nАлфавит, обязательная фиксированная подцепочка и кратность длины всех цепочек языка";
    temp+="";
    msg.setWindowTitle("Тема");
    msg.setText(temp);
    msg.exec();
}


void MainWindow::on_action_3_triggered()
{
    QString filename = QFileDialog::getSaveFileName(NULL,NULL,NULL,"*.txt");
    QFile f( filename+"txt");

    f.open( QIODevice::WriteOnly );
    QTextStream out(&f);
    out<<"CFG\n";
    out<<al_n.join(" ");
    out<<"\n";
    out<<FixedChain.join("");
    out<<"\n";
    out<<al_t.join(" ");
    out<<"\n";
    out<<rules.join("\n");
    f.close();
}


void MainWindow::on_action_4_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    QFile f( filename);
    bool check=false;
    int line=0;
     if( f.open( QIODevice::ReadOnly )){
          QTextStream out(&f);
          while(!out.atEnd()){
              QString temp=out.readLine();
              if(!check){
              if(temp=="CFG"){
                  check=true;

              }
              else{
                  QMessageBox msg;
                  msg.setText("WRONG FORMAT!");
                  msg.exec();
                  return;
              }
              }
              if(line<3){
                  line+=3;
                  temp=out.readLine();
                  al_n=temp.split(" ");
                  temp=out.readLine();
                  FixedChain=temp.split("");
                  ui->lineEdit_4->setText(FixedChain.join(""));
                  temp=out.readLine();
                   al_t=temp.split(" ");


              }
              else{
                  rules.append(temp);
                  if(temp.at(3).isUpper()){
                      R_mode=true;
                      ui->radioButton->setChecked(true);

                  }
              }


          }

          updateList(ui->rulesList,&rules);
           updateList(ui->termList,&al_t);
           updateList(ui->nonTermList,&al_n);
     }

}

