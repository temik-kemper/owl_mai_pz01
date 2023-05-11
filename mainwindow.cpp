#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->startTimer(1000);
//=====================Реализация ДСЧ=============================================
    this->serSamples=new QLineSeries;
    this->chartSamples=new QChart;
    this->chartSamples->addSeries(this->serSamples);

    this->InitChart(this->ui->wdRndSamples,this->chartSamples,"Реализация ДСЧ");

    this->serSamples->setColor(QRgb(0xff0000));
    QValueAxis *axisX,*axisY;
    axisX=(QValueAxis *)this->chartSamples->axes(Qt::Horizontal).first();
    axisY=(QValueAxis *)this->chartSamples->axes(Qt::Vertical).first();
    axisX->setRange(0,250);
    axisY->setRange(-5,5);
//=============================Гистограмма=============================================
    this->serGist=new QLineSeries;
    QAreaSeries *serAGist=new QAreaSeries(this->serGist);
    serAGist->setPen(QColor(QRgb(0x0f0000)));
    serAGist->setBrush(QColor(QRgb(0xff0000)));

    this->chartGist=new QChart;
    this->chartGist->addSeries(serAGist);

    this->InitChart(this->ui->wdRndGist,this->chartGist,"Гистограмма ДСЧ");
    axisX=(QValueAxis *)this->chartGist->axes(Qt::Horizontal).first();
    axisY=(QValueAxis *)this->chartGist->axes(Qt::Vertical).first();
    axisX->setRange(-5,5);
    axisY->setRange(0,1);
//==============================Корреляционная Функция=====================================
    this->serCor=new QLineSeries;
    this->chartCor=new QChart;
    this->chartCor->addSeries(this->serCor);

    this->InitChart(this->ui->wdRndCor,this->chartCor,"Корреляционная функция ДСЧ");

    this->serCor->setColor(QRgb(0xff0000));
    axisX=(QValueAxis *)this->chartCor->axes(Qt::Horizontal).first();
    axisY=(QValueAxis *)this->chartCor->axes(Qt::Vertical).first();
    axisX->setRange(0,250);
    axisY->setRange(-5,5);
//===========================Энергетический спектр=========================================
    this->serSpectr=new QLineSeries;
    QAreaSeries *serASpectr=new QAreaSeries(this->serSpectr);
    serASpectr->setPen(QColor(QRgb(0x0f0000)));
    serASpectr->setBrush(QColor(QRgb(0xff0000)));

    this->chartSpectr=new QChart;
    this->chartSpectr->addSeries(serASpectr);

    this->InitChart(this->ui->wdRndSpectr,this->chartSpectr,"Спектр ДСЧ");
    axisX=(QValueAxis *)this->chartSpectr->axes(Qt::Horizontal).first();
    axisY=(QValueAxis *)this->chartSpectr->axes(Qt::Vertical).first();
    axisX->setRange(-5,5);
    axisY->setRange(0,1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    QDateTime now;

    if(this->ui->chBxTimeUTC->isChecked()) now=QDateTime::currentDateTimeUtc();
    else    now=QDateTime::currentDateTime();

    this->ui->lbDate->setText(now.date().toString("dd.MM.yyyy"));
    this->ui->lbTime->setText(now.time().toString());

}//void MainWindow::timerEvent(QTimerEvent *)

void MainWindow::InitChart(QWidget *parent,QChart *chart,QString title,QString y_title,QString x_title)
{
    chart->legend()->hide();
    chart->createDefaultAxes();

    QValueAxis *axisX,*axisY;
    axisX=(QValueAxis*)chart->axes(Qt::Horizontal).first();
    axisY=(QValueAxis*)chart->axes(Qt::Vertical).first();

    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    chart->setTitleBrush(QBrush(QRgb(0x0000ff)));
    chart->setTitleFont(font);
    chart->setTitle(title);

    QPen axisPen(QRgb(0x0000ff));
    axisPen.setWidth(5);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    axisX->setRange(0,1000);
    axisY->setRange(0,500);
    axisX->setTickCount(11);
    axisY->setTickCount(11);

    axisPen.setWidth(1);
    axisPen.setStyle(Qt::DotLine);
    axisPen.setColor(QColor(QRgb(0x0f0f0f)));
    axisX->setGridLinePen(axisPen);
    axisY->setGridLinePen(axisPen);

    QFont labelsFont;
    labelsFont.setPointSize(12);

    axisX->setLabelsFont(labelsFont);
    axisX->setLabelsColor(QRgb(0x0000ff));
    axisX->setTitleText(x_title);
    axisX->setTitleFont(font);
    axisX->setTitleBrush(QBrush(QRgb(0x0000ff)));

    axisY->setLabelsFont(labelsFont);
    axisY->setLabelsColor(QRgb(0x0000ff));
    axisY->setTitleText(y_title);
    axisY->setTitleFont(font);
    axisY->setTitleBrush(QBrush(QRgb(0x0000ff)));

    QChartView *chartView=new QChartView(chart);
    QVBoxLayout *layout=new QVBoxLayout(parent);
    layout->addWidget(chartView);
}//void MainWindow::InitChart(QWidget *parent,QLineSeries *ser,QString title,QString y_title,QString x_title)


void MainWindow::on_btTest01_clicked()
{
    QString str;
    QTextStream out(&str);
    int index;
    double x;

    index=this->ui->cmBxRndSelect->currentIndex();

    for(int i=0;i<SIZE;i++)
    {
        switch(index)
        {
        case 4:
            x=this->rnd.GetCGauss().imag();
            break;
        case 3:
            x=this->rnd.GetCGauss().real();
            break;
        case 2:
            x=this->rnd.GetGauss();
            break;
        case 1:
            x=this->rnd.GetReley();
            break;
        case 0:
        default:
            x=this->rnd.GetRand();
        }//switch(index)

        str.clear();
        out<<x;
        this->ui->txtMain->appendPlainText(str);

    }//for(int i=0;i<SIZE;i++)

    str.clear();
    this->ui->txtMain->appendPlainText(str);

}//void MainWindow::on_btTest01_clicked()

void MainWindow::on_btRndInit_clicked()
{
    this->rnd.Init();
}//void MainWindow::on_btRndInit_clicked()

void MainWindow::on_btTest02_clicked()
{
    QString str;
    QTextStream out(&str);
    int index,size;
    double x,mx,dx;

    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    index=this->ui->cmBxRndSelect->currentIndex();

    size=this->ui->cmBxSize->currentText().toInt();

    mx=dx=0.;
    for(int i=0;i<size;i++)
    {
        switch(index)
        {
        case 4:
            x=this->rnd.GetCGauss().imag();
            break;
        case 3:
            x=this->rnd.GetCGauss().real();
            break;
        case 2:
            x=this->rnd.GetGauss();
            break;
        case 1:
            x=this->rnd.GetReley();
            break;
        case 0:
        default:
            x=this->rnd.GetRand();
        }//switch(index)

        mx+=x;
        dx+=x*x;
    }//for(int i=0;i<size;i++)

    mx/=size;
    dx/=size;
    dx=sqrt(dx-mx*mx);

    str.clear();
    out<<"size="<<size<<" m="<<mx<<" d="<<dx;
    this->ui->txtMain->appendPlainText(str);

    QGuiApplication::restoreOverrideCursor();
}//void MainWindow::on_btTest02_clicked()

void MainWindow::on_btRndSamplesShow_clicked()
{
    int index,size;
    double x;
    QValueAxis *axisX,*axisY;

    axisX=(QValueAxis *)this->chartSamples->axes(Qt::Horizontal).first();
    axisY=(QValueAxis *)this->chartSamples->axes(Qt::Vertical).first();

    index=this->ui->cmBxRndSelect->currentIndex();
    size=this->ui->edRndSamplesSize->text().toInt();

    this->serSamples->clear();

    for(int i=0;i<size;i++)
    {
        switch(index)
        {
        case 4:
            x=this->rnd.GetCGauss().imag();
            break;
        case 3:
            x=this->rnd.GetCGauss().real();
            break;
        case 2:
            x=this->rnd.GetGauss();
            break;
        case 1:
            x=this->rnd.GetReley();
            break;
        case 0:
        default:
            x=this->rnd.GetRand();
        }//switch(index)

        this->serSamples->append(i,x);
    }//for(int i=0;i<size;i++)

    axisX->setRange(0,size);

    switch(index)
    {
    case 4:
    case 3:
    case 2:
        axisY->setRange(-5,5);
        break;
    case 1:
        axisY->setRange(0,5);
        break;
    case 0:
    default:
        axisY->setRange(0,2);
    }//switch(index)

}//void MainWindow::on_btRndSamplesShow_clicked()

void MainWindow::on_btGrSamplesClear_clicked()
{
    this->serSamples->clear();
}//void MainWindow::on_btGrSamplesClear_clicked()

void MainWindow::on_btRndGistShow_clicked()
{
    int index,size,gist_index;
    double x,x0,dx,d;
    unsigned int Gist[GIST_SIZE];
    QValueAxis *axisX,*axisY;

    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    axisX=(QValueAxis *)this->chartGist->axes(Qt::Horizontal).first();
    axisY=(QValueAxis *)this->chartGist->axes(Qt::Vertical).first();

    index=this->ui->cmBxRndSelect->currentIndex();
    size=this->ui->edRndGistSize->text().toInt();
    if(size < 100) {size=100;this->ui->edRndGistSize->setText("100");}

    for(int i=0;i<GIST_SIZE;i++) Gist[i]=0;

    this->serGist->clear();

    switch(index)
    {
    case 4:
    case 3:
    case 2:
        x0=-5;dx=0.5;
        axisX->setRange(-5,5);
        axisY->setRange(0,0.5);
        break;
    case 1:
        x0=0.;dx=0.25;
        axisX->setRange(0,5);
        axisY->setRange(0,1);
        break;
    case 0:
    default:
        x0=0.;dx=0.05;
        axisX->setRange(0,1);
        axisY->setRange(0,2);
    }//switch(index)


    for(int i=0;i<size;i++)
    {
        switch(index)
        {
        case 4:
            x=this->rnd.GetCGauss().imag();
            break;
        case 3:
            x=this->rnd.GetCGauss().real();
            break;
        case 2:
            x=this->rnd.GetGauss();
            break;
        case 1:
            x=this->rnd.GetReley();
            break;
        case 0:
        default:
            x=this->rnd.GetRand();
        }//switch(index)

        gist_index=(x-x0)/dx;
        if(gist_index < 0) gist_index=0;
        if(gist_index >= GIST_SIZE) gist_index=GIST_SIZE-1;

        Gist[gist_index]++;

    }//for(int i=0;i<size;i++)

    x=x0;
    for(int i=0;i<GIST_SIZE;i++)
    {
        d=Gist[i]/(size*dx);

        this->serGist->append(x,0);
        this->serGist->append(x,d);
        x+=dx;
        this->serGist->append(x,d);
        this->serGist->append(x,0);
    }//for(int i=0;i<GIST_SIZE;i++)

    QGuiApplication::restoreOverrideCursor();
}//void MainWindow::on_btRndGistShow_clicked()

void MainWindow::on_btRndGistClear_clicked()
{
    this->serGist->clear();
}//void MainWindow::on_btRndGistClear_clicked()


/*
Лорды, сэры, пэры, знайте чувство меры,
Избегайте пьянства вы, как западни,
Ждет нас путь не близкий и чем крепче виски,
Тем короче, сэры, будут ваши дни.
Каждый лишний градус, будет вам не в радость,
Вашему здоровью вреден каждый тост.
Простите, не цветет, как роза, печень от цирроза?
Да, и от склероза, лишь тупеет мозг.

Пятнадцать человек на сундук мертвеца,
Йо-хо-хо, и бутылка рома,
Пей, и дьявол тебя доведет до конца,
Йо-хо-хо, и бутылка рома,
Пей, и дьявол тебя доведет до конца,
Йо-хо-хо, и бутылка рома.

От похмелья, сэры, будете вы серы,
И не мил вам будет утром белый свет,
Будет враг доволен, ты уже не воин,
Если пляшут в пальцах шпага и мушкет.
Утром встал с постели, лучше взять гантели,
И любая ноша будет вам как пух,
Нету лучше в мире полновесной гири,
И в здоровом теле - здоровее дух.

Пятнадцать человек на сундук мертвеца,
Йо-хо-хо, и бутылка рома,
Пей, и дьявол тебя доведет до конца,
Йо-хо-хо, и бутылка рома,
Пей, и дьявол тебя доведет до конца,
Йо-хо-хо, и бутылка рома.*/
void MainWindow::on_btRndCorShow_clicked(){

    int index, size, size2, wnd_size;
    double x, y, x1, x0, dx, d;
    unsigned int gistSize = 30;
    double Gist[gistSize];

    QValueAxis *axisX,*axisY, *axisX2, *axisY2;
    axisX=(QValueAxis *)this->chartCor->axes(Qt::Horizontal).first();
    axisY=(QValueAxis *)this->chartCor->axes(Qt::Vertical).first();

    axisX2=(QValueAxis *)this->chartSpectr->axes(Qt::Horizontal).first();
    axisY2=(QValueAxis *)this->chartSpectr->axes(Qt::Vertical).first();

    index=this->ui->cmBxRndSelect->currentIndex();
    size=this->ui->edRndCorSize->text().toInt();
    wnd_size=this->ui->edRndWndSize->text().toInt();


    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    this->serCor->clear();

    CVectorDFT corrVec(size);
    CVectorDFT wndVec(2*size-1);
    CVectorDFT wndVec_rev(size);

    int step = (int)size/(wnd_size);

/*
 * 2*size/wnd_size (окргленное вверх)
 * Сумма случайные значение со сдвинутой копией от 0 до n с шагом
 */
    double reley_const = sqrt(M_PI / 2.);

    for(int i=0;i<size;i++)
    {
        switch(index)
        {
        case 4:
            x=this->rnd.GetCGauss().imag();
            break;
        case 3:
            x=this->rnd.GetCGauss().real();
            break;
        case 2:
            x=this->rnd.GetGauss();
            break;
        case 1:
            x=this->rnd.GetReley() - reley_const;
            break;
        case 0:
        default:
            x=this->rnd.GetRand() - 0.5;
        }//switch(index)

        corrVec[i] = x;

    }//for(int i=0;i<size;i++)

    for (int i=0; i < 2*size-1;i++) {
        wndVec[i]=0;
    }//for (int i=0; i < wnd_size;i++)

    for (int i=0;i < size;i++) {

        wndVec_rev[i] = corrVec[size-i];
        //wndVec_rev[size+size-i] = 0;
    }
    for (int i = 0; i < 2*size-1; i+=step)//Сама операция линейной свертки в окне
    {
        for (int j = 0; j < size; j++)
        {
            if (i < j + size)//Данное условие отвечает за правильность получения значений правее нуля
            {
                if( i-j < 0 )
                {//Данное условие отвечает за правильность получения значений левее нуля
                    wndVec[i] += 0. * wndVec[j];//По условию алгоритма если i-j<0, то массив с их разностью зануляется
                 }else
                 {
                    wndVec[i] += corrVec[i - j] * wndVec_rev[j];
                 }
             }
         }
    }

    double max = wndVec[0].real();

    for(unsigned int i = 0; i < wndVec.GetSize(); i++)
    {
        if (max < wndVec[i].real()) max = wndVec[i].real();
    }//for(unsigned int i = 0; i < corrVec.GetSize(); i++)


    for(int i=0; i < 2*size-1; i+=step)
    {
        y = wndVec[i].real() / max;
        //y = (wndVec[(i + wndVec.GetSize() / 2) % wndVec.GetSize()].real()) / max;
        this->serCor->append(i - ((2*size-1) / 2), y);
    }//for(unsigned int i = 0; i < corrVec.GetSize(); i++)

    //*
    

    std::vector<std::complex<double> > tmpVec;
    
    for(int i = 0; i < 2*size-1; i+=step)
    {
        tmpVec.push_back(wndVec[i]);
    }

    corrVec.SetSize(tmpVec.size());
    for(int i = 0; i < tmpVec.size(); i++)
    {
        corrVec[i] = tmpVec[i];
    }

    corrVec = corrVec.DFT();

    complex gistArr[corrVec.GetSize()];

    for(unsigned int i = 0; i < corrVec.GetSize(); i++)
    {
        corrVec[i] *= std::conj(corrVec[i]);

        gistArr[i] = corrVec[i];
    }

    size2=corrVec.GetSize();

    //===========================================
    for(unsigned int i=0;i<gistSize;i++) Gist[i] = 0.;

    this->serSpectr->clear();

    switch(index) //for gist
    {
    case 4:
    case 3:
    case 2:
        x0=0;dx=1;
        axisX2->setRange(0,size2);
        axisY2->setRange(0,1);
        break;
    case 1:
        x0=0.;dx=1;
        axisX2->setRange(0,size2);
        axisY2->setRange(0,1);
        break;
    case 0:
    default:
        x0=0.;dx=1;
        axisX2->setRange(0,size2);
        axisY2->setRange(0,1);
    }//switch(index)

    for(int i=0;i<size2;i++)
    {
        Gist[i * gistSize / size2] += std::abs(gistArr[i]);
    }//for(int i=0;i<size;i++)

    double max2 = Gist[0];

    for(unsigned int i=0;i<gistSize;i++)
    {
        if (max2 < Gist[i]) max2 = Gist[i];
    }//for(unsigned int i=0;i<gistSize;i++)

    x1=x0;

    for(unsigned int i=0;i<gistSize;i++)
    {

        d = Gist[i] / max2;
        this->serSpectr->append(x1,0);
        this->serSpectr->append(x1,d);
        x1+=dx * size2 / gistSize;
        this->serSpectr->append(x1,d);
        this->serSpectr->append(x1,0);

    }//for(int i=0;i<GIST_SIZE;i++)
    //============================================

    // corrVec = corrVec.IDFT();

    // double max3 = corrVec[0].real();

    // for(unsigned int i = 0; i < corrVec.GetSize(); i++)
    // {
    //     if (max3 < corrVec[i].real()) max3 = corrVec[i].real();
    // }//for(unsigned int i = 0; i < corrVec.GetSize(); i++)

    // for(unsigned int i = 0; i < corrVec.GetSize(); i++)
    // {
    //     y = (corrVec[(i + corrVec.GetSize() / 2) % corrVec.GetSize()].real()) / max3;
    //     this->serCor->append(i, y);
    // }//for(unsigned int i = 0; i < corrVec.GetSize(); i++)
    //*/

    QGuiApplication::restoreOverrideCursor();

    //axisX->setRange(-0.5*wnd_size,0.5*wnd_size);
    // axisX->setRange(0,size);
    axisX->setRange(-1 * size, size);


    switch(index)
    {
    case 4:
    case 3:
    case 2:
        axisY->setRange(-0.2,1);
        break;
    case 1:
        axisY->setRange(-0.2,1);
        break;
    case 0:
    default:
        axisY->setRange(-0.2,1);
    }//switch(index)

}//void MainWindow::on_btRndCorShow_clicked()

/*
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⠞⣋⠉⣿⣯⣿⢿⣖⠦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠿⣶⣾⣿⣾⣿⣹⣿⣶⣿⣿⣾⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣧⣰⣿⣿⣿⣿⣿⣿⡿⠿⠿⣿⣿⡟⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠟⣠⣿⠟⠋⠉⠀⠈⠀⠀⠀⠀⠘⣿⣧⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⠀⠀⠀⢀⡀⠀⠀⣀⡀⠀⣾⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⡏⠀⢻⣯⡽⢿⡄⠘⢿⡯⠵⢻⣟⡋⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠼⣧⠀⠉⠀⠀⠀⠁⠀⠀⠀⠀⢨⣿⢳⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢌⢧⣬⠇⠀⠀⠀⠸⠛⠂⠘⠆⢎⡴⣻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠉⣿⡆⠀⠀⢾⣯⢿⣗⣀⣼⣹⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠸⡟⠀⠀⠀⠟⢲⣶⠶⣿⠍⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⠰⡇⠀⠀⠀⠴⢺⣿⣤⢿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣾⣿⣿⣿⡆⢧⡀⠀⢀⣀⣼⣿⣟⡇⢿⣷⣶⣤⣄⣀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⣀⣴⣶⣿⣿⣿⣿⣿⣿⣿⣷⠀⠳⣄⠀⠉⢿⣿⣿⠇⠸⣿⣿⣿⣿⣿⣿⣷⣦⣄⡀⠀
⠀⢀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⠆⠙⢦⣀⣨⠗⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀
⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣀⣠⣤⣀⣉⠀⠀⡀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆
⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢁⣼⠿⢿⣿⣿⣿⠲⠶⠶⠯⢤⣠⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇
⠀⡿⣿⣿⣿⣿⣿⣿⣿⡟⣰⢹⣁⡀⠈⠙⣻⣿⣍⣉⣙⣒⣻⠓⢾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏
⠀⣷⣾⣿⣿⣿⣿⣿⣿⠁⡇⠀⠉⡀⠙⢿⣿⣿⡧⠤⠤⠭⠭⣌⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇
⢀⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁⠀⠀⣇⣤⣾⣿⣿⣗⠒⠒⠲⣶⠦⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇*/

void MainWindow::on_btRndCorClear_clicked(){
    this->serCor->clear();
    this->serSpectr->clear();
}//void MainWindow::on_btRndCorClear_clicked()


