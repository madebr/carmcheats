#pragma once

#include <carmhash.h>
#include <carmcheatrawdata.h>

#include <QAbstractTableModel>
#include <QMainWindow>

class QLabel;
class Ui_Carm2PatcherMainWindow;
class CheatPatcherModel;
struct CarmGameCheats;
struct CarmActualHashCodes_t;

struct CarmHashCode_t {
    CarmHashCode_t() = default;
    CarmHashCode_t(CarmCheatVerifyType type_, const c2_hash_t &fileHash_, const c2_hash_t &actualHash_,const c2_hash_t &defaultHash_,
        const char *defaultCheat_, bool modded_)
        : type(type_)
        , fileHash(fileHash_)
        , actualHash(actualHash_)
        , defaultHash(defaultHash_)
        , defaultCheat(defaultCheat_)
        , modded(modded_) {
    }
    CarmCheatVerifyType type;
    int cheatDataIndex{};

    c2_hash_t fileHash;

    QString actualCheat{};
    c2_hash_t actualHash;

    c2_hash_t defaultHash;
    const char *defaultCheat;

    bool modded;
    bool modified = false;

    bool updateCheat(const QString &newCheat);
    void undoChanges();
    void setDefault();
};

struct CarmActualHashCodes_t {
    QVector<CarmHashCode_t> items;
};

class CheatPatcherModel : public QAbstractTableModel {
    Q_OBJECT

    CarmActualHashCodes_t m_actualHashes{};
    const CarmGameCheats *m_cheatData{};
    enum ColumnType {
        COLUMN_HASH,
        COLUMN_CHEAT,
        COLUMN_DESCRIPTION,
        COLUMN_COUNT,
    };
    std::tuple<CarmCheatVerifyType, size_t> modelIndex2Idx(const QModelIndex &index) const;
public:
    void setActualHashes(CarmActualHashCodes_t &&actualHashes, const CarmGameCheats *cheatData);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    const CarmHashCode_t &itemAtIndex(const QModelIndex &) const;
    const CarmHashCode_t &itemAtIndex(int) const;
    CarmHashCode_t &itemAtIndex(const QModelIndex &);

    void itemUndoChanges(QModelIndex &);
    void itemUndoChanges(int);
    void itemSetDefault(QModelIndex &);
    void itemSetDefault(int);
    const CarmActualHashCodes_t &getActualHashes() const { return m_actualHashes; }
    QModelIndex idxToModelIndex(CarmCheatVerifyType idxType, size_t index) const;
    bool anyModified() const;
    bool anyNonDefault() const;
signals:
    void cheatUpdated(QString id, QString cheat);
};

class Carm2PatcherMainWindow : public QMainWindow {
    Q_OBJECT
public:
    Carm2PatcherMainWindow();
    ~Carm2PatcherMainWindow();
    void openExe(const QString &path);
    bool saveExe();
    void closeExe();
    const QString &currentExe() const;
    void closeEvent(QCloseEvent *closeEvent) override;
private:
    bool maybeSave();

    Ui_Carm2PatcherMainWindow *m_ui;
    QLabel *m_statusWidget;
    const CarmGameCheats *m_cheatData{};
    CheatPatcherModel *m_model{};

    QString m_exePath;
};
