#define GLM_ENABLE_EXPERIMENTAL
#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgColorChangeEvent.h"
#include "CgEvents/CgUnterteilungsEvent.h"
#include "CgEvents/CgRotateEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgVerschiebungsEvent.h"
#include "CgEvents/CgSpecialEvent.h"
#include "CgUtils/ObjLoader.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgExampleTriangle.h"
#include "CgPolyline.h"
#include "CgCube.h"
#include "CgMesh.h"
#include "CgRotationObject.h"
#include "CgRotationMitVierObject.h"
#include "CgScenegraph.h"
#include "CgScenegraphEnity.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

CgSceneControl::CgSceneControl()
{
    m_triangle=NULL;
    m_mesh=NULL;
    m_scenegraph = NULL;
    m_cube = NULL;
     m_current_transformation=glm::mat4(1.);
      m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
     m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
   m_trackball_rotation=glm::mat4(1.);

//   m_cube = new CgCube(99);

   m_mesh=new CgMesh(1998);

   m_rotationObject = NULL;
   m_rotationMitVierObject = NULL;
   m_color = glm::vec4(0.0,1.0,0.0,1.0);
   mv_matrix = m_lookAt_matrix * m_trackball_rotation* m_current_transformation;
//    createCurve();
//    createSceneGraph();
//    m_rotationMitVierObject = new CgRotationMitVierObject(1132,m_kurve,4);
//    m_rotationMitVierObject->printAll();
//    m_rotationObject = new CgRotationObject(1154,m_kurve,4);
}


CgSceneControl::~CgSceneControl()
{
    if(m_triangle!=NULL)
        delete m_triangle;

    delete m_mesh;
   delete  m_cube;
   delete m_kurve;
   delete m_rotationObject;
    delete m_rotationMitVierObject;
   m_polylines.clear();
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer=r;
    m_renderer->setSceneControl(this);

//    if(m_triangle!=NULL)
//        m_renderer->init(m_triangle);

    if(m_mesh!=NULL)
       m_renderer->init(m_mesh);

    for(CgPolyline* pl : m_polylines) {
        //std::cout << "---" << std::endl;
        m_renderer->init(pl);
    }
    if(m_kurve!=NULL)
        m_renderer->init(m_kurve);
    if(m_cube!=NULL)
        m_renderer->init(m_cube);
    if(m_rotationObject!=NULL)
        m_renderer->init(m_rotationObject);
    if(m_rotationMitVierObject!=NULL)
        m_renderer->init(m_rotationMitVierObject);
//    m_renderer->init(m_triangle);

}


void CgSceneControl::renderObjects()
{

    // Materialeigenschaften setzen
    // sollte ja eigentlich pro Objekt unterschiedlich sein können, naja bekommen sie schon hin....

    m_renderer->setUniformValue("mycolor",m_color);

    m_renderer->setUniformValue("matDiffuseColor",glm::vec4(0.35,0.31,0.09,1.0));
    m_renderer->setUniformValue("lightDiffuseColor",glm::vec4(1.0,1.0,1.0,1.0));


    m_renderer->setUniformValue("matAmbientColor",glm::vec4(0.25,0.22,0.06,1.0));
    m_renderer->setUniformValue("lightAmbientColor",glm::vec4(1.0,1.0,1.0,1.0));


    m_renderer->setUniformValue("matSpecularColor",glm::vec4(0.8,0.72,0.21,1.0));
    m_renderer->setUniformValue("lightSpecularColor",glm::vec4(1.0,1.0,1.0,1.0));

    mv_matrix = m_lookAt_matrix * m_trackball_rotation* m_current_transformation ;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
    m_renderer->setUniformValue("normalMatrix",normal_matrix);

//    if(m_triangle!=NULL)
//        m_renderer->render(m_triangle);
    if(m_mesh!=NULL) {
        m_renderer->setUniformValue("mycolor",glm::vec4(0.3,0.1,0.9,1));
        m_renderer->render(m_mesh);
    }
    if(m_kurve!=NULL){
        m_renderer->setUniformValue("mycolor",glm::vec4(m_kurve->getColor(),1));
        m_renderer->render(m_kurve);
    }
    m_renderer->setUniformValue("mycolor",m_color);
    if(m_cube!=NULL)
        m_renderer->render(m_cube);
    if(m_rotationObject!=NULL){
        m_renderer->setUniformValue("mycolor",glm::vec4(0.5,0.1,0.3,1));
        m_renderer->render(m_rotationObject);
    }
    m_renderer->setUniformValue("mycolor",m_color);
    if(m_rotationMitVierObject!=NULL) {
        m_renderer->render(m_rotationMitVierObject);
    }
//    std::cout << "WWWWWWWWWWWWWW!" << std::endl;
    if(m_scenegraph!=NULL)
        m_scenegraph->render(m_renderer,mv_matrix,m_color);
    if(m_polylines.size()>0)
    for(CgPolyline* pl : m_polylines) {
//        std::cout << pl->getColor().x << " " << pl->getColor().y << " " <<pl->getColor().z << std::endl;
        m_renderer->setUniformValue("mycolor",glm::vec4(pl->getColor(),1));
        m_renderer->render(pl);
    }
}

void CgSceneControl::createSceneGraph() {
    createCurve();
    m_cube = new CgCube(99);

    CgAppearance* appearance = new CgAppearance(glm::vec3(1,1,1),glm::vec3(1,1,1));
    std::vector<CgBaseRenderableObject*> list_of_cubes;
    std::vector<CgBaseRenderableObject*> list_of_curves;
    list_of_cubes.push_back(m_cube);
    list_of_curves.push_back(m_kurve);

    m_scenegraph_enity_root = new CgScenegraphEnity(list_of_cubes,glm::mat4(1),appearance,NULL,{});

    CgScenegraphEnity* scenegraph_enity2;
    scenegraph_enity2 = new CgScenegraphEnity(list_of_curves,mv_matrix,appearance,m_scenegraph_enity_root,{});

    list_of_cubes[0] = new CgCube(101);

    CgScenegraphEnity* scenegraph_enity3;
    scenegraph_enity3 = new CgScenegraphEnity(list_of_cubes,mv_matrix,appearance,scenegraph_enity2,{});
    scenegraph_enity2->addChildEnity(scenegraph_enity3);
    m_scenegraph_enity_root->addChildEnity(scenegraph_enity2);

    m_scenegraph = new CgScenegraph(m_scenegraph_enity_root,glm::mat4(1.));
    m_list_of_all_objects = m_scenegraph->getAllObjectsOfGraph();
    m_position_of_list_all_objects = -1;

}


void CgSceneControl::drawAxis(CgBaseRenderableObject* o)
{
    unsigned int type = o->getType();
    if(type == 2) {
        CgPolyline* cp = (CgPolyline*)o;
        glm::vec3 start_point = cp->getVertices()[0];
        glm::vec3 end_point_x = cp->getVertices()[1] * glm::vec3(4.,4,4);
        std::cout<< end_point_x.x << " " << end_point_x.y << " " << end_point_x.z <<std::endl;
        glm::vec3 _x = end_point_x - start_point;
        glm::vec3 end_point_y = glm::cross(_x,glm::vec3(0,1,0)) + start_point;
        std::cout<< end_point_y.x << " " << end_point_y.y << " " << end_point_y.z <<std::endl;
        glm::vec3 end_point_z = glm::cross(_x,glm::vec3(0,0,1)) + start_point;
        std::cout<< end_point_z.x << " " << end_point_z.y << " " << end_point_z.z <<std::endl;
        cp->addAxe(new CgPolyline(start_point,end_point_x,glm::vec3(1,1,0),2,301));
        cp->addAxe(new CgPolyline(start_point,end_point_y,glm::vec3(1,0,1),2,302));
        cp->addAxe(new CgPolyline(start_point,end_point_z,glm::vec3(0,1,1),2,303));
    } else if (type == 4) {
        CgCube* cb = (CgCube*)o;
        glm::vec3 start_point = cb->getVertices()[0];
        glm::vec3 x_normal =  cb->getFaceNormals()[0] * glm::vec3(2,2,2);
        glm::vec3 y_normal = glm::cross(x_normal,glm::vec3(0,1,0)) + start_point;
        glm::vec3 z_normal = glm::cross(y_normal,glm::vec3(0,0,1)) + start_point;
        cb->addAxe(new CgPolyline(start_point,start_point + x_normal,glm::vec3(1,1,0),2,401));
        cb->addAxe(new CgPolyline(start_point,y_normal,glm::vec3(1,0,1),2,402));
        cb->addAxe(new CgPolyline(start_point,z_normal,glm::vec3(0,1,1),2,403));
    }
        for(CgBaseRenderableObject* po : o->getAxis()) {
            CgPolyline* pl = (CgPolyline*)po;
//            std::cout << "---" << std::endl;
            m_renderer->init(pl);
        }
        m_renderer->redraw();
}

void CgSceneControl::clearAxis(CgBaseRenderableObject* o)
{
    if(o->getAxis().size()>0) {
        o->clearAxis();
    }
}

void CgSceneControl::createNormaleOfCube()
{
    std::cout << "createNormaleOfCube" << std::endl;
    std::vector<unsigned int> m_cube_triangle_indices = m_cube -> getTriangleIndices();
    std::vector<glm::vec3> m_cube_vertices = m_cube -> getVertices();
    std::vector<glm::vec3> m_cube_faces_normals = m_cube -> getFaceNormals();
    std::vector<glm::vec3> m_cube_faces_centroids;
    for (unsigned int i = 0; i < m_cube_triangle_indices.size(); i = i + 3) {
        unsigned int vertex_1 = m_cube_triangle_indices[i];
        unsigned int vertex_2 = m_cube_triangle_indices[i + 1];
        unsigned int vertex_3 = m_cube_triangle_indices[i + 2];

        glm::vec3 p1 = m_cube_vertices[vertex_1];
        glm::vec3 p2 = m_cube_vertices[vertex_2];
        glm::vec3 p3 = m_cube_vertices[vertex_3];

        glm::vec3 centroid = glm::vec3((p1.x+p2.x+p3.x)/3.0,(p1.y+p2.y+p3.y)/3.0,(p1.z+p2.z+p3.z)/3.0);
        m_cube_faces_centroids.push_back(centroid);
    }
    for (unsigned int i = 0; i < m_cube_faces_centroids.size(); i++) {
        CgPolyline* pl = new CgPolyline(m_cube_faces_centroids[i],m_cube_faces_centroids[i] + m_cube_faces_normals[i],glm::vec3(1,1,1),2,i);
        m_polylines.push_back(pl);
    }
}

void CgSceneControl::createCurve()
{
    std::vector<glm::vec3> pointList;
//    pointList.push_back(glm::vec3(-0.5,0,0));
    pointList.push_back(glm::vec3(0,0.5,0));
    pointList.push_back(glm::vec3(0.25,0.25,0));
    pointList.push_back(glm::vec3(0.5,0,0));
    pointList.push_back(glm::vec3(0.25,-0.25,0));
    pointList.push_back(glm::vec3(0,-0.5,0));
    m_kurve = new CgPolyline(pointList,glm::vec3(1,0,1),2,999);
    //m_polylines.push_back(m_kurve);
}

void CgSceneControl::resetCurve()
{
    std::vector<glm::vec3> pointList;
//    pointList.push_back(glm::vec3(-0.5,0,0));
    pointList.push_back(glm::vec3(0,0.5,0));
    pointList.push_back(glm::vec3(0.25,0.25,0));
    pointList.push_back(glm::vec3(0.5,0,0));
    pointList.push_back(glm::vec3(0.25,-0.25,0));
    pointList.push_back(glm::vec3(0,-0.5,0));
    m_kurve->setVertices(pointList);
//    createCurve();
}

void CgSceneControl::makeRisenfeldAlgo(int mittel)
{
    m_kurve->lane_Risenfeld_Algo(mittel);
}

void CgSceneControl::setColor(int r,int g,int b)
{
        float _r,_g,_b;
        _r = r / 256.0 + 0.0000000001;
        _g = g / 256.0;
        _b = b / 256.0;
//        std::cout << "Get Color_RGB (" << _r << "," << _g << "," << _b << ")" << std::endl;
        m_color = glm::vec4(_r,_g,_b,1.0);

//        std::cout << m_program->uniformLocation("mycolor") << std::endl;

//        m_program->setUniformValue(m_program->uniformLocation("mycolor"),glm::vec4(_r,_g,_b,1));

//        update();
}

void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h


    if(e->getType() & Cg::CgMouseEvent)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
//        std::cout << *ev << std::endl;

         // hier kommt jetzt die Abarbeitung des Events hin...
    }


    if(e->getType() & Cg::CgTrackballEvent)
    {
        CgTrackballEvent* ev = (CgTrackballEvent*)e;
//        std::cout << *ev << std::endl;

        m_trackball_rotation=ev->getRotationMatrix();
        m_renderer->redraw();
    }


    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if(e->getType() & Cg::CgKeyEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*)e;
        std::cout << *ev <<std::endl;

        if(ev->text()=="+")
        {
            glm::mat4 scalemat = glm::mat4(1.);
            scalemat = glm::scale(scalemat,glm::vec3(1.2,1.2,1.2));
            if(m_position_of_list_all_objects == -1) {
                std::cout << "Kein Objekt selektiert wird!" << std::endl;
                m_current_transformation=m_current_transformation*scalemat;
            } else {
//                m_current_transformation=m_current_transformation*scalemat;
                m_list_of_all_objects[m_position_of_list_all_objects]->setTransformMatrix(m_list_of_all_objects[m_position_of_list_all_objects]->getTransformMatrix()*scalemat);
            }
//            m_current_transformation=m_current_transformation*scalemat;
            m_renderer->redraw();
        }
        if(ev->text()=="-")
        {
            glm::mat4 scalemat = glm::mat4(1.);
            scalemat = glm::scale(scalemat,glm::vec3(0.8,0.8,0.8));
            if(m_position_of_list_all_objects == -1) {
                std::cout << "Kein Objekt selektiert wird!" << std::endl;
                m_current_transformation=m_current_transformation*scalemat;
            } else {
//                m_current_transformation=m_current_transformation*scalemat;
                m_list_of_all_objects[m_position_of_list_all_objects]->setTransformMatrix(m_list_of_all_objects[m_position_of_list_all_objects]->getTransformMatrix()*scalemat);
            }
//            m_current_transformation=m_current_transformation*scalemat;

            m_renderer->redraw();
        }
        if(ev->key()==16777237)
            if(m_scenegraph!=NULL) // |
            {                       // ^
                if(m_position_of_list_all_objects == m_list_of_all_objects.size() - 1) {
                    m_position_of_list_all_objects = -1;
                }

                m_position_of_list_all_objects++;
                if(m_position_of_list_all_objects == 0) {
                    clearAxis(m_list_of_all_objects[m_list_of_all_objects.size()-1]);
                } else {
                    clearAxis(m_list_of_all_objects[m_position_of_list_all_objects-1]);
                }
                drawAxis(m_list_of_all_objects[m_position_of_list_all_objects]);
                std::cout << m_list_of_all_objects[m_position_of_list_all_objects] <<std::endl;

            } else {
                std::cout<<"Noch keine SceneGraph erzeugt! Bitte in Tab Aufgabe 3/4-Button klicken!"<<std::endl;
            }
        if(ev->text()=="x" || ev->text()=="y" || ev->text()=="z") {
            if(m_position_of_list_all_objects == -1) {
                std::cout << "Kein Objekt selektiert wird!" << std::endl;
            } else {
                glm::mat4 rotationMatrix;
                if(ev->text()=="x")
                {
                    CgPolyline* pl_x_axe = (CgPolyline*)m_list_of_all_objects[m_position_of_list_all_objects]->getAxis()[0];
                    glm::vec3 x_axe = pl_x_axe->getDirectionVector();
                    rotationMatrix = glm::rotate(3.1415926f/4.0f,x_axe);
                }
                if(ev->text()=="y")
                {
                    CgPolyline* pl_y_axe = (CgPolyline*)m_list_of_all_objects[m_position_of_list_all_objects]->getAxis()[1];
                    glm::vec3 y_axe = pl_y_axe->getDirectionVector();
                    rotationMatrix = glm::rotate(3.1415926f/4.0f,y_axe);
                }
                if(ev->text()=="z")
                {
                    CgPolyline* pl_z_axe = (CgPolyline*)m_list_of_all_objects[m_position_of_list_all_objects]->getAxis()[2];
                    glm::vec3 z_axe = pl_z_axe->getDirectionVector();
                    rotationMatrix = glm::rotate(3.1415926f/4.0f,z_axe);
                }
                m_list_of_all_objects[m_position_of_list_all_objects]->setTransformMatrix(m_list_of_all_objects[m_position_of_list_all_objects]->getTransformMatrix()*rotationMatrix);
                m_renderer->redraw();
            }

        }
        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if(e->getType() & Cg::CgVerschiebungsEvent)
    {
        CgVerschiebungsEvent* ev = (CgVerschiebungsEvent*)e;
        std::cout << *ev <<std::endl;
        glm::mat4 translation = glm::mat4(1.);
        translation = glm::translate(translation,glm::vec3(ev->dx(),ev->dy(),ev->dz()));
        if(m_position_of_list_all_objects != -1) {
            m_list_of_all_objects[m_position_of_list_all_objects]->setTransformMatrix(m_current_transformation*translation);
        } else {
            std::cout << "Kein Objekt selektiert wird!" << std::endl;
        }
    }

    if(e->getType() & Cg::WindowResizeEvent)
    {
         CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
         std::cout << *ev <<std::endl;
         m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    if(e->getType() & Cg::LoadObjFileEvent)
    {

        CgLoadObjFileEvent* ev = (CgLoadObjFileEvent*)e;


        ObjLoader* loader= new ObjLoader();
        loader->load(ev->FileName());

        std::cout << ev->FileName() << std::endl;

        std::vector<glm::vec3> pos;
        loader->getPositionData(pos);

         std::vector<glm::vec3> norm;
         loader->getNormalData(norm);

          std::vector<unsigned int> indx;
          loader->getFaceIndexData(indx);



        m_mesh->init(pos,norm,indx);
        m_renderer->init(m_mesh);
        m_renderer->redraw();
        std::cout << m_mesh->getVertices().size() << std::endl;

        if(m_mesh->getVertexNormals().size() < 1) {
//            std::cout << "!@#$%" << std::endl;
            m_mesh->calcFaceNormal();
            m_mesh->calcVertexNormal();
        }

        std::cout << m_mesh->getVertexNormals().size() << std::endl;
//        std::vector<glm::vec3> m_vertex_normals = m_mesh->getVertexNormals();
//        for (unsigned int i = 0; i < m_vertex_normals.size(); i++) {
//            std::cout << "Vertex_" << i << " , X:" << m_vertex_normals[i].x << ", Y:" << m_vertex_normals[i].y << ", Z:" << m_vertex_normals[i].z << std::endl;
//        }
    }

    if(e->getType() & Cg::CgUnterteilungsEvent)
    {
        CgUnterteilungsEvent *ev = (CgUnterteilungsEvent*)e;
        std::cout << *ev <<std::endl;
        if(m_kurve!=NULL){
            if(ev->mode() == 1) {
                m_kurve->lane_Risenfeld_Algo(ev->mittel());
            } else { //reset
                std::cout<<"Check!"<<std::endl;
                resetCurve();
                std::cout<<"Check!"<<std::endl;
            }
            m_renderer -> init(m_kurve);
            m_renderer -> redraw();
        } else {
            std::cout<<"Kein Kurve erzeugt! Bitte klicken Sie Button 'Display Kurve'" << std::endl;
        }
    }

    if(e->getType() & Cg::CgRotateEvent)
    {
        CgRotateEvent *ev = (CgRotateEvent*)e;
        std::cout << *ev <<std::endl;
        if(m_kurve!=NULL){
            m_rotationObject = new CgRotationObject(79,m_kurve,ev->grad());
            m_renderer -> init(m_rotationObject);
            m_renderer->redraw();
        } else {
            std::cout<<"Kein Kurve erzeugt! Bitte klicken Sie Button 'Display Kurve'" << std::endl;
        }


//        m_rotationMitVierObject = new CgRotationMitVierObject(1112,m_kurve,ev->grad());
//        m_renderer -> init(m_rotationMitVierObject);
//        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgColorChangeEvent)
    {
        CgColorChangeEvent* ev = (CgColorChangeEvent*)e;
        std::cout << *ev <<std::endl;
        setColor(ev->r(),ev->g(),ev->b());
        m_renderer -> redraw();
    }
    if(e->getType() & Cg::CgSpecialEvent)
    {
        CgSpecialEvent* ev = (CgSpecialEvent*)e;
        std::cout << *ev <<std::endl;
        if(ev->signal()==1){
            m_scenegraph = NULL;
            m_kurve = NULL;
            m_mesh = NULL;
            m_rotationObject = NULL;
            m_cube = new CgCube(99);
            createNormaleOfCube();
            m_renderer->init(m_cube);
            for(CgPolyline* pl : m_polylines) {
                //std::cout << "---" << std::endl;
                m_renderer->init(pl);
            }
        } else if(ev->signal()==2) {
            m_scenegraph = NULL;
            m_cube = NULL;
            m_mesh = NULL;
            m_polylines.clear();
            createCurve();
            m_renderer->init(m_kurve);
        } else if(ev->signal()==3) {
            m_mesh = NULL;
            m_cube = NULL;
            m_kurve =NULL;
            m_rotationObject = NULL;
            createSceneGraph();
        }
        m_renderer -> redraw();
    }

    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;


}
