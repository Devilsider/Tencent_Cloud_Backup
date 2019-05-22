#include "read_rss.h"
using std::to_string;
using std::ofstream;
using std::regex;
void RssReader::parseRss(const string &filename){
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filename.c_str());
    if(0!=doc.Error()){
        cout<<"filename error!fail creating RssReader "<<endl;
        return;
    }
    /* doc.Print(); */

    XMLElement* root = doc.RootElement();
    XMLElement* channel=root->FirstChildElement("channel");
    if(NULL==channel){
        cout<<"get channel error!"<<endl;
        return;
    }
    RssItem tmp;

    tmp.title.clear();
    XMLElement* title=channel->FirstChildElement("title");
    tmp.title=title->GetText();
    /* cout<<"titlename :"<<title->Name()<<" tiltletxt:"<<title->GetText()<<endl; */

    tmp.link.clear();
    XMLElement* link=title->NextSiblingElement("link");
    tmp.link=link->GetText();
    /* cout<<"link is "<<link->Name()<<endl; */
    /* printf("link is %s",link->GetText()); */

    tmp.description.clear();
    XMLElement* description=title->NextSiblingElement("description");
    tmp.description=description->GetText();
    /* cout<<"description is "<<description->Name()<<endl; */
    /* cout<<"description txt is "<<description->GetText()<<endl; */

    tmp.content.clear();
    _rss.push_back(tmp);
    XMLElement* item=title->NextSiblingElement("item");
    /* cout<<"item name "<<item->Name()<<endl; */
    /* cout<<"item txt"<<item->GetText()<<endl; */
     
    while(item){
        //获取依次获取link title description content
        //可封装
        //    读取title
        tmp.title.clear();
        XMLElement* itemTitle=item->FirstChildElement("title");
        tmp.title=itemTitle->GetText();
        //    读取link
        tmp.link.clear();
        XMLElement* itemLink=item->FirstChildElement("link");
        tmp.link=itemLink->GetText();
        /* printf("tmp.link is %s \n",itemLink->GetText()); */
        /* printf("test link is  %s\n",tmp.link.c_str()); */
        tmp.description.clear() ;
        XMLElement* itemDescription=item->FirstChildElement("description");
        tmp.description=itemDescription->GetText();
    
        /* //content内容太过庞大，存到文件里面去，用文件指针指向他 */
        /* contentFileName.append(to_string(count)); */
        /* cout<<"content file name is "<<contentFileName<<endl; */
        /* /1* open(contentFileName.c_str(),O_CREAT,0666); *1/ */
        /* XMLElement* itemContent=item->FirstChildElement("content:encoded"); */
        /* ofstream ofs(contentFileName); */
        /* ofs<<itemContent->GetText(); */
        //读取content
        tmp.content.clear(); 
        XMLElement* itemContent=item->FirstChildElement("content:encoded");
        tmp.content=itemContent->GetText();
        

        /* cout<<"tmp is "<<endl */
        /*     <<"title is "<<tmp.title<<endl; */
        /* printf("test link is  %s\n",tmp.link.c_str()); */
        /* cout<<"description is "<<tmp.description<<endl; */
        /* cout<<"content is "<<tmp.content<<endl; */

        _rss.push_back(tmp);
        item=item->NextSiblingElement("item");
    }
    /* for(auto i:_rss){ */
    /*     cout<<"tmp is "<<endl */
    /*         <<"title is "<<i.title<<endl; */
    /*     printf("test link is  %s\n",i.link.c_str()); */
    /*     cout<<"description is "<<i.description<<endl; */
    /*     /1* cout<<"content is "<<tmp.content<<endl; *1/ */

    /* } */

}
void RssReader::dump(const string &filename){
    ofstream ofs(filename,std::ios::app);
    int id=0;
    string tmp;
    for(auto &i:_rss){
        ofs<<"<doc>"<<endl;
        ofs<<" <docid> "<<id<<"</docid>"<<endl;
        ofs<<" <title> "<<i.title<<"</title>"<<endl;
        ofs<<" <link> "<<i.link<<"</link>"<<endl;
        ofs<<" <description> "<<i.description<<"</description>"<<endl;
        //将<*> 都替换成空格
        regex pattern("<.*?>");
        tmp.clear(); 
        tmp=regex_replace(i.content,pattern," ");
        i.content.clear();
        i.content=tmp;
        ofs<<" <content> "<<i.content<<"</content>"<<endl;
        ofs<<"</doc>"<<endl;
        ++id;
    }
    ofs.close();
}


int main()
{
    RssReader rr;
    rr.parseRss("coolshell.xml");
    rr.dump("pagelib.txt");
    return 0;
}

