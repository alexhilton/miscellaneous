#!/usr/bin/env python

import cgi
import cgitb; cgitb.enable()
import os
import urllib

CONTENTS_DIR="contents"

def redirect(url):
	#print "Status: 302 Moved"
	#print "Location: %s" % url
	#print
	
    print "Content-Type: text/plain"
    print "Refresh: 0; url=%s" % url
    print
    print "Redirecting..."

def url(**kw):
    params=["%s=%s" % (key,urllib.quote_plus(value)) for key,value in kw.items()]
    return "?" + "&".join(params)

def page_file_name(page):
    file_name="%s.txt" % urllib.quote_plus(page)
    return os.path.join(CONTENTS_DIR,file_name)

def page_contents(page):
    file_name=page_file_name(page)
    if not os.path.exists(file_name):
        return None
    return file(file_name).read()

def save_page_contents(page,contents):
    file_name=page_file_name(page)
    file(file_name,'w').write(contents)

def page_header(title):
    print "Content-Type: text/html"
    print
    print "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dt'>"
    print "<html xmlns='http://www.w3.org/1999/xhtml'>"
    print "<head>"
    print "<title>%s</title>" % cgi.escape(title)
    print "</head>"
    print "<body>"

def page_footer(page=None):
	print "<div class='footer_links'>"
	if page is not None:
		print "[<a href='%s'>%s</a>]" % (cgi.escape(url(page=page,action='edit')),'edit')
	print "</div>"
	print "</body>"
	print "</html>"

def view_page(page,params):
    contents=page_contents(page)
    if contents is None:
        edit_page(page,params)
        return
    
    page_header(page)
    print "<h1>%s</h1>" % cgi.escape(page)
    print "<div class='contents'>"
    print cgi.escape(contents)
    print "</div>"
    page_footer(page=page)

def edit_page(page,params):
    title='Edit'
    contents=page_contents(page)
    if contents is None:
        contents=''
        title='Add'

    page_header(title)
    print "<h1>%s: %s</h1>" % (title,cgi.escape(page))
    print "<div class='contents'>"
    print "<form method='post'>"
    print "<input type='hidden' name='page' value='%s' />" % cgi.escape(page)
    print "<input type='hidden' name='action' value='save' />"
    print "<textarea name='contents' rows='20' cols='80'>%s</textarea>"  % cgi.escape(contents)
    print "<div><input type='submit' value='Save' /></div>"
    print "</form>"
    print "</div>"
    page_footer(page=page)

def save_page(page,params):
    contents=params.getfirst('contents',None)
    if contents is not None:
        save_page_contents(page,contents)
	#view_page(page,params)
    redirect(url(page=page,action='view'))

views = { 'view': view_page, 'edit': edit_page, 'save': save_page }

def execute(params):
	page=params.getfirst('page','main')
	action=params.getfirst('action','view')
	view=views.get(action,view_page)
	view(page,params)

params=cgi.FieldStorage()
execute(params)
