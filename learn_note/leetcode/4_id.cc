#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1=(int)nums1.size();
        int len2=(int)nums2.size();
        if(len1>len2){
            swap(len1,len2);
            swap(nums1,nums2);
        }
        /* for(auto &i:nums1){ */
        /*     cout<<">>nums1" <<endl; */
        /*     cout<<" "<<i; */
        /* } */
        /* cout<<endl; */
        /* for(auto &j:nums2){ */
        /*     cout<<">>nums1" <<endl; */
        /*     cout<<" "<<j; */
        /* } */
        /* cout<<endl; */
        int imin=0;
        int imax=len1;
        int i,j; 
        while(imin<=imax){
            i=(imin+imax)/2;
            j=(len1+len2+1)/2 - i;
            /* cout<<" i = "<<i<<" , j = "<< j <<endl; */
            if(i<imax&&nums1[i]<nums2[j-1]){
                /* cout<<" 1 1 "<<endl; */
                imin=i+1;
            }
            else if(imin<i&&nums2[j]<nums1[i-1]){
                /* cout<<" 2 2 "<<endl; */
                imax=i-1;
            }
            else {
                /* cout<<" 3 3"<<endl; */
                int maxLeft=0;
                if(0==i){
                    maxLeft=nums2[j-1];
                }
                else if(j==0){
                    maxLeft=nums1[i-1];
                }
                else {
                    maxLeft=max(nums1[i-1],nums2[j-1]);
                }
                if((len1+len2)%2==1){
                    return maxLeft;
                }
                int minRight=0;
                if(len2==j){
                    minRight=nums1[i];
                }
                else if(len1==i){
                    minRight=nums2[j];
                }
                else {
                    minRight=min(nums1[i],nums2[j]);
                }
                return (maxLeft+minRight)/2.0;
                
            }
        }
        return 0.0;
    }
    bool isOdd(int n){
        if(1==(n&1)){
            //奇数
            return true;
        }
        return false;
    }
};



int main(){
    vector<int> v1={1,3};
    vector<int> v2={2};
    
    Solution s1;
    double ret= s1.findMedianSortedArrays(v1,v2);
    
    cout<<" "<<ret<<endl;

}
