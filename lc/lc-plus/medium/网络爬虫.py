# """
# This is HtmlParser's API interface.
# You should not implement it, or speculate about its implementation
# """
#class HtmlParser(object):
#    def getUrls(self, url):
#        """
#        :type url: str
#        :rtype List[str]
#        """
from urllib.parse import urlparse

def get_domain(url):
    parsed_url = urlparse(url)
    domain = parsed_url.netloc
    return domain

class Solution:
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        dom = get_domain(startUrl)
        vis = set()
        ans = []
        def dfs(url):
            nonlocal htmlParser,vis,ans,dom
            ans.append(url)
            vis.add(url)
            urls = htmlParser.getUrls(url)
            for u in urls:
                if u not in vis and get_domain(u) == dom:
                    dfs(u)
        dfs(startUrl)
        return ans
