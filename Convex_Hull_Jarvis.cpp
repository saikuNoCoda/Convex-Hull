#include<bits/stdc++.h>
using namespace std;
#define ll long long int

ll orientation(pair<ll,ll> p,pair<ll,ll> q,pair<ll,ll> r){
    ll val = (r.second-q.second)*(q.first-p.first)-
             (q.second-p.second)*(r.first-q.first);
    if(val == 0){
        return 0;
    }
    if(val > 0){
        return 2;
    }else {
        return 1;
    }
}

ll convex_hull(vector<pair<ll,ll>> points,ll n){
    ll left = 0;
    vector<pair<ll,ll> > hull;
    for(ll i=0;i<n;i++){
        if(points[i].first<points[left].first){
            left = i;
        }
    }

    ll p = left,q;
    do {
        hull.push_back(points[p]);

        q = (p+1)%n;
        for(ll i=0;i<n;i++){
            if(orientation(points[p],points[i],points[q]) == 2){
                q = i;
            }
        }
        p = q;
    }while(p!=left);

    for(ll i=0;i<hull.size();i++){
        cout<<"{"<<hull[i].first<<","<<hull[i].second<<"}"<<endl;
    }
}

int main(){
    vector<pair<ll,ll> > points;

    ll n;
    n = 7;
    points.push_back(make_pair(0,3));
    points.push_back(make_pair(2,2));
    points.push_back(make_pair(1,1));
    points.push_back(make_pair(2,1));
    points.push_back(make_pair(3,0));
    points.push_back(make_pair(0,0));
    points.push_back(make_pair(3,3));

    convex_hull(points,n);
}