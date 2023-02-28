// Jahongir Hayitov CS-01
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
#define rep(i,n) for (ll i = 0; i < (n); ++i)
#define FOR(i,a,b) for(ll i = a; i < ll(b); i++)

class YouPay {
public:
    YouPay(ll low, ll high, ll pos) {
        this->lowVal = low;
        this->highVal = high;
        this->position = pos;
    }
    ll getLowVal() {
        return this->lowVal;
    }
    ll getHighVal() {
        return this->highVal;
    }
    ll getPosition() {
        return this->position;
    }
private:
    ll lowVal;
    ll highVal;
    ll position;
};

vector<YouPay*> countingSort(vector<YouPay*> arr, bool isLow, bool ascending) {
    // first val, second extra info
    vector<YouPay*> res(arr.size());
    ll maxVal, minVal;
    rep(i, arr.size()) {
        // find the max and min values
        if(isLow) {
            if (i == 0) {
                maxVal = arr[i]->getLowVal();
                minVal = arr[i]->getLowVal();
            } else if (arr[i]->getLowVal() > maxVal) {
                maxVal = arr[i]->getLowVal();
            } else if (arr[i]->getLowVal() < minVal) {
                minVal = arr[i]->getLowVal();
            }
        } else {
            if (i == 0) {
                maxVal = arr[i]->getHighVal();
                minVal = arr[i]->getHighVal();
            } else if (arr[i]->getHighVal() > maxVal) {
                maxVal = arr[i]->getHighVal();
            } else if (arr[i]->getHighVal() < minVal) {
                minVal = arr[i]->getHighVal();
            }
        }
    }
    // create counting array
    vector<pair<ll, ll>> counting;
    for(ll i = minVal; i<=maxVal; i++) {
        counting.push_back({i, 0});
    }
    // count the elements
    for(YouPay* num : arr) {
        if(isLow) {
            if (ascending) counting[num->getLowVal() - minVal].second++;
            else counting[maxVal - num->getLowVal()].second++;
        } else {
            if(ascending) counting[num->getHighVal()-minVal].second++;
            else counting[maxVal - num->getHighVal()].second++;
        }
    }
    
    for(ll i=1; i<counting.size(); i++) {
        counting[i].second += counting[i-1].second;
    }
    // newCounting for determining the elements' start positions
    vector<pair<ll,ll>> newCounting = counting;
    if(ascending) newCounting[0].first = minVal;
    else newCounting[0].first = maxVal;
    newCounting[0].second = 0;
    for(ll i=0; i<counting.size()-1; i++) {
        newCounting[i+1].second = counting[i].second;
    }

    // Put element in the right position
    for(YouPay* elem : arr) {
        if(isLow) {
            if(ascending) res[newCounting[elem->getLowVal()-minVal].second++] = elem;
            else res[newCounting[maxVal - elem->getLowVal()].second++] = elem;
        } else {
            if(ascending) res[newCounting[elem->getHighVal()-minVal].second++] = elem;
            else res[newCounting[maxVal - elem->getHighVal()].second++] = elem;
        }
    }
    
    return res;
}

int main() {
    ll t;
    cin >> t;
    vector<YouPay*> arr;
    // input
    rep(i, t) {
        ll l, h;
        // low and high costs
        cin >> l >> h;
        YouPay* bid = new YouPay(l, h, i+1);
        arr.push_back(bid);
    }
    // First sort high costs in ascending order
    arr = countingSort(arr, false, true);
    // Then sort low-value costs in descending order
    arr = countingSort(arr, true, false);
    // output
    for(YouPay* iter : arr) {
        cout << iter->getPosition() << " ";
    }
    return 0;
}
