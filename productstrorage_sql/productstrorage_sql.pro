QT       += core gui
QT       += axcontainer
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_product.cpp \
    earnings.cpp \
    inventory.cpp \
    main.cpp \
    profile.cpp \
    sqltablewidget.cpp \
    widget.cpp

HEADERS += \
    add_product.h \
    earnings.h \
    inventory.h \
    profile.h \
    sqltablewidget.h \
    widget.h

include(product_sale/saleProduct.pri)
include(product_strorage/product_strorage.pri)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
