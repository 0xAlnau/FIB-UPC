TEMPLATE = app
#nom exe
TARGET = MyForm
QT += widgets
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += MyForm.h MyButton.h MyLine.h
FORMS += Form.ui
SOURCES += main.cpp MyForm.cpp MyButton.cpp MyLine.cpp
