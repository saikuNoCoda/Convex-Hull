#include<bits/stdc++.h>
using namespace std;
#define ll long long int

void swap(pair<ll,ll> &p1,pair<ll,ll> &p2){
    pair<ll,ll> temp = p1;
    p1 = p2;
    p2 = temp;
}

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

ll distance(pair<ll,ll> p1,pair<ll,ll> p2){
    return (p1.first-p2.first)*(p1.first-p2.first) +
           (p1.second-p2.second)*(p1.second-p2.second);
}
pair<ll,ll> pivot;

bool PIVOTSORT(pair<ll,ll> p1,pair<ll,ll> p2){
    ll o = orientation(pivot,p1,p2);
    if(o==0){
        if(distance(pivot,p1) >= distance(pivot,p2)){
            return false;
        }else {
            return true;
        }
    }
    if(o==2){
        return true;
    }else {
        return false;
    }
}

pair<ll,ll> next_to_top(stack<pair<ll,ll>> &s){
    pair<ll,ll> val = s.top();
    s.pop();
    pair<ll,ll> ret = s.top();
    s.push(val);
    return ret;
};

void convex_hull(vector<pair<ll,ll>> points){
    ll n = points.size();

    ll ymin = points[0].second;
    ll min = 0;

    for(ll i=0;i<n;i++){
        ll y = points[i].second;
        if((y<ymin)||(y==ymin && points[i].first<points[min].first)){
            ymin = y;
            min = i;
        }
    }

    swap(points[0],points[min]);
    pivot = points[0];
    sort(points.begin()+1,points.end(),PIVOTSORT);

    vector<pair<ll,ll> > points_new;
    points_new.push_back(points[0]);
    for(ll i=1;i<n;i++){
        while(i<n-1 && orientation(pivot,points[i],points[i+1])==0){
            i++;
        }
        if(i<n)
            points_new.push_back(points[i]);
    }

    stack<pair<ll,ll>> s;
    s.push(points_new[0]);
    s.push(points_new[1]);
    s.push(points_new[2]);

    ll m = points_new.size();
    for(ll i=3;i<m;i++){
        while(s.size()>=2 && orientation(next_to_top(s),s.top(),points_new[i])!=2){
            s.pop();
        }
        s.push(points_new[i]);
    }

    while(!s.empty()){
        cout<<"{"<<s.top().first<<","<<s.top().second<<"}\n";
        s.pop();
    }
}

int main(){

    vector<pair<ll,ll> >points;
    points.push_back(make_pair(0,3));
    points.push_back(make_pair(1,1));
    points.push_back(make_pair(2,2));
    points.push_back(make_pair(4,4));
    points.push_back(make_pair(0,0));
    points.push_back(make_pair(1,2));
    points.push_back(make_pair(3,1));
    points.push_back(make_pair(3,3));
    convex_hull(points);
}