#include "read_rss.h"
using std::to_string;
using std::ofstream;
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

    XMLElement* title=channel->FirstChildElement("title");
    /* cout<<"titlename :"<<title->Name()<<" tiltletxt:"<<title->GetText()<<endl; */

    XMLElement* link=title->NextSiblingElement("link");
    /* cout<<"link is "<<link->Name()<<endl; */
    /* printf("link is %s",link->GetText()); */

    XMLElement* description=title->NextSiblingElement("description");
    /* cout<<"description is "<<description->Name()<<endl; */
    /* cout<<"description txt is "<<description->GetText()<<endl; */

    XMLElement* item=title->NextSiblingElement("item");
    /* cout<<"item name "<<item->Name()<<endl; */
    /* cout<<"item txt"<<item->GetText()<<endl; */
    int count=0;

    while(item){
        //获取依次获取link title description content
        //可封装
        string contentFileName("content");
        RssItem tmp;
        //    读取title
        bzero(&tmp.title,tmp.title.size());
        XMLElement* itemTitle=item->FirstChildElement("title");
        tmp.title=itemTitle->GetText();
        //    读取link
        bzero(&tmp.link,tmp.link.size());
        XMLElement* itemLink=item->FirstChildElement("link");
        tmp.link=itemLink->GetText();
        /* printf("test link is  %s\n",tmp.link.c_str()); */
        bzero(&tmp.description,tmp.description.size());
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
        bzero(&tmp.content,tmp.content.size());
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
    for(auto i:_rss){
        cout<<"tmp is "<<endl
            <<"title is "<<i.title<<endl;
        printf("test link is  %s\n",i.link.c_str());
        cout<<"description is "<<i.description<<endl;
        /* cout<<"content is "<<tmp.content<<endl; */

    }

}
int main()
{
    RssReader rr;
    rr.parseRss("coolshell.xml");
    return 0;
}

