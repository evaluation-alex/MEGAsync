#include "GuestWidget.h"
#include "ui_GuestWidget.h"
#include "megaapi.h"
#include "MegaApplication.h"

using namespace mega;

GuestWidget::GuestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuestWidget)
{
    ui->setupUi(this);

    app = (MegaApplication *)qApp;

    connect(ui->lDescLogin, SIGNAL(linkActivated(QString)), this, SLOT(on_descLogin_linkActivated(QString)));

    ui->lDescLogin->setText(QString::fromUtf8("<p style=\" line-height: 140%;\"><span style=\"font-size:13px;\">")
                               + ui->lDescLogin->text().replace(QString::fromUtf8("[A]"), QString::fromUtf8("<a href=\"#setup_login\" style=\"text-decoration:none;\"><font color=\"#d90007\"> "))
                                                       .replace(QString::fromUtf8("[/A]"), QString::fromUtf8(" </font></a>"))
                                                       .replace(QString::fromUtf8("[B]"), QString::fromUtf8("<a href=\"#setup_account\" style=\"text-decoration:none;\"><font color=\"#d90007\"> "))
                                                       .replace(QString::fromUtf8("[/B]"), QString::fromUtf8(" </font></a>"))
                                                                   + QString::fromUtf8("</span></p>"));

}

GuestWidget::~GuestWidget()
{
    delete ui;
}

void GuestWidget::on_bLogin_clicked()
{
    emit actionButtonClicked(LOGIN_CLICKED);
}

void GuestWidget::on_bCreateAccount_clicked()
{
    emit actionButtonClicked(CREATE_ACCOUNT_CLICKED);
}

void GuestWidget::on_bSettings_clicked()
{
    QPoint p = ui->bSettings->mapToGlobal(QPoint(ui->bSettings->width() - 2, ui->bSettings->height()));

#ifdef __APPLE__
    QPointer<GuestWidget> iod = this;
#endif

    app->showTrayMenu(&p);

#ifdef __APPLE__
    if (!iod)
    {
        return;
    }

    if (!this->rect().contains(this->mapFromGlobal(QCursor::pos())))
    {
        this->hide();
    }
#endif
}

void GuestWidget::on_descLogin_linkActivated(const QString &link)
{
    if (link == QString::fromUtf8("#setup_account"))
    {
        on_bCreateAccount_clicked();
    }
    else if (link == QString::fromUtf8("#setup_login"))
    {
        emit actionButtonClicked(LOGIN_CLICKED);
    }
}
