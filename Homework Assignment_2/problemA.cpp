// Jahongir Hayitov CS-01
#include<bits/stdc++.h>
typedef long long int ll;
using namespace std;

// Structure to represent a point
struct Point {
    ll x, y;
};

// Structure to represent a line segment
struct Segment {
    Point p1, p2;
};

// Compare function to sort line segments by x-coordinate of their left endpoint
bool segmentCompare(const Segment* a, const Segment* b) {
    return (a->p1.x < b->p1.x);
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
ll orientation(Point p, Point q, Point r) {
    ll val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Segment* s1, Segment* s2) {
    Point p1 = s1->p1, q1 = s1->p2;
    Point p2 = s2->p1, q2 = s2->p2;

    // Find the four orientations needed for general and special cases
    ll o1 = orientation(p1, q1, p2);
    ll o2 = orientation(p1, q1, q2);
    ll o3 = orientation(p2, q2, p1);
    ll o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;

    vector<Segment*> segments;
    for (ll i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Point p1 = {x1, y1};
        Point p2 = {x2, y2};
        Segment* s = new Segment{p1, p2};
        segments.push_back(s);
    }
    // Sort segments by x-coordinate of their left endpoint
    sort(segments.begin(), segments.end(), segmentCompare);
    
    // Use a set to store active segments (those that intersect with the sweep line)
    set<Segment*, decltype(&segmentCompare)> activeSegments(segmentCompare);
    
    // Sweep line algorithm
    for (ll i = 0; i < n; i++) {
        Segment* s = segments[i];
    
        // Check if the new segment intersects with any of the active segments
        for (Segment* activeSegment : activeSegments) {
            if (doIntersect(s, activeSegment)) {
                cout << "INTERSECTION\n";
                cout<< s->p1.x <<" "<< s->p1.y<<" "<< s->p2.x<<" "<< s->p2.y << endl;
                cout<< activeSegment->p1.x <<" "<< activeSegment->p1.y<<" "<< activeSegment->p2.x<<" "<< activeSegment->p2.y << endl;
                return 0;
            }
        }
    
        // Add the new segment to the set
        activeSegments.insert(s);
    }
    
    // No intersections found
    cout << "NO INTERSECTIONS" << endl;
    
    // Free memory
    for (Segment* s : segments) {
        delete s;
    }
    
    return 0;
}
