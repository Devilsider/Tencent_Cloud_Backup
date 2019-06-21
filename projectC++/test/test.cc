#include <cpp_redis/cpp_redis>
#include <cpp_redis/misc/macro.hpp>

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::cout;
using std::endl;

int main()
{
    cpp_redis::client mycli;
    
    mycli.connect("127.0.0.1",6379,[](const string &host,size_t port,cpp_redis::client::connect_state status ){
            if(status==cpp_redis::client::connect_state::dropped){
               cout<<"clinet disconnected from " << host <<" : "<<port<<endl;
            }
            }); 
    
    string s("我是韩梅梅，我不好好不好");
    mycli.set("你好",s,[&s](cpp_redis::reply & rep){
             cout<<"set 你好 "<<s<<" :"<<rep<<endl;
             });

    __CPP_REDIS_LOG(debug,"this debug messages");
    mycli.get("你好",[](cpp_redis::reply &rep){
              cout<<"get 你好: "<<rep<<endl;
              });
    std::vector<string> vs;
    auto get = mycli.get("你好");

    mycli.sync_commit();
    cpp_redis::reply r = get.get();
    string s1;

    if(r.is_null())
    {
        s1="";
    }

    s1= r.as_string();
    cout<<s1<<endl;
    /* if(s1.empty()){ */
    /*     cout<<"zhen de "<<endl; */
    /* } */
    vs.push_back("你好");
    mycli.del(vs,[](cpp_redis::reply &rep)
              {
              cout<<"del :"<<rep<<endl;
              });
    mycli.sync_commit();
    return 0;
}

