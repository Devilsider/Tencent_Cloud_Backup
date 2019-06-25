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
    if(title!=NULL)
    {
        if(NULL==title->GetText())
        {
             temp.title="";
        }else{
            cout<<temp.title<<endl;       
            temp.title=title->GetText();
        }
    }

    XMLElement* link = title->NextSiblingElement("link");
    if(link!=NULL)
    {
        if(NULL==link->GetText())
        {
            temp.link = "";
        }else{
             temp.link = link->GetText();
        }
    }

    XMLElement* description = title->NextSiblingElement("description");
    if(description!=NULL) 
    {
        if(NULL==description->GetText())
        {
            temp.description = "";
        }else{
            temp.description = description->GetText();
        }
    }
    
    _rss.push_back(temp);

    XMLElement* item = title->NextSiblingElement("item");


    while(item)
    {
        RssItem tmp;
        XMLElement* itemTitle = item->FirstChildElement("title");
        if(itemTitle!=NULL)
        {
            if(NULL==itemTitle->GetText()) 
            {
                tmp.title = "";
            }
            else {
                tmp.title = itemTitle->GetText();
            }
        }
        XMLElement* itemLink = item->FirstChildElement("link");
        if(itemLink!=NULL)
        {
            if(NULL==itemLink->GetText()){
                tmp.link = "";
            }
            else {
                tmp.link = itemLink->GetText();
            }
        }
        

        XMLElement* itemDescription = item->FirstChildElement("description");
        if(itemDescription!=NULL) 
        {
            if(NULL==itemDescription->GetText())
            {
                tmp.description="";
            }
            else{
                tmp.description = itemDescription->GetText();
            }
        }
        
        XMLElement* itemContent = item->FirstChildElement("content::encoded");
        if(itemContent!=NULL) 
        {
            if(NULL==itemContent)
            {
                tmp.content="";
            }
            else 
            {
                tmp.content = itemContent->GetText();
            }
        }

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
        regex pattern("<(.|\\s)*?>");
        ofs<<"<doc>"<<endl;
        ofs<<" <docid>"<<id<<"</docid>"<<endl;
        tmp = regex_replace(iter->title,pattern,"");
        ofs<<" <title>"<<tmp<<"</title>"<<endl;
        tmp = regex_replace(iter->link,pattern,"");
        ofs<<" <link>"<<tmp<<"</link>"<<endl;
        tmp = regex_replace(iter->description,pattern,"");
        cout<< tmp <<endl;
        ofs<<" <description>"<<tmp<<"</description>"<<endl;
        tmp = regex_replace(iter->content,pattern,"");
        ofs<<" <content::encoded>"<<tmp<<"</content::encoded>"<<endl;
        ofs<<"</doc>"<<endl;
        ++id;
    }
    ofs.close();
}

}//end of wd


