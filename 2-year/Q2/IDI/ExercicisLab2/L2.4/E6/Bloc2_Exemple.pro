TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += ../Model

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h MyLabel.h

SOURCES += main.cpp MyForm.cpp MyLabel.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp
SOURCES += ../Model/model.cpp
