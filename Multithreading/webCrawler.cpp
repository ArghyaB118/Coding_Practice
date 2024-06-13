/* LC#1242

Given a URL startUrl and an interface HtmlParser, 
implement a Multi-threaded web crawler 
to crawl all links that are under the same hostname as startUrl.

Return all URLs obtained by your web crawler in any order.

Your crawler should:

Start from the page: startUrl
Call HtmlParser.getUrls(url) to get all URLs from a webpage of a given URL.
Do not crawl the same link twice.
Explore only the links that are under the same hostname as startUrl.

As shown in the example URL above, 
the hostname is example.org. 
For simplicity's sake, 
you may assume all URLs use HTTP protocol 
without any port specified. 
For example, the URLs http://leetcode.com/problems and http://leetcode.com/contest 
are under the same hostname, 
while URLs http://example.org/test and 
http://example.com/abc are not under the same hostname.
*/

class WebCrawler {
private:
    string hostName;
    string getHost (string url) {
        return url.substr(0, url.find('/', 7));
    }
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        queue<string> q({startUrl});
        unordered_set<string> seen;
        mutex mtx;
        condition_variable cv;
        vector<thread> threads;
        this->hostName = getHost(startUrl);
        
        auto worker = [&]() {
            while (true) {
                unique_lock<mutex> lock(mtx);
                cv.wait_for(lock, 15ms, [&]() { return q.size(); });

                if (q.empty())
                    return;

                string url = q.front();
                seen.insert(url);
                vector<string> urls = htmlParser.getUrls(url);
                q.pop();
                lock.unlock();

                for (auto &j : urls) {
                    lock_guard<mutex> lock(mtx);
                    if (seen.find(j) == seen.end() 
                        && getHost(j) == this->hostName)
                        q.push(j);
                }

                lock.lock();
                cv.notify_all();
            }
        };

        for (int i = 0; i < thread::hardware_concurrency(); ++i)
            threads.emplace_back(worker);

        for (auto& t : threads) t.join();
        return {seen.begin(), seen.end()};
    }
};