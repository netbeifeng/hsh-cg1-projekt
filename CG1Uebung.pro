QT       += core gui opengl widgets

TEMPLATE = app

TARGET = CgViewer

SOURCES += main.cpp \
    CgQtViewer/CGQtGLRenderWidget.cpp \
    CgQtViewer/CgQtGui.cpp \
    CgBase/CgObservable.cpp \
    CgEvents/CgMouseEvent.cpp \
    CgQtViewer/CgQtMainApplication.cpp \
    CgSceneGraph/CgSceneControl.cpp \
    CgEvents/CgKeyEvent.cpp \
    CgSceneGraph/CgExampleTriangle.cpp \
    CgQtViewer/CgQtGlBufferObject.cpp \
    CgQtViewer/CgTrackball.cpp \
    CgEvents/CgWindowResizeEvent.cpp \
    CgEvents/CgLoadObjFileEvent.cpp \
    CgUtils/ObjLoader.cpp \
    CgEvents/CgTrackballEvent.cpp \
    CgEvents/CgUnterteilungsEvent.cpp \
    CgEvents/CgRotateEvent.cpp \
    CgEvents/CgColorChangeEvent.cpp \
    CgSceneGraph/CgPolyline.cpp \
    CgSceneGraph/CgCube.cpp \
    CgSceneGraph/CgMesh.cpp \
    CgSceneGraph/CgAppearance.cpp \
    CgSceneGraph/CgScenegarphEnity.cpp \
    CgSceneGraph/CgScenegraph.cpp \
    CgEvents/CgVerschiebungsEvent.cpp \
    CgEvents/CgSpecialEvent.cpp \
    CgSceneGraph/CgRotationObject.cpp \
    CgSceneGraph/CgRotationMitVierObject.cpp



HEADERS += \
    CgQtViewer/CgQtGLRenderWidget.h \
    CgQtViewer/CgQtGui.h \
    CgBase/CgObserver.h \
    CgBase/CgObservable.h \
    CgBase/CgBaseEvent.h \
    CgBase/CgEnums.h \
    CgEvents/CgMouseEvent.h \
    CgQtViewer/CgQtMainApplication.h \
    CgSceneGraph/CgSceneControl.h \
    CgEvents/CgKeyEvent.h \
    CgBase/CgBaseRenderer.h \
    CgBase/CgBaseRenderableObject.h \
    CgSceneGraph/CgExampleTriangle.h \
    CgBase/CgBasePointCloud.h \
    CgBase/CgBaseTriangleMesh.h \
    CgBase/CgBasePolygonMesh.h \
    CgBase/CgBasePolyline.h \
    CgBase/CgBaseSceneControl.h \
    CgQtViewer/CgQtGlBufferObject.h \
    CgQtViewer/CgTrackball.h \
    CgEvents/CgWindowResizeEvent.h \
    CgEvents/CgLoadObjFileEvent.h \
    CgUtils/ObjLoader.h \
    CgBase/CgBaseImage.h \
    CgEvents/CgTrackballEvent.h \
    CgEvents/CgUnterteilungsEvent.h \
    CgEvents/CgRotateEvent.h \
    CgEvents/CgColorChangeEvent.h \
    CgSceneGraph/CgPolyline.h \
    CgSceneGraph/CgCube.h \
    CgSceneGraph/CgRotationObject.h \
    CgSceneGraph/CgMesh.h \
    CgSceneGraph/CgScenegraphEnity.h \
    CgSceneGraph/CgAppearance.h \
    CgSceneGraph/CgScenegraph.h \
    CgEvents/CgVerschiebungsEvent.h \
    CgEvents/CgSpecialEvent.h \
    CgSceneGraph/CgRotationMitVierObject.h

