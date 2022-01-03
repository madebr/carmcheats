#include "gui_utils.h"

#include "carmhash.h"

#include <QString>

QString
cheat2hashstr_qt(const QString &text) {
    auto bytes = text.toUtf8();
    c2_state_t state;
    c2_hash_t hash;
    hash_reset(&state);
    hash_update(&state, bytes.data());
    hash_digest(&state, &hash);
    return QString{"%1:%2"}
        .arg(static_cast<ulong>(hash.code1), 8, 16, QChar{'0'})
        .arg(static_cast<ulong>(hash.code2), 8, 16, QChar{'0'});
}
