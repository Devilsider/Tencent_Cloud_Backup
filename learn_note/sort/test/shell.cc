#include <vector>
#include <iostream>
using namespace std;

template<typename T,typename Compare = std::less<T>>
class Shell{
    public:
        Shell(){}
        Shell(const vector<T> &arr)
        :_arr(arr)
        {}

        void shellSort(){
            int len=(int)_arr.size();
            int temp;
            for(int gap=len>>1;gap>0;gap>>=1) {
                for(int i=gap;i<len;++i){
                    temp=_arr[i];
                    for(int j=i-gap;j>=0&&_arr[j]>temp;j-=gap){
                        swap(_arr[j+gap],_arr[j]);
                    }
                }
            }
        }
        void print(){
            for(auto &i:_arr){
                cout<<" "<<i;
            }
            cout<<endl;
        }
    private:
        vector<T> _arr;
};
int main()
{
    vector<int> tmp={1,3,5325,7,45,475,345,23,645,7856,89,9745,462,986};
    Shell<int> sh(tmp);
    sh.shellSort();
    sh.print();

    vector<char> tmp2={'z','s','/','q'};
    Shell<char> sh1(tmp2);
    sh1.shellSort();
    sh1.print();
    return 0;
}

