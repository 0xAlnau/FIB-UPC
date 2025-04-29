TEMPLATE = app
#nom exe
TARGET = MyForm
QT += widgets
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += MyForm.h MyLabel.h
FORMS += Form.ui
SOURCES += main.cpp MyForm.cpp MyLabel.cpp
