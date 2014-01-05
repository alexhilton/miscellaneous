"""
  Objective:

    Render a simple Web page containing text, data,
    and graphics. Wireframe design to be provided.

  Implementation:

    This sample makes use of the Twisted framework,
    which is more than a web framework but supports
    other protocols, both server and client.
    Information about Twisted can be found at:

        http://twistedmatrix.com/trac/

    The sample also makes use of STAN, a document
    object model lighter than that of W3C, and part
    of the Nevow extension to Twisted, for defining
    the page HTML layout.  Nevow can be obtained at:

        http://divmod.org/trac/wiki/DivmodNevow

    As an aside, the Nevow package provides very
    cool AJAX/COMET support for Python with its
    Athena module.  We don't use AJAX for this
    example though.

    For parsing an example RSS feed, the sample
    relies upon:

      Universal Feed Parser by Mark Pilgrim (Author
      of "Dive into Python")
      http://code.google.com/p/feedparser/
      http://feedparser.org/docs/

    Python has many web frameworks, some of which
    generate HTML source programmatically from
    within Python, and others of which use a
    template language and embed Python expressions
    into the stylized HTML.  Twisted uses a slightly
    different approach, in providing a "Pythonic
    DOM" model, where the HTML is defined, not as
    strings, in the Python program itself.  This DOM
    model allows for very powerful aggregation of
    HTML fragments, such as widgets, access to the
    full expressive power of Python, and reliable
    escaping of variable values into URL and HTML
    safe strings.

  Execution:

    This source file represents the entire webserver
    instance.  It gets imported at runtime into the
    Twisted framework, which provides network
    listening, daemon-restart/backgrounding
    management and Apache-format common logging.

    To bring up the server in the foreground:

      % twistd -noy sample.tac

    and point your browser to http://localhost:8081

"""

import sys;
import os;
import os.path;
import urllib2;
import feedparser;

from twisted.application import service, strports;
from nevow import appserver, loaders, static, rend;
from nevow import tags as T;

def site_welcome(context, data):
    """Return an HTML fragment for the center pane of the front page"""

    text = """
        Python is a dynamic object-oriented
        programming language that can be used for
        many kinds of software development. It
        offers strong support for integration with
        other languages and tools, comes with
        extensive standard libraries, and can be
        learned in a few days. Many Python
        programmers report substantial productivity
        gains and feel the language encourages the
        development of higher quality, more
        maintainable code.

        Python runs on Windows, Linux/Unix, Mac OS
        X, OS/2, Amiga, Palm Handhelds, and Nokia
        mobile phones. Python has also been ported
        to the Java and .NET virtual machines.

        Python is distributed under an OSI-approved
        open source license that makes it free to
        use, even for commercial products.

        The Python Software Foundation (PSF) holds
        and protects the intellectual property
        rights behind Python, underwrites the PyCon
        conference, and funds grants and other
        projects in the Python community.
    """

    return [T.p[para] for para in text.split('\n\n')];

def pull_rssfeed(feed_url, maxstories = 9):
    "Pull the most recent N news stories and formt to HTML"
    events = [];
    feed = feedparser.parse(feed_url);
    for entry in feed.entries:
        events.append(T.p[T.a(href = entry.link)[entry.title]]);
        if len(events) >= maxstories:
            break;

    return events;

class MySiteRootPage(rend.Page):
    """Define the content and general layout of the site front page"""
    addSlash = True;
    docFactory = loaders.stan(
            T.html(xmlns = 'http://www.w3.org/1999/xhtml', lang = 'en')[
                T.head[T.title['Sample code'], T.link(href = '/samplesite.css',
                                                        type = 'text/css',
                                                        rel = 'stylesheet')
                ],
                T.body[
                    T.table(style = 'width: 100%;', border = 1)[
                        T.tr[
                            T.td(id = 'banner', colspan = 3)[
                                T.img(src = '/sitelogo.png', height = 50),
                            ],
                        ],
                        T.tr[
                            T.td(id = 'sidelinks', render = T.directive('linkset'),
                                        data = T.directive('linkset')),
                            T.td(id = 'newspane')[site_welcome],
                            T.td(id = 'events')[
                                T.a(href = 'http://us.pycon.org/')[
                                    T.img(src = '/eventlogo.gif'),
                                ],
                                T.br,
                                T.div(id = 'rssfeed')[pull_rssfeed(
                                        'http://www.python.org/channews.rdf',
                                        maxstories = 5)
                                ],
                            ],
                        ],
                    ]
                ]
            ]
    );

    def data_linkset(self, context, data):
        "Return a list of links, with labels, for 'linkset' directive above"
        return (
                ('The Basics',
                    'http://www.python.org/about'),
                ('Documentation',
                    'http://www.python.org/doc/'),
                ('Downloads',
                    'http://www.python.org/download/'),
                ('Code samples',
                    'http://aspn.activestate.com/ASPN/Python/Cookbook/'),
                ('Discussion forum',
                    'http://www.python.org/community/lists/'),
                ('About us',
                    'http://www.python.org/psf/'),
               );

    def render_linkset(self, context, links):
        "Given a list of links, format as a sequence of anchor tags."
        
        return context.tag[
                    [T.p[T.a(href = url)[label]] for label, url in links]
               ];

site_dir = os.path.split(os.path.abspath(__file__))[0];

root = MySiteRootPage();

root.putChild('samplesite.css',
        static.File(os.path.join(site_dir, 'samplesite.css')));
root.putChild('sitelogo.png',
        static.File(os.path.join(site_dir, 'sitelogo.png')));
root.putChild('eventlogo.gif',
        static.File(os.path.join(site_dir, 'eventlogo.gif')));

application = service.Application('sampleserver');

http_site = appserver.NevowSite(root);
strports.service('8081', http_site).setServiceParent(application);
