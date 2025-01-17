//https://rosettacode.org/wiki/Stable_marriage_problem#C.2B.2B
// go to the link for more things to implement
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

const char *men_data[][11] = {
    { "abe",  "abi","eve","cath","ivy","jan","dee","fay","bea","hope","gay" },
    { "bob",  "cath","hope","abi","dee","eve","fay","bea","jan","ivy","gay" },
    { "col",  "hope","eve","abi","dee","bea","fay","ivy","gay","cath","jan" },
    { "dan",  "ivy","fay","dee","gay","hope","eve","jan","bea","cath","abi" },
    { "ed",   "jan","dee","bea","cath","fay","eve","abi","ivy","hope","gay" },
    { "fred", "bea","abi","dee","gay","eve","ivy","cath","jan","hope","fay" },
    { "gav",  "gay","eve","ivy","bea","cath","abi","dee","hope","jan","fay" },
    { "hal",  "abi","eve","hope","fay","ivy","cath","jan","bea","gay","dee" },
    { "ian",  "hope","cath","dee","gay","bea","abi","fay","ivy","jan","eve" },
    { "jon",  "abi","fay","jan","gay","eve","bea","dee","cath","ivy","hope" }
};

const char *women_data[][11] = {
    { "abi",  "bob","fred","jon","gav","ian","abe","dan","ed","col","hal" },
    { "bea",  "bob","abe","col","fred","gav","dan","ian","ed","jon","hal" },
    { "cath", "fred","bob","ed","gav","hal","col","ian","abe","dan","jon" },
    { "dee",  "fred","jon","col","abe","ian","hal","gav","dan","bob","ed" },
    { "eve",  "jon","hal","fred","dan","abe","gav","col","ed","ian","bob" },
    { "fay",  "bob","abe","ed","ian","jon","dan","fred","gav","col","hal" },
    { "gay",  "jon","gav","hal","fred","bob","abe","col","ed","dan","ian" },
    { "hope", "gav","jon","bob","abe","ian","dan","hal","ed","col","fred" },
    { "ivy",  "ian","col","hal","gav","fred","bob","abe","ed","jon","dan" },
    { "jan",  "ed","hal","gav","abe","bob","jon","col","ian","fred","dan" }
};

typedef vector<string> PrefList;
typedef map<string, PrefList> PrefMap;
typedef map<string, string> Couples;

bool prefers(const PrefList &prefer, const string &first, const string &second)
{
    for (PrefList::const_iterator it = prefer.begin(); it != prefer.end(); ++it)
    {
        if (*it == first) return true;
        if (*it == second) return false;
    }
    return false; // no preference
}


int main() {
	PrefMap men_pref, women_pref;
    queue<string> bachelors;
 
    // init data structures
    for (int i = 0; i < 10; ++i) // person
    {
        for (int j = 1; j < 11; ++j) // preference
        {
            men_pref[men_data[i][0]].push_back(men_data[i][j]);
            women_pref[women_data[i][0]].push_back(women_data[i][j]);
        }
        bachelors.push(men_data[i][0]);
    }
 
    Couples engaged; // <woman,man>

    for (int i = 0; i < 10; ++i) // person
    {
        for (int j = 0; j < 11; ++j) // preference
        {
        	cout << men_pref[men_data[i][0]][j] << "\t";
        }
        cout << "\n";
    }
    /*while(!bachelors.empty()){
		cout<<" "<<bachelors.front();
		bachelors.pop();
	}
	cout << "\n";*/

	cout << "Matchmaking:\n";
    while (!bachelors.empty())
    {
        const string &suitor = bachelors.front();
        const PrefList &preflist = men_pref[suitor];
 
        for (PrefList::const_iterator it = preflist.begin(); it != preflist.end(); ++it)
        {
            const string &bride = *it;
 
            if (engaged.find(bride) == engaged.end()) // she's available
            {
                cout << "\t" << bride << " and " << suitor << "\n";
                engaged[bride] = suitor; // hook up
                break;
            }

            const string &groom = engaged[bride];
 
            if (prefers(women_pref[bride], suitor, groom))
            {
                cout << "\t" << bride << " dumped " << groom << " for " << suitor << "\n";
                bachelors.push(groom); // dump that zero
                engaged[bride] = suitor; // get a hero
                break;
            }
        }
        bachelors.pop();
    }

    cout << "Engagements:\n";
    for (Couples::const_iterator it = engaged.begin(); it != engaged.end(); ++it)
    {
        cout << "\t" << it->first << " and " << it->second << "\n";
    }
}
