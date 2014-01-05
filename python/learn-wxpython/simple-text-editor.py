#!/usr/bin/env python

import wx;
from os.path import join;

class MyFrame(wx.Frame):
    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, title = title, size = (480, 320));
        self.control = wx.TextCtrl(self, style = wx.TE_MULTILINE);
        self.Show(True);

        filemenu = wx.Menu();

        itemOpen = filemenu.Append(wx.ID_OPEN, '&Open', 'Open a textfile');
        filemenu.AppendSeparator();
        itemSave = filemenu.Append(wx.ID_SAVE, '&Save', 'Save as a textfile');
        filemenu.AppendSeparator();
        itemExit = filemenu.Append(wx.ID_EXIT, 'E&xit', 'Terminate the program');

        aboutmenu = wx.Menu();
        itemAbout = aboutmenu.Append(wx.ID_ABOUT, '&About', 'Information about this program');

        self.Bind(wx.EVT_MENU, self.onSave, itemSave);
        self.Bind(wx.EVT_MENU, self.onOpen, itemOpen);
        self.Bind(wx.EVT_MENU, self.onAbout, itemAbout);
        self.Bind(wx.EVT_MENU, self.onExit, itemExit);
        menubar = wx.MenuBar();
        menubar.Append(filemenu, '&File');
        menubar.Append(aboutmenu, '&About');

        self.SetMenuBar(menubar);
        self.Show(True);

    def onOpen(self, event):
        self.dirname = '';
        dlg = wx.FileDialog(self, 'Choose a textfile', self.dirname, '', '*.txt', wx.OPEN);
        if dlg.ShowModal() == wx.ID_OK:
            self.filename = dlg.GetFilename();
            self.dirname = dlg.GetDirectory();
            f = open(join(self.dirname, self.filename), 'r');
            self.control.SetValue(f.read());
            f.close();
        dlg.Destroy();

    def onSave(self, event):
        text = self.control.GetValue();
        if text.strip() == '':
            dlg = wx.MessageDialog(self, 'Content is empty', 'Warning', wx.OK);
            dlg.ShowModal();
            dlg.Destroy();
            return;
        self.dirname = '';
        dlg = wx.FileDialog(self, 'Save file', self.dirname, '', '*.txt', wx.SAVE);
        if dlg.ShowModal() == wx.ID_OK:
            self.filename = dlg.GetFilename();
            self.dirname = dlg.GetDirectory();
            f = open(join(self.dirname, self.filename), 'w');
            f.write(text);
            f.write('\n');
            f.close();
        dlg.Destroy();

    def onAbout(self, event):
        dlg = wx.MessageDialog(self, 'A small text editor', 'About sample editor', wx.OK);
        dlg.ShowModal();
        dlg.Destroy();

    def onExit(self, event):
        self.Close(True);

app = wx.App(False);
frame = MyFrame(None, 'Sample text editor');
app.MainLoop();
