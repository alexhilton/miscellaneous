#!/usr/bin/env python

from CGIHTTPServer import CGIHTTPRequestHandler
from BaseHTTPServer import HTTPServer

server_addr = ('', 8000)
httpd = HTTPServer(server_addr, CGIHTTPRequestHandler)
httpd.serve_forever()
