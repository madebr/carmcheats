#include "carm2cheatpatchergui.h"

#include "ui_carm2cheatpatchergui.h"

#include <carmcheatrawdata.h>
#include <carm2cheatrawdata.h>
#include <carmhash.h>

#include <QCloseEvent>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QItemSelectionModel>

static c2_hash_t
calculateHash(const char *cheat) {
    c2_state_t state;
    c2_hash_t hash;
    hash_reset(&state);
    hash_update(&state, cheat);
    hash_digest(&state, &hash);
    return hash;
}

static c2_hash_t
calculateHash(const QString &cheat) {
    auto stdString = cheat.toStdString();
    return calculateHash(stdString.data());
}

bool
CarmHashCode_t::updateCheat(const QString &newCheat) {
    bool cheatChanged = actualCheat != newCheat;
    actualCheat = newCheat;
    c2_hash_t newHash = calculateHash(newCheat);
    modified = (newHash.code1 != fileHash.code1) || (newHash.code2 != fileHash.code2);
    modded = (newHash.code1 != defaultHash.code1) || (newHash.code2 != defaultHash.code2);
    cheatChanged = cheatChanged || (newHash.code1 != actualHash.code1) || (newHash.code2 != actualHash.code2);
    actualHash = newHash;
    return cheatChanged;
}

void
CarmHashCode_t::undoChanges() {
    actualHash = fileHash;
    actualCheat = "";
    modified = false;
    modded = !((actualHash.code1 == defaultHash.code1) && (actualHash.code2 == defaultHash.code2));
    if (!modded) {
        actualCheat = defaultCheat;
    }
}

void
CarmHashCode_t::setDefault() {
    updateCheat(defaultCheat);
}

static void
collect_data_callback(CarmCheatVerifyResult* result, void *userData) {
    bool hashDiffers = (result->type & CARM_CHEAT_VERIFY_RESULT_HASH_DIFFERS) != 0;
    CarmActualHashCodes_t *actualHashes = static_cast<CarmActualHashCodes_t *>(userData);
    const char *defaultCheat;
    c2_hash_t defaultHash;
    const char *actualCheat = nullptr;
    int actualIndex;
    switch(result->cheatType) {
    case CARM_CHEAT_VERIFY_FRAGMENT: {
        actualIndex = result->index;
        defaultCheat = result->cheatData->fragments[result->index].cheat;
        defaultHash = calculateHash(defaultCheat);
        if (!hashDiffers) {
            actualCheat = defaultCheat;
        }
        break;
    case CARM_CHEAT_VERIFY_TABLE_ITEM: {
        actualIndex = result->cheatData->nbFragments + result->index;
        defaultCheat = result->cheatData->table->items[result->index].cheat;
        defaultHash = calculateHash(defaultCheat);
        if (!hashDiffers) {
            actualCheat = defaultCheat;
        }
        break;
    }
    }
    default:
        return;
    }
    actualHashes->items[actualIndex] = {result->cheatType, result->hash, result->hash, defaultHash, defaultCheat, hashDiffers};
    actualHashes->items[actualIndex].cheatDataIndex = result->index;
    if (actualCheat != nullptr) {
        actualHashes->items[actualIndex].actualCheat = actualCheat;
    }
}

std::tuple<CarmCheatVerifyType, size_t>
CheatPatcherModel::modelIndex2Idx(const QModelIndex &index) const {
    return {m_actualHashes.items[index.row()].type, index.row()};
}

void
CheatPatcherModel::setActualHashes(CarmActualHashCodes_t &&actualHashes, const CarmGameCheats *cheatData) {
    beginResetModel();
    m_cheatData = cheatData;
    m_actualHashes = std::move(actualHashes);
    endResetModel();
}

int
CheatPatcherModel::rowCount(const QModelIndex &) const {
    return (m_actualHashes.items.size());
}

int
CheatPatcherModel::columnCount(const QModelIndex &) const {
    return COLUMN_COUNT;
}

static QString
idxTypeIndexToString(CarmCheatVerifyType idxType, size_t idx) {
    char c;
    if (idxType == CARM_CHEAT_VERIFY_TABLE_ITEM) {
        c = 'T';
    } else {
        c = 'F';
    }
    return QString("%1%2").arg(c).arg(idx);
}

QVariant
CheatPatcherModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (role) {
    case Qt::DisplayRole:
        switch (orientation) {
        case Qt::Horizontal:
            switch (section) {
            case COLUMN_HASH:
                return tr("hash");
            case COLUMN_CHEAT:
                return tr("cheat");
            case COLUMN_DESCRIPTION:
                return tr("description");
            }
            break;
        case Qt::Vertical: {
            const CarmHashCode_t &item = itemAtIndex(section);
            return idxTypeIndexToString(item.type, item.cheatDataIndex);
        }
        }
        break;
    default:
        break;
    }
    return {};
}

QVariant
CheatPatcherModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return {};
    }
    const CarmHashCode_t &item = itemAtIndex(index);
    switch (role) {
    case Qt::FontRole: {
        QFont font;
        switch (index.column()) {
        case COLUMN_HASH:
            font.setFamily("Courier");
        }
        if (m_actualHashes.items[index.row()].modded) {
            font.setItalic(true);
        }
        if (m_actualHashes.items[index.row()].modified) {
            font.setWeight(QFont::Bold);
        }
        return font;
    }
    case Qt::DisplayRole:
        switch (index.column()) {
        case COLUMN_DESCRIPTION:
            switch (item.type) {
            case CARM_CHEAT_VERIFY_TABLE_ITEM:
                return m_cheatData->table->items[item.cheatDataIndex].description;
            case CARM_CHEAT_VERIFY_FRAGMENT:
                return m_cheatData->fragments[item.cheatDataIndex].description;
            }
            break;
        case COLUMN_CHEAT:
            if (m_actualHashes.items[index.row()].actualCheat.length() > 0) {
                return m_actualHashes.items[index.row()].actualCheat;
            } else if (m_actualHashes.items[index.row()].modded) {
                return tr("(unknown)");
            } else {
                return m_cheatData->table->items[index.row()].cheat;
            }
            break;
        case COLUMN_HASH:
            return QString{"%1:%2"}
                .arg(m_actualHashes.items[index.row()].actualHash.code1, 8, 16, QChar{'0'})
                .arg(m_actualHashes.items[index.row()].actualHash.code2, 8, 16, QChar{'0'});
            break;
        }
        break;
    case Qt::EditRole:
        switch (index.column()) {
        case COLUMN_CHEAT:
            if (m_actualHashes.items[index.row()].actualCheat.length() > 0) {
                return m_actualHashes.items[index.row()].actualCheat;
            } else if (m_actualHashes.items[index.row()].modded) {
                return {};
            } else {
                return m_cheatData->table->items[index.row()].cheat;
            }
        }
    }
    return {};
}

bool
CheatPatcherModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) {
        return false;
    }
    const CarmHashCode_t &item = itemAtIndex(index);
    switch (role) {
    case Qt::EditRole:
        switch (index.column()) {
        case COLUMN_CHEAT: {
            auto newCheat = value.toString();
            if (newCheat.length() == 0) {
                break;
            }
            bool cheatChanged = false;
            cheatChanged = m_actualHashes.items[index.row()].updateCheat(newCheat);
            if (cheatChanged) {
                emit cheatUpdated(idxTypeIndexToString(item.type, item.cheatDataIndex), newCheat);
            }
            emit dataChanged(index, index, {Qt::DisplayRole, Qt::FontRole});
            emit dataChanged(createIndex(index.row(), COLUMN_CHEAT), createIndex(index.row(), COLUMN_CHEAT), {Qt::DisplayRole});
            return true;
        }
        }
    }
    return false;
}

Qt::ItemFlags
CheatPatcherModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.isValid()) {
        switch (index.column()) {
        case COLUMN_CHEAT:
            flags |= Qt::ItemIsEditable;
        }
    }
    return flags;
}

const CarmHashCode_t &
CheatPatcherModel::itemAtIndex(const QModelIndex &index) const {
    if (!index.isValid()) {
        return m_actualHashes.items[0];
    }
    return m_actualHashes.items[index.row()];
}

const CarmHashCode_t &
CheatPatcherModel::itemAtIndex(int i) const {
    return itemAtIndex(createIndex(i, 0));
}

CarmHashCode_t &
CheatPatcherModel::itemAtIndex(const QModelIndex &index) {
    if (!index.isValid()) {
        return m_actualHashes.items[0];
    }
    return m_actualHashes.items[index.row()];
}

void
CheatPatcherModel::itemUndoChanges(QModelIndex &index) {
    auto &item = itemAtIndex(index);
    item.undoChanges();
    emit dataChanged(createIndex(index.row(), 0), createIndex(index.row(), COLUMN_COUNT-1), {Qt::DisplayRole, Qt::FontRole});
}

void
CheatPatcherModel::itemUndoChanges(int i) {
    auto index = createIndex(i, 0);
    itemUndoChanges(index);
}

void
CheatPatcherModel::itemSetDefault(QModelIndex &index) {
    auto &item = itemAtIndex(index);
    item.setDefault();
    emit dataChanged(createIndex(index.row(), 0), createIndex(index.row(), COLUMN_COUNT-1), {Qt::DisplayRole, Qt::FontRole});
}

void
CheatPatcherModel::itemSetDefault(int i) {
    auto index = createIndex(i, 0);
    itemSetDefault(index);
}


bool CheatPatcherModel::anyModified() const {
    bool anyModified = false;
    for (int i = 0; i < m_actualHashes.items.size(); i += 1) {
        anyModified = anyModified || m_actualHashes.items[i].modified;
    }
    return anyModified;
}

bool CheatPatcherModel::anyNonDefault() const {
    bool anyNonDefault = false;
    for (int i = 0; i < m_actualHashes.items.size(); i += 1) {
        anyNonDefault = anyNonDefault || m_actualHashes.items[i].modded;
    }
    return anyNonDefault;
}

Carm2PatcherMainWindow::Carm2PatcherMainWindow() {
    m_ui = new Ui_Carm2PatcherMainWindow;
    m_ui->setupUi(this);

    m_model = new CheatPatcherModel;
    m_ui->centralTable->setModel(m_model);

    connect(m_model, &QAbstractItemModel::modelReset,
        this, [=]() {
            const auto &actualHash = m_model->itemAtIndex(m_ui->centralTable->selectionModel()->currentIndex());
            m_ui->undoItemAction->setEnabled(actualHash.modified);
            m_ui->resetItemAction->setEnabled(actualHash.modded);
            m_ui->resetAllAction->setEnabled(m_model->anyNonDefault());
            m_ui->undoAllAction->setEnabled(m_model->anyModified());
            m_ui->saveAction->setEnabled(m_model->anyModified());
        });
    connect(m_model, &QAbstractItemModel::dataChanged,
        this, [=](const auto &) {
            const auto &actualHash = m_model->itemAtIndex(m_ui->centralTable->selectionModel()->currentIndex());
            m_ui->undoItemAction->setEnabled(actualHash.modified);
            m_ui->resetItemAction->setEnabled(actualHash.modded);
            m_ui->resetAllAction->setEnabled(m_model->anyNonDefault());
            m_ui->undoAllAction->setEnabled(m_model->anyModified());
            m_ui->saveAction->setEnabled(m_model->anyModified());
        });
    connect(m_model, &CheatPatcherModel::cheatUpdated,
        m_ui->statusBar, [=](QString id, QString cheat) {
            m_ui->statusBar->showMessage(tr("%1 cheat changed to %2").arg(id).arg(cheat));
        });
    connect(m_ui->centralTable->selectionModel(), &QItemSelectionModel::currentChanged,
        this, [=](const auto &index) {
            const auto &item = m_model->itemAtIndex(index);
            m_ui->resetItemAction->setEnabled(item.modded);
            m_ui->undoItemAction->setEnabled(item.modified);
        });
    m_ui->centralTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_statusWidget = new QLabel;
    m_ui->statusBar->addPermanentWidget(m_statusWidget);

    connect(m_ui->openAction, &QAction::triggered,
        this, [=]() {
            QString exePath = QFileDialog::getOpenFileName(this, tr("Select CARMA2_HW.EXE"), {}, tr("Executables (*.exe *.EXE);;All files (* *.*)"));
            openExe(exePath);
        });
    connect(m_ui->saveAction, &QAction::triggered,
        this, [=]() {
            saveExe();
        });
    connect(m_ui->quitAction, &QAction::triggered,
        QApplication::instance(), &QCoreApplication::quit, Qt::QueuedConnection);

    connect(m_ui->undoItemAction, &QAction::triggered,
        this, [=]() {
            QModelIndex index = m_ui->centralTable->selectionModel()->currentIndex();
            m_model->itemUndoChanges(index);
        });
    connect(m_ui->undoAllAction, &QAction::triggered,
        this, [=]() {
            const auto &actualHashes = m_model->getActualHashes();
            for (int i = 0; i < actualHashes.items.size(); i += 1) {
                m_model->itemUndoChanges(i);
            }
        });
    connect(m_ui->resetItemAction, &QAction::triggered,
        this, [=]() {
            QModelIndex index = m_ui->centralTable->selectionModel()->currentIndex();
            m_model->itemSetDefault(index);
        });
    connect(m_ui->resetAllAction, &QAction::triggered,
        this, [=]() {
            const auto &actualHashes = m_model->getActualHashes();
            for (int i = 0; i < actualHashes.items.size(); i += 1) {
                m_model->itemSetDefault(i);
            }
        });

    connect(m_ui->aboutQtAction, &QAction::triggered,
        QApplication::instance(), &QApplication::aboutQt);
    connect(m_ui->aboutAction, &QAction::triggered,
        QApplication::instance(), [=](){
            QMessageBox::about(this,
                tr("About Carmageddon Cheat Patcher"),
                tr("A Carmageddon cheat patcher brought to you by Maarten."));
        });
}

Carm2PatcherMainWindow::~Carm2PatcherMainWindow() {
    delete m_ui;
}

void
Carm2PatcherMainWindow::openExe(const QString &exePath) {
    if (exePath.length() == 0) {
        return;
    }
    auto stdExePath = exePath.toStdString();
    FILE *f = fopen(stdExePath.data(), "rb");
    if (f == NULL) {
        QMessageBox::warning(this, tr("Could not open"),
            exePath + tr(" could not be opened."));
        return;
    }

    closeExe();

    const CarmGameCheats *cheatData = carm2_game_cheats();

    CarmActualHashCodes_t actualHashes;
    actualHashes.items.resize(cheatData->table->nbItems + cheatData->nbFragments);
    int fileMatches = carm_list_cheats(f, cheatData, collect_data_callback, &actualHashes);
    fclose(f);
    if (fileMatches != 0) {
        QMessageBox::warning(this, tr("File is not Carmageddon 2"),
            tr("%1 could not be identified as Carmageddon II.").arg(exePath));
        return;
    }
    m_cheatData = cheatData;
    m_exePath = exePath;
    m_statusWidget->setText(exePath);
    m_model->setActualHashes(std::move(actualHashes), cheatData);
}

void Carm2PatcherMainWindow::closeExe() {
    m_cheatData = nullptr;
    m_statusWidget->setText(tr("No file loaded"));
}

bool Carm2PatcherMainWindow::saveExe() {
    size_t nbModified = 0;
    const auto &actualHashes = m_model->getActualHashes();
    for (int i = 0; i < actualHashes.items.size(); i += 1) {
        if (actualHashes.items[i].modified) {
            nbModified += 1;
        }
    }

    auto stdExePath = m_exePath.toStdString();
    FILE *f = fopen(stdExePath.data(), "r+");
    if (f == NULL) {
        QMessageBox::warning(this, tr("Save failed"),
            tr("Could not open %1 in read/update mode.").arg(m_exePath));
        return false;
    }

    auto *modifiers = alloc_CarmModifersType(nbModified);
    size_t idx = 0;
    for (size_t i = 0; i < m_cheatData->nbFragments; i += 1) {
        if (actualHashes.items[i].modified) {
            modifiers->items[idx].type = CARM_CHEAT_VERIFY_FRAGMENT;
            modifiers->items[idx].index = i;
            auto stdString = actualHashes.items[i].actualCheat.toStdString();
            modifiers->items[idx].cheat = ::strdup(stdString.data());
            idx += 1;
        }
    }
    for (size_t i = 0; i < m_cheatData->table->nbItems; i += 1) {
        int actualIndex = i + m_cheatData->nbFragments;
        if (actualHashes.items[actualIndex].modified) {
            modifiers->items[idx].type = CARM_CHEAT_VERIFY_TABLE_ITEM;
            modifiers->items[idx].index = i;
            auto stdString = actualHashes.items[actualIndex].actualCheat.toStdString();
            modifiers->items[idx].cheat = ::strdup(stdString.data());
            idx += 1;
        }
    }
    carm_patch_executable(f, modifiers, m_cheatData);
    fclose(f);
    free_CarmModifersType(modifiers);

    openExe(m_exePath);
    return true;
}

const QString &Carm2PatcherMainWindow::currentExe() const {
    return m_exePath;
}

void
Carm2PatcherMainWindow::closeEvent(QCloseEvent *closeEvent) {
    if (!maybeSave()) {
        closeEvent->ignore();
    }
}

bool
Carm2PatcherMainWindow::maybeSave() {
    if (m_model->anyModified()) {
        auto standardButton = QMessageBox::question(this,
            tr("Unsaved changes"),
            tr("Do you want to save the changes?"),
            QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard);
        switch (standardButton) {
        case QMessageBox::Save:
            return saveExe();
        case QMessageBox::Discard:
            return true;
        case QMessageBox::Cancel:
            return false;
        default:
            break;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto mainWindow = new Carm2PatcherMainWindow;
    if (argc >= 2) {
        mainWindow->openExe(argv[1]);
    }
    mainWindow->show();

    return app.exec();
}


