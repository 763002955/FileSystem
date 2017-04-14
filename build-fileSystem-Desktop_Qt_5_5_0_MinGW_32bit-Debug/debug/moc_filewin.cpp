/****************************************************************************
** Meta object code from reading C++ file 'filewin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fileSystem/filewin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filewin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_fileWin_t {
    QByteArrayData data[21];
    char stringdata0[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fileWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fileWin_t qt_meta_stringdata_fileWin = {
    {
QT_MOC_LITERAL(0, 0, 7), // "fileWin"
QT_MOC_LITERAL(1, 8, 41), // "on_tableWidget_customContextM..."
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 3), // "pos"
QT_MOC_LITERAL(4, 55, 11), // "create_file"
QT_MOC_LITERAL(5, 67, 13), // "create_folder"
QT_MOC_LITERAL(6, 81, 11), // "rename_file"
QT_MOC_LITERAL(7, 93, 9), // "open_file"
QT_MOC_LITERAL(8, 103, 11), // "delete_file"
QT_MOC_LITERAL(9, 115, 10), // "paste_file"
QT_MOC_LITERAL(10, 126, 8), // "cut_file"
QT_MOC_LITERAL(11, 135, 9), // "copy_file"
QT_MOC_LITERAL(12, 145, 31), // "on_treeWidget_itemDoubleClicked"
QT_MOC_LITERAL(13, 177, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(14, 194, 4), // "item"
QT_MOC_LITERAL(15, 199, 6), // "column"
QT_MOC_LITERAL(16, 206, 28), // "on_tableWidget_doubleClicked"
QT_MOC_LITERAL(17, 235, 5), // "index"
QT_MOC_LITERAL(18, 241, 21), // "on_goToDirect_clicked"
QT_MOC_LITERAL(19, 263, 21), // "on_backDirect_clicked"
QT_MOC_LITERAL(20, 285, 21) // "on_pushButton_clicked"

    },
    "fileWin\0on_tableWidget_customContextMenuRequested\0"
    "\0pos\0create_file\0create_folder\0"
    "rename_file\0open_file\0delete_file\0"
    "paste_file\0cut_file\0copy_file\0"
    "on_treeWidget_itemDoubleClicked\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_tableWidget_doubleClicked\0index\0"
    "on_goToDirect_clicked\0on_backDirect_clicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fileWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       4,    0,   87,    2, 0x08 /* Private */,
       5,    0,   88,    2, 0x08 /* Private */,
       6,    0,   89,    2, 0x08 /* Private */,
       7,    0,   90,    2, 0x08 /* Private */,
       8,    0,   91,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    2,   95,    2, 0x08 /* Private */,
      16,    1,  100,    2, 0x08 /* Private */,
      18,    0,  103,    2, 0x08 /* Private */,
      19,    0,  104,    2, 0x08 /* Private */,
      20,    0,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::QModelIndex,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void fileWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fileWin *_t = static_cast<fileWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_tableWidget_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->create_file(); break;
        case 2: _t->create_folder(); break;
        case 3: _t->rename_file(); break;
        case 4: _t->open_file(); break;
        case 5: _t->delete_file(); break;
        case 6: _t->paste_file(); break;
        case 7: _t->cut_file(); break;
        case 8: _t->copy_file(); break;
        case 9: _t->on_treeWidget_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->on_tableWidget_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->on_goToDirect_clicked(); break;
        case 12: _t->on_backDirect_clicked(); break;
        case 13: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject fileWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fileWin.data,
      qt_meta_data_fileWin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *fileWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fileWin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_fileWin.stringdata0))
        return static_cast<void*>(const_cast< fileWin*>(this));
    return QWidget::qt_metacast(_clname);
}

int fileWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
