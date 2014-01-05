#!/usr/bin/env python

from scrapy.spider import BaseSpider
from scrapy.selector import HtmlXPathSelector
from dmoz.items import DmozItem

class DmozSpider(BaseSpider):
    name = "dmoz"
    allowed_domains = ["dmoz.org"]
    start_urls = [
            "http://www.dmoz.org/Computers/Programming/Languages/Python/Books/",
            "http://www.dmoz.org/Computers/Programming/Languages/Python/Resources/"
    ]

    def parse(self, response):
        sel = HtmlXPathSelector(response)
        sites = sel.select('//ul/li')
        items = []
        for site in sites:
            item = DmozItem()
            item['title'] =  site.select('a/text()').extract()
            item['link'] = site.select('a/@href').extract()
            item['desc'] = site.select('text()').extract()
            items.append(item)

        return items
