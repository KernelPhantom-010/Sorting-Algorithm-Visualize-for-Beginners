 #include <windows.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <string>
#include <QGraphicsTextItem>
#include <QTimeLine>
#include <QPropertyAnimation>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <vector>
#include <QGraphicsItemAnimation>
QString globalSet;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}
/*Quick Sort- Logic*/
int findCenter_qSortLogic(std::vector<int>& array, int start, int end, QPlainTextEdit* interface_select)
{
    int pivot = array[end];
    int center = start - 1;

    for(int i = start; i < end; i++)
    {
        if(array[i] <= pivot)
        {
            center++;
            std::swap(array[center], array[i]);
        }
    }
    std::swap(array[center + 1], array[end]);

    interface_select->appendPlainText(QString("[i] Pivot %1 sorted to position %2").arg(pivot).arg(center + 1));

    return center + 1;
}

void q_sortLogic(std::vector<int>& array, int start, int end, QPlainTextEdit* interface_select)
{
    if(start < end)
    {
        int center_item = findCenter_qSortLogic(array, start, end, interface_select);

        q_sortLogic(array, start, center_item - 1, interface_select);
        q_sortLogic(array, center_item + 1, end, interface_select);
    }
}

void quick_sort(QPlainTextEdit* interface_select, std::vector<int> intervall)
{
    interface_select->clear();
    interface_select->appendPlainText("[+] Iteration started..\n");

    q_sortLogic(intervall, 0, intervall.size() - 1, interface_select);

    QString result = "[+] Fully Sorted: ";
    for(int val : intervall)
        result += QString::number(val) + " ";
    interface_select->appendPlainText("\n" + result);
}
/*-----------------------------------------------------------------------*/

/*Insertion-Sort Logic*/
void insertion_sort(QPlainTextEdit* interface_select, std::vector<int> intervall)
{
    interface_select->clear();
    interface_select->appendPlainText("[+] Iteration started..\n");
    for (size_t i = 0; i < intervall.size() - 1; i++)
    {
        int temp_int = intervall[i + 1];
        int j = i + 1;

        while (j > 0 && intervall[j - 1] > temp_int)
        {
            int unsorted = intervall[j];
            intervall[j] = intervall[j - 1];
            interface_select->appendPlainText("[PROGRESS] Set " + QString::number(unsorted) + " ↔️ " + QString::number(intervall[j]) + "..\n");
            j--;
        }

        intervall[j] = temp_int;

        QCoreApplication::processEvents();
    }
    std::string final = "\n[+] Sorted array -> { " + std::to_string(intervall[0]) + ", " +  std::to_string(intervall[1]) + ", " + std::to_string(intervall[2]) + ", " + std::to_string(intervall[3]) + " }\n";
    interface_select->appendPlainText(QString::fromStdString(final));

}
/*-----------------------------------------------------------------------*/

/*Selection-Sort Logic*/

void selection_sort(QPlainTextEdit* interface_select, std::vector<int> intervall)
{
    interface_select->clear();
    interface_select->appendPlainText("[+] Iteration started..\n");
    for (int outer = 0; outer < (intervall.size() - 1); ++outer)
    {
        bool swapped = false;
        int min_temp = intervall[outer];
        int index_old = outer;
        for (int j = outer + 1; j < intervall.size(); j++)
        {
            if (intervall[j] < min_temp)
            {
                int temp_min_space = min_temp;


                min_temp = intervall[j];
                interface_select->appendPlainText("[PROGRESS] New minimum found " + QString::number(temp_min_space) + " ↔️ " + QString::number(min_temp) + "..\n");
                index_old = j;
                swapped = true;
            }
        }
        int temp_swap = intervall[outer];
        intervall[outer] = min_temp;
        intervall[index_old] = temp_swap;
        if (!swapped) break;
        QCoreApplication::processEvents();
    }
    std::string final = "\n[+] Sorted array -> { " + std::to_string(intervall[0]) + ", " +  std::to_string(intervall[1]) + ", " + std::to_string(intervall[2]) + ", " + std::to_string(intervall[3]) + " }\n";
    interface_select->appendPlainText(QString::fromStdString(final));
}


/*Bubble-Sort Logic*/


void bubble_sort(QPlainTextEdit *interface_select, std::vector<int> intervall)
{
    interface_select->clear();
    interface_select->appendPlainText("[+] Iteration started..\n");
    for (int outer = 0; outer < intervall.size(); ++outer)
    {
        bool swapped = false;
        for (int j = 0; j < (intervall.size() - 1); ++j)
        {
            if (intervall[j] > intervall[j + 1])
            {
                int temp_var = intervall[j];
                interface_select->appendPlainText("[PROGRESS] Swapping " + QString::number(temp_var) + " ↔️ " + QString::number(intervall[j + 1]) + "..\n");
                intervall[j] = intervall[j + 1];
                intervall[j + 1] = temp_var;
                interface_select->appendPlainText("[PROGRESS] Iteration " + QString::number(outer + 1) + " -> { " + QString::number(intervall[0]) + ", " +  QString::number(intervall[1]) + ", " + QString::number(intervall[2]) + ", " + QString::number(intervall[3]) + " }\n");
                swapped = true;
            }
        }
        if (!swapped) break;
        QCoreApplication::processEvents();
    }
    std::string final = "\n[+] Sorted array -> { " + std::to_string(intervall[0]) + ", " +  std::to_string(intervall[1]) + ", " + std::to_string(intervall[2]) + ", " + std::to_string(intervall[3]) + " }\n";
    interface_select->appendPlainText(QString::fromStdString(final));
}



void MainWindow::on_pushButton_clicked()
{
    std::vector<QString> arrayFull;
    arrayFull.push_back(ui->lineEdit->text());
    arrayFull.push_back(ui->lineEdit_2->text());
    arrayFull.push_back(ui->lineEdit_3->text());
    arrayFull.push_back(ui->lineEdit_6->text());

    BOOL oneIsEmpty = FALSE;

    for (QString currentIndex : arrayFull){
        if (currentIndex.isEmpty())
        {
            oneIsEmpty = TRUE;
            break;
        }
    }
    QListWidgetItem* checkForNULL = ui->listWidget->currentItem();
    if (checkForNULL == nullptr)
    {
        MessageBoxA(NULL, "Please select an sorting algorithm and fill in the\ncustom vector to generate!", "Common Failure", NULL);
        return;
    }
    if ( oneIsEmpty == TRUE)
    {
        MessageBoxA(NULL, "Please select an sorting algorithm and fill in the\ncustom vector to generate!", "Common Failure", NULL);
        return;
    }

    for (int init = 0; init < 360; ++init)
    {
        double current_angle = init * M_PI /180;

        double x_coord = 410 + 100 * std::cos(current_angle);
        double y_coord = 300 + 100 * std::sin(current_angle);


    }
    int liste[] = {5, 2, 12 , 4};
    int num1, num2, num3, num4;
    QByteArray num1_c, num2_c, num3_c, num4_c;

    num1_c = ui->lineEdit->text().toUtf8();
    num2_c = ui->lineEdit_2->text().toUtf8();
    num3_c = ui->lineEdit_3->text().toUtf8();
    num4_c = ui->lineEdit_6->text().toUtf8();

    std::string num1_f = num1_c.data();
    std::string num2_f = num2_c.data();
    std::string num3_f = num3_c.data();
    std::string num4_f = num4_c.data();


    num1 = std::stoi(num1_f);
    num2 = std::stoi(num2_f);
    num3 = std::stoi(num3_f);
    num4 = std::stoi(num4_f);

    std::vector<int> vector_entries;
    vector_entries.push_back(num4);
    vector_entries.push_back(num1);
    vector_entries.push_back(num2);
    vector_entries.push_back(num3);
    QList<QListWidgetItem*> selected = ui->listWidget->selectedItems();
    ui->plainTextEdit->setStyleSheet("color: red");
    for (QListWidgetItem* item : selected)
    {
        if (item->text() == "Bubble Sort")
        {
            ui->plainTextEdit->clear();
            std::string startingText = "[+] Starting Bubble Sort for { " + std::to_string(num4) + ", " + std::to_string(num1) + ", " + std::to_string(num2) + ", " + std::to_string(num3) + " }\n";
            ui->plainTextEdit->appendPlainText(QString::fromStdString(startingText));
            bubble_sort(ui->plainTextEdit, vector_entries);
        }
        else if (item->text() == "Selection Sort")
        {
            ui->plainTextEdit->clear();
            std::string startingText = "[+] Starting Selection Sort for { " + std::to_string(num4) + ", " + std::to_string(num1) + ", " + std::to_string(num2) + ", " + std::to_string(num3) + " }\n";
            ui->plainTextEdit->appendPlainText(QString::fromStdString(startingText));
            selection_sort(ui->plainTextEdit, vector_entries);
        }
        else if (item->text() == "Insertion Sort")
        {
            ui->plainTextEdit->clear();
            std::string startingText = "[+] Starting Insertion Sort for { " + std::to_string(num4) + ", " + std::to_string(num1) + ", " + std::to_string(num2) + ", " + std::to_string(num3) + " }\n";
            ui->plainTextEdit->appendPlainText(QString::fromStdString(startingText));
            insertion_sort(ui->plainTextEdit, vector_entries);
        }
        else if (item->text() == "Quick Sort")
        {
            ui->plainTextEdit->clear();
            std::string startingText = "[+] Starting Quick Sort for { " + std::to_string(num4) + ", " + std::to_string(num1) + ", " + std::to_string(num2) + ", " + std::to_string(num3) + " }\n";
            ui->plainTextEdit->appendPlainText(QString::fromStdString(startingText));
            quick_sort(ui->plainTextEdit, vector_entries);
        }
    }

}

