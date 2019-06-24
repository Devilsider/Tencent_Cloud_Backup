#include "readRss.h"
#include <iostream>
using std::to_string;
using std::ofstream;
using std::regex;
void readRss::parseRss(const string &filename)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filename.c_str());
    if(0!=doc.Error())
    {
        cout<<"filename error!fail creating rssReader"<<endl;
        return;
    }

    XMLElement* root = doc.RootElement();
    XMLElement* channel = root->FirstChildElement("channel");
    if(NULL== channel){
        cout<<"get channel error"<<endl;
        return;
    }

    RssItem tmp;

    tmp.title.clear();

    XMLElement* title = channel->FirstChildElement("title");
    tmp.title = title->GetText();

    tmp.link.clear();
    XMLElement* link = title->NextSiblingElement("link");
    tmp.link = link->GetText();

    tmp.description.clear();
    XMLElement * derscription = title->NextSiblingElement("description");
    tmp.description = derscription->GetText();

    tmp.content.clear();
    _rss.push_back(tmp);


    XMLElement* item  = title->NextSiblingElement("item");




}

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

