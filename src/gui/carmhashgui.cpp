#include "carmhashgui.h"

#include "ui_carmhashgui.h"
#include "gui_utils.h"
#include <QClipboard>
#include <QMenu>

static void
fixupString(QString &string) {
    int getPos = 0;
    int putPos = 0;
    while (getPos <= string.length()) {
        QChar c = string[getPos];
        if (((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')))) {
            string[putPos] = string[getPos];
            putPos += 1;
        }
        getPos += 1;
    }
    string.resize(putPos);
}

CarmHashMainWindow::CarmHashMainWindow() {
    m_ui = new Ui_CarmHashMainWindow;
    m_ui->setupUi(this);

    connect(m_ui->addButton, &QPushButton::clicked,
        this, [=]() {
            auto cheat = m_ui->inputEdit->text();
            addCheatToHistory(cheat);
            m_ui->inputEdit->clear();
            m_ui->inputEdit->setFocus();
        });
    connect(m_ui->clearButton, &QPushButton::clicked,
        this, [=]() {
            m_ui->inputEdit->clear();
            m_ui->history->clear();
            m_ui->inputEdit->setFocus();
        });
    connect(m_ui->inputEdit, &QLineEdit::textChanged,
        this, [=](auto text) {
            int size = text.size();
            fixupString(text);
            if (text.size() != size) {
                m_ui->inputEdit->setText(text);
                return;
            }
            m_ui->inputHashLabel->setText(cheat2hashstr_qt(text));
        });
    connect(m_ui->inputEdit, &QLineEdit::returnPressed,
        this, [=]() {
            auto cheat = m_ui->inputEdit->text();
            addCheatToHistory(m_ui->inputEdit->text());
            m_ui->inputEdit->clear();
        });
    connect(m_ui->history, &QWidget::customContextMenuRequested,
        this, [=](const auto &pos) {
            QMenu menu(this);
            auto copyAct = new QAction{tr("Copy")};
            connect(copyAct, &QAction::triggered,
                this, [=]() {
                    auto selectedIndexes = m_ui->history->selectionModel()->selectedIndexes();
                    QString str = m_ui->history->item(selectedIndexes[0].row())->data(Qt::DisplayRole).toString();
                    for (int i = 1; i < selectedIndexes.size(); i += 1) {
                        str += "\n";
                        str += m_ui->history->item(selectedIndexes[i].row())->data(Qt::DisplayRole).toString();
                    }
                    auto *clipboard = QApplication::clipboard();
                    clipboard->setText(str);
                });
            if (!m_ui->history->selectionModel()->hasSelection()) {
                copyAct->setEnabled(false);
            }
            menu.addAction(copyAct);
            menu.exec(m_ui->history->viewport()->mapToGlobal(pos));
        });
    emit m_ui->inputEdit->textChanged("");
}

CarmHashMainWindow::~CarmHashMainWindow() {
    delete m_ui;
}

void
CarmHashMainWindow::addCheatToHistory(const QString &cheat) {
    auto hash = cheat2hashstr_qt(cheat);
    m_ui->history->addItem(QString{"%1:%2"}.arg(hash, cheat));
    m_ui->history->scrollToBottom();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto mainWindow = new CarmHashMainWindow;
    mainWindow->show();

    return app.exec();
}
