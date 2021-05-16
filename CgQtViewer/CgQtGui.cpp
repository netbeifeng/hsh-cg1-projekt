
#include "../CgEvents/CgColorChangeEvent.h"
#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgUnterteilungsEvent.h"
#include "../CgEvents/CgRotateEvent.h"
#include "../CgEvents/CgTrackballEvent.h"
#include "../CgEvents/CgLoadObjFileEvent.h"
#include "../CgEvents/CgTrackballEvent.h"
#include "../CgEvents/CgVerschiebungsEvent.h"
#include "../CgEvents/CgSpecialEvent.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QActionGroup>
#include <QFileDialog>
#include <QLineEdit>
#include <iostream>



CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;

    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));
    connect(m_glRenderWidget, SIGNAL(trackballChanged()), this, SLOT(slotTrackballChanged()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;


    QWidget *opt = new QWidget;
    createOptionPanelExample1(opt);

    QWidget *otheropt = new QWidget;
    createOptionPanelExample2(otheropt);

    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(opt,"&Aufgabe 1/2");
    m_tabs->addTab(otheropt,"&Aufgabe 3/4");
    container->addWidget(m_tabs);

    m_tabs->setMaximumWidth(400);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2020"));


    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File" );
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    QMenu *settings_menu = new QMenu("&Setting" );
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode" );

    QAction* m_custom_rot=settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction* m_lighting=settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);


    QActionGroup* polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction* points=polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);


    QAction* wireframe=polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction* filled=polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);



    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);



    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    m_menuBar->addMenu( settings_menu );
    m_menuBar->addMenu( polygon_mode_menu );


    m_mainWindow->setMenuBar(m_menuBar);

}

QSlider *CgQtGui::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}






void CgQtGui::createOptionPanelExample1(QWidget* parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();
    QHBoxLayout *r_control = new QHBoxLayout();
    QHBoxLayout *g_control = new QHBoxLayout();
    QHBoxLayout *b_control = new QHBoxLayout();
    /*Example forusing a label */

    QLabel *options_label = new QLabel("Color:");
    tab1_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignTop);

    QLabel *label_r = new QLabel("R:");
    r_control->addWidget(label_r);
    label_r->setAlignment(Qt::AlignLeft);

    input_r = new QSpinBox();
    input_r->setValue(0);
    input_r->setRange(0,256);
    r_control->addWidget(input_r);
    connect(input_r, SIGNAL( valueChanged(int) ), this, SLOT(colorChanged()) );

    QLabel *label_g = new QLabel("G:");
    g_control->addWidget(label_g);
    label_g->setAlignment(Qt::AlignLeft);

    input_g = new QSpinBox();
    input_g->setValue(0);
    input_g->setRange(0,256);
    g_control->addWidget(input_g);
    connect(input_g, SIGNAL( valueChanged(int) ), this, SLOT(colorChanged()) );

    QLabel *label_b = new QLabel("B:");
    b_control->addWidget(label_b);
    label_b->setAlignment(Qt::AlignLeft);

    input_b = new QSpinBox();
    input_b->setValue(0);
    input_b->setRange(0,256);
    b_control->addWidget(input_b);
    connect(input_b, SIGNAL( valueChanged(int) ), this, SLOT(colorChanged()) );

    tab1_control->addLayout(r_control);
    tab1_control->addLayout(g_control);
    tab1_control->addLayout(b_control);


    QPushButton* drawButton = new QPushButton("&Draw Normalen Von Cube");
    tab1_control->addWidget(drawButton);
    connect(drawButton, SIGNAL( clicked() ), this, SLOT(normalenErzeugen()) );

    QPushButton* showCurve = new QPushButton("&Display Kurve");
    tab1_control->addWidget(showCurve);
    connect(showCurve, SIGNAL( clicked() ), this, SLOT(showKurve()) );
    //   // mySpinBox1->setSuffix("   suffix");
//   // mySpinBox1->setPrefix("Prefix:  ");

    /*Example for using a button */
    QHBoxLayout *mittelungsLayout = new QHBoxLayout();

    QLabel *mittelungsSchritte_label = new QLabel("Mittelungsschritte:");
    tab1_control->addWidget(mittelungsSchritte_label);
    mittelungsSchritte_label->setAlignment(Qt::AlignLeft);

//    QHBoxLayout *drawNormale_Layout = new QHBoxLayout();
//    QLabel *drawNormale_label = new QLabel("Normalen erzeugen");
//    tab1_control->addWidget(drawNormale_label);
//    drawNormale_label->setAlignment(Qt::AlignLeft);



    mittelungsSchritte = new QSpinBox();
    mittelungsSchritte->setRange(1,9);
    mittelungsLayout->addWidget(mittelungsSchritte);

    enableResetMode = new QCheckBox("reset Curve");
    enableResetMode->setCheckable(true);
    enableResetMode->setChecked(false);
    mittelungsLayout->addWidget(enableResetMode);

    QPushButton* myButton1 = new QPushButton("&Unterteilen");
    mittelungsLayout->addWidget(myButton1);
    connect(myButton1, SIGNAL( clicked() ), this, SLOT(unterteilung()) );

    tab1_control->addLayout(mittelungsLayout);

    QHBoxLayout *rotationsLayout = new QHBoxLayout();

    QLabel *rotation_label = new QLabel("Kurve Rotation:");
    tab1_control->addWidget(rotation_label);
    rotation_label->setAlignment(Qt::AlignLeft);

    rotationsGrad = new QSpinBox();
    rotationsGrad->setRange(1,999);
    rotationsLayout->addWidget(rotationsGrad);

    QPushButton* rotationsButton = new QPushButton("&Rotate");
    rotationsLayout->addWidget(rotationsButton);
    connect(rotationsButton, SIGNAL( clicked() ),this,SLOT(rotate()) );

    tab1_control->addLayout(rotationsLayout);

    parent->setLayout(tab1_control);

}

void CgQtGui::createOptionPanelExample2(QWidget* parent)
{


    QVBoxLayout *tab2_control = new QVBoxLayout();
//    QHBoxLayout *subBox = new QHBoxLayout();

    QPushButton* showSceneGraph = new QPushButton("&Display SceneGraph");
    tab2_control->addWidget(showSceneGraph);
    connect(showSceneGraph, SIGNAL( clicked() ), this, SLOT(showSceneGraph()) );

    /*Example for using a button group */

//    QGroupBox* myGroupBox = new QGroupBox("Radiobutton Group Example ");

//    myButtonGroup = new QButtonGroup(subBox);
//    myButtonGroup->setExclusive(true);

//    QRadioButton* radiobutton1 = new QRadioButton( "&Option1");
//    QRadioButton* radiobutton2 = new QRadioButton( "&Option2");
//    QRadioButton* radiobutton3 = new QRadioButton( "&Option3");
//    QRadioButton* radiobutton4 = new QRadioButton( "&Option4");
//    QRadioButton* radiobutton5 = new QRadioButton( "&Option5");

//    radiobutton2->setChecked(true);

//    myButtonGroup->addButton(radiobutton1,0);
//    myButtonGroup->addButton(radiobutton2,1);
//    myButtonGroup->addButton(radiobutton3,2);
//    myButtonGroup->addButton(radiobutton4,3);
//    myButtonGroup->addButton(radiobutton5,4);


//    QVBoxLayout *vbox = new QVBoxLayout;
//    vbox->addWidget(radiobutton1);
//    vbox->addWidget(radiobutton2);
//    vbox->addWidget(radiobutton3);
//    vbox->addWidget(radiobutton4);
//    vbox->addWidget(radiobutton5);
//    vbox->addStretch(1);
//    myGroupBox->setLayout(vbox);
//    subBox->addWidget(myGroupBox);
//    tab2_control->addLayout(subBox);

    QHBoxLayout *dx_control = new QHBoxLayout();
    QHBoxLayout *dy_control = new QHBoxLayout();
    QHBoxLayout *dz_control = new QHBoxLayout();

    QLabel *verschiebung_label = new QLabel("Verschiebung:");
    tab2_control->addWidget(verschiebung_label);
    verschiebung_label->setAlignment(Qt::AlignTop);

    QLabel *label_dx = new QLabel("dx:");
    dx_control->addWidget(label_dx);
    label_dx->setAlignment(Qt::AlignLeft);

    input_dx = new QLineEdit();
    dx_control->addWidget(input_dx);
    connect(input_dx, SIGNAL( textChanged(QString) ), this, SLOT(translationChanged()) );

    QLabel *label_dy = new QLabel("dy:");
    dy_control->addWidget(label_dy);
    label_dy->setAlignment(Qt::AlignLeft);

    input_dy = new QLineEdit();
    dy_control->addWidget(input_dy);
    connect(input_dy, SIGNAL( textChanged(QString) ), this, SLOT(translationChanged()) );

    QLabel *label_dz = new QLabel("dz:");
    dz_control->addWidget(label_dz);
    label_dz->setAlignment(Qt::AlignLeft);

    input_dz = new QLineEdit();
    dz_control->addWidget(input_dz);
    connect(input_dz, SIGNAL( textChanged(QString) ), this, SLOT(translationChanged()) );

    tab2_control->addLayout(dx_control);
    tab2_control->addLayout(dy_control);
    tab2_control->addLayout(dz_control);

//    connect(myButtonGroup, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );
    parent->setLayout(tab2_control);

}



void CgQtGui::slotButtonGroupSelectionChanged()
{

}

void CgQtGui::slotMySpinBox1Changed()
{
    std::cout << "change pressed " << std::endl;
}

void CgQtGui::slotMyCheckBox1Changed()
{

}


//void CgQtGui::slotLoadMeshFile()
//{
//    std::cout << "load Mesh file callback reached, but not implemented..." << std::endl;
//    // Hier FileChooser öffnen, datei selektieren
//    QString fileName = QFileDialog::getOpenFileName(this,
//                                                    tr("Open a file"),
//                                                    "",
//                                                    tr("All files(*.*)"));
//    std::cout << fileName.toStdString() << std::endl;
//    // und dann neuen Event implementieren, der das an den Controller schickt.
//    // dort wird dann die Datei tatsächliche geöffnet und ein entsprechendes Mesh Objekt angelegt
//    // im View(GUI) passiert nichts außer festellung DASS geladen werden soll und welche Datei und zu welchem Zweck (Mesh)
//}



void CgQtGui::translationChanged()
{
    float dx =this->input_dx->text().toFloat();
    float dy =this->input_dy->text().toFloat();
    float dz =this->input_dz->text().toFloat();

    CgBaseEvent* e = new CgVerschiebungsEvent(Cg::CgVerschiebungsEvent,dx,dy,dz);
    notifyObserver(e);
}

void CgQtGui::normalenErzeugen()
{
    CgBaseEvent* e = new CgSpecialEvent(Cg::CgSpecialEvent,1);
    notifyObserver(e);
}

void CgQtGui::showKurve()
{
    CgBaseEvent* e = new CgSpecialEvent(Cg::CgSpecialEvent,2);
    notifyObserver(e);
}


void CgQtGui::showSceneGraph()
{
    CgBaseEvent* e = new CgSpecialEvent(Cg::CgSpecialEvent,3);
    notifyObserver(e);
}


void CgQtGui::colorChanged()
{
   int r = this->input_r->text().toInt();
   int g = this->input_g->text().toInt();
   int b = this->input_b->text().toInt();

//   m_glRenderWidget->setColor(r,g,b);
   CgBaseEvent* e = new CgColorChangeEvent(Cg::CgColorChangeEvent,r,g,b);
   notifyObserver(e);
}

void CgQtGui::mouseEvent(QMouseEvent* event)
{

   // std::cout << QApplication::keyboardModifiers() << std::endl;

  //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;


   if(event->type()==QEvent::MouseButtonPress)
   {


        CgBaseEvent* e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x() ,event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
   }

   if(event->type()==QEvent::MouseMove)
   {
       CgBaseEvent* e= new CgMouseEvent(Cg::CgMouseMove,
                                        glm::vec2(event->localPos().x() ,event->localPos().y()),
                                        (Cg::MouseButtons)event->button());
       notifyObserver(e);
   }



}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
   CgBaseEvent* e= new CgKeyEvent(Cg::CgKeyPressEvent,(Cg::Key)event->key(),(Cg::KeyboardModifiers)event->nativeModifiers(),event->text().toStdString());
   notifyObserver(e);
}

void CgQtGui::slotTrackballChanged()
{
    CgBaseEvent* e = new CgTrackballEvent(Cg::CgTrackballEvent, m_glRenderWidget->getTrackballRotation());
    notifyObserver(e);
}

void CgQtGui::viewportChanged(int w, int h)
{
     CgBaseEvent* e = new CgWindowResizeEvent(Cg::WindowResizeEvent,w,h);
     notifyObserver(e);
}

CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}


void CgQtGui::slotLoadMeshFile()
{



   QString file=  QFileDialog::getOpenFileName(this, tr("Open Obj-File"),"",tr("Model Files (*.obj)"));


    CgBaseEvent* e = new CgLoadObjFileEvent(Cg::LoadObjFileEvent, file.toStdString());

    notifyObserver(e);
}


void CgQtGui::unterteilung()
{
    if(this->enableResetMode->checkState()) {
        CgBaseEvent* e = new CgUnterteilungsEvent(Cg::CgUnterteilungsEvent,1,2);
        notifyObserver(e);
    } else {
//        std::cout << this->mittelungsSchritte->value() << std::endl;
        int mittel = this->mittelungsSchritte->value();
        CgBaseEvent* e = new CgUnterteilungsEvent(Cg::CgUnterteilungsEvent,mittel,1);
        notifyObserver(e);
    }
    m_glRenderWidget->update();
}

void CgQtGui::rotate()
{
    int grad = this->rotationsGrad->value();
    CgBaseEvent* e = new CgRotateEvent(Cg::CgRotateEvent,grad);
    notifyObserver(e);
    m_glRenderWidget->update();
}


