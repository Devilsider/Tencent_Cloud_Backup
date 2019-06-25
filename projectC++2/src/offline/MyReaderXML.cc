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
void MyReaderXML::parseDoc(const string &filename)
{
    tinyxml2::XMLDocument pagelib;
    pagelib.LoadFile(filename.c_str());
    if(0!=pagelib.Error()){
        cout<<"load file "<<filename<<" error!"<<endl;
        return;
    }
    XMLElement* doc  = pagelib.RootElement() ;
    while(doc){
        string temp;
        XMLElement* docid = doc->FirstChildElement("docid");
        if(docid!=NULL){
            if(docid->GetText()!=NULL)
            {
                temp.append("<doc><docid>").append(docid->GetText()).append("</docid>");
            }
            else {
                temp.append("<doc><docid>").append("</docid>");
            }
        }
        XMLElement* title = doc->FirstChildElement("title");
        if(title!=NULL){
            if(title->GetText()!=NULL){
                temp.append("<title>").append(title->GetText()).append("</title>");
            }
            else{
                temp.append("<title>").append("</title>");
            }
        }
        XMLElement* link = doc->FirstChildElement("link");
        if(link!=NULL){
            if(link->GetText()!=NULL){
                temp.append("<link>").append(link->GetText()).append("</link>");
            }
            else{
                temp.append("<link>").append("</link>");
            }
        }
        XMLElement* description = doc->FirstChildElement("description");
        if(description!=NULL){
            if(description->GetText()!=NULL){
                temp.append("<description>").append(description->GetText()).append("</description>");
            }
            else{
                temp.append("<description>").append("</description>");
            }
        }
        XMLElement* content = doc->FirstChildElement("content::encoded");
        if(content!=NULL){
            if(content->GetText()!=NULL){
                temp.append("<content::encoded>").append(content->GetText()).append("</content::encoded>");
            }
            else{
                temp.append("<content::encoded>").append("</content::encoded>").append("</doc>");
            }
        }
        _vecFilesfile.push_back(temp);
        doc = doc->NextSiblingElement("doc");
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
        ofs<<" <description>"<<tmp<<"</description>"<<endl;
        tmp = regex_replace(iter->content,pattern,"");
        ofs<<" <content::encoded>"<<tmp<<"</content::encoded>"<<endl;
        ofs<<"</doc>"<<endl;
        ++id;
    }
    ofs.close();
}

}//end of wd


