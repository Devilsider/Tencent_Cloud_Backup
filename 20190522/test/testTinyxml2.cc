#include <string>
#include "tinyxml2.h"
#include <iostream>
using namespace tinyxml2;
using std::cout;
using std::endl;

int main(){
    tinyxml2::XMLDocument doc;
    doc.LoadFile("test.xml");

    doc.Print();
    tinyxml2::XMLElement *scene=doc.RootElement();
    tinyxml2::XMLElement *surface=scene->FirstChildElement("node");

    while(surface){
        tinyxml2::XMLElement *surfaceChild=surface->FirstChildElement();
        const char *content;
        const tinyxml2::XMLAttribute *attributeOfSurface=surface->FirstAttribute();
        cout<<attributeOfSurface->Name()<<" : "<<attributeOfSurface->Value()<<endl;
        while(surfaceChild){
            content=surfaceChild->GetText();
            surfaceChild=surfaceChild->NextSiblingElement();
            cout<<content<<endl;
        }
        surface=surface->NextSiblingElement();
    }
    return 0;
}
    

