#!/usr/bin/env python

import wx;
import os;
import wx.html;
from os.path import exists;

MAIN_WINDOW_DEFAULT_SIZE = (640, 480);
ABOUT_DIALOG_SIZE = (320, 240);

class ImageViewerAbout(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, -1, 'About the ImageViewer', size = ABOUT_DIALOG_SIZE);
        text = '''<html>
            <h1>Image viewer</h1>
            <p>The Image viewer is a demonstration application for the wxPython tutorial.</p>
            <p>More information is available at <a href="http://showmedo.com">Showmedow.com</a>.</p>
            <p>Created Feburary 2008, Copyright &copy; Showmedo Ltd.</p>
            </html>''';
        html = wx.html.HtmlWindow(self);
        html.SetPage(text);
        button = wx.Button(self, wx.ID_OK, 'OK');
        sizer = wx.BoxSizer(wx.VERTICAL);
        sizer.Add(html, 1, wx.EXPAND | wx.ALL, 5);
        sizer.Add(button, 0, wx.ALIGN_CENTER | wx.ALL, 5);
        self.SetSizer(sizer);
        self.Layout();

class Frame(wx.Frame):
    def __init__(self, parent, id, title):
        self.dirname = os.getcwd();
        self.image = None;

        style = wx.DEFAULT_FRAME_STYLE ^ wx.RESIZE_BORDER;
        wx.Frame.__init__(self, parent, id, title = title,
                size = MAIN_WINDOW_DEFAULT_SIZE, style = style);

        self.Center();
        self.panel = wx.Panel(self);
        self.panel.SetBackgroundColour('White');
        self.CreateMenuBar();

        self.statusbar = self.CreateStatusBar();
        self.statusbar.SetFieldsCount(2);
        self.statusbar.SetStatusText('No image specified', 1);

    def CreateMenuBar(self):
        filemenu = wx.Menu();

        itemOpen = filemenu.Append(wx.ID_OPEN, '&Open an image', 'Open a image');
        filemenu.AppendSeparator();
        itemMirror = filemenu.Append(wx.ID_SAVE, '&Mirror image', 'Mirror the image horizontally');
        filemenu.AppendSeparator();
        itemExit = filemenu.Append(wx.ID_EXIT, 'E&xit', 'Terminate the program');

        aboutmenu = wx.Menu();
        itemAbout = aboutmenu.Append(wx.ID_ABOUT, '&About', 'Information about this program');

        self.Bind(wx.EVT_MENU, self.OnMirror, itemMirror);
        self.Bind(wx.EVT_MENU, self.OnOpen, itemOpen);
        self.Bind(wx.EVT_MENU, self.OnAbout, itemAbout);
        self.Bind(wx.EVT_MENU, self.OnExit, itemExit);
        menubar = wx.MenuBar();
        menubar.Append(filemenu, '&File');
        menubar.Append(aboutmenu, '&About');

        self.SetMenuBar(menubar);
        self.Show(True);

    def OnMirror(self, event):
        if self.image is None:
            return;
        old = self.image;
        self.image = old.Mirror(True);
        old.Destroy();
        self.ShowBitmap();

    def OnOpen(self, event):
        filters = 'Image files (*.gif;*.png;*.jpg)|*.gif;*.png;*.jpg';
        dlg = wx.FileDialog(self, message = "Open an Image...", defaultDir = self.dirname,
                defaultFile = '', wildcard = filters, style = wx.OPEN);
        if dlg.ShowModal() == wx.ID_OK:
            self.dirname = dlg.GetDirectory();
            filename = dlg.GetPath();
            self.SetTitle(filename);
            wx.BeginBusyCursor();
            self.image = wx.Image(filename, wx.BITMAP_TYPE_ANY, -1);
            self.statusbar.SetStatusText('Size = %s' % (str(self.image.GetSize())), 1);
            self.ShowBitmap();
            wx.EndBusyCursor();
        dlg.Destroy();

    def ShowBitmap(self):
        window_list = self.panel.GetChildren();
        for child in window_list:
            child.Destroy();

        if self.image is None:
            return;
        bitmap = wx.StaticBitmap(self.panel, -1, wx.BitmapFromImage(self.image));
        self.SetClientSize(bitmap.GetSize());

    def OnAbout(self, event):
        dlg = ImageViewerAbout(self);
        dlg.ShowModal();
        dlg.Destroy();

    def OnExit(self, event):
        #self.Close(True);
        self.Destroy();

class App(wx.App):
    def OnInit(self):
        self.frame = Frame(parent = None, id = -1, title = "Image viewer");
        self.frame.Show();
        self.SetTopWindow(self.frame);
        return True;

if __name__ == "__main__":
    app = App();
    splash_image_path = "python.png";
    splash_duration = 3000;
    if exists(splash_image_path):
        splash_image = wx.Image(splash_image_path, wx.BITMAP_TYPE_ANY, -1);
        wx.SplashScreen(splash_image.ConvertToBitmap(), wx.SPLASH_CENTER_ON_SCREEN | wx.SPLASH_TIMEOUT,
                splash_duration, None, -1);
    app.MainLoop();
