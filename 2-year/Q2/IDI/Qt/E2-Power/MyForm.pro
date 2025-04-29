TEMPLATE = app
#nom exe
TARGET = MyForm
QT += widgets
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += MyForm.h MyLCD.h
FORMS += Form.ui
SOURCES += main.cpp MyForm.cpp MyLCD.cpp
