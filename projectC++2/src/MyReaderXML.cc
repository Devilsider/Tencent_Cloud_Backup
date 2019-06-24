#include "MyReaderXML.h"
using std::to_string;
using std::ofstream;
using std::regex;

namespace wd
{
void MyReaderXML::parseRss(const string &filename)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filename.c_str());
    if(0!=doc.Error())
    {
        cout<<"load file "<<filename<<" error!"<<endl;
        return ;
    }

    XMLElement* root = doc.RootElement();
    XMLElement* channel = root->FirstChildElement("channel");
    if(NULL==channel)
    {
        cout<<"get channel error!"<<endl;
        return ;
    }
    RssItem temp;
    
    XMLElement* title = channel->FirstChildElement("title");
    temp.title=title->GetText();

    XMLElement* link = title->NextSiblingElement("link");
    temp.link = link->GetText();

    XMLElement* description = title->NextSiblingElement("description");
    temp.description = description->GetText();
    
    _rss.push_back(temp);

    XMLElement* item = title->NextSiblingElement("item");


    while(item)
    {
        RssItem tmp;
        
        XMLElement* itemTitle = item->FirstChildElement("title");
        tmp.title = itemTitle->GetText();
        
        XMLElement* itemLink = item->FirstChildElement("link");
        tmp.link = itemLink->GetText();
        
        XMLElement* itemDescription = item->FirstChildElement("description");
        tmp.description = itemDescription->GetText();
        
        XMLElement* itemContent = item->FirstChildElement("content::encoded");
        tmp.content = itemContent->GetText();

        _rss.push_back(tmp);
        item = item->NextSiblingElement("item");
    }

}

void MyReaderXML::dump(const string &filename)
{
    ofstream ofs(filename,std::ios::app);
    int id=1;
    
    for(auto iter =_rss.begin();iter!=_rss.end();++iter)
    {
        string tmp;
        ofs<<"<doc>"<<endl;
        ofs<<" <docid> "<<id<<" </docid>"<<endl;
        ofs<<" <title> "<<iter->title<<" </title>"<<endl;
        ofs<<" <link> "<<iter->link<<" </link>"<<endl;
        ofs<<" <description> "<<iter->description<<" </description>"<<endl;
        
        regex pattern("<.*?>");
        tmp = regex_replace(iter->content,pattern," ");
        iter->content=tmp;
        ofs<<" <content::encoded> "<<iter->content<<" </content::encoded>"<<endl;
        ofs<<"</doc>"<<endl;
        ++id;
    }
    ofs.close();
}

}//end of wd


