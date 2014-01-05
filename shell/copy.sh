#!/bin/sh

#smbclient '\\mbjsfs06\' '' -d 10 -D '\public2\AM_Share\vend_am00005\' -U vend_am00005 -c 'put /proj/vend_am00005/bin/dashboard.txt'

#smbclient //mbjsfs06/ '' -d 10 -D '/public2/AM_Share/vend_am00005/' -U vend_am00005 -tc backup.tar $PWD
smbclient '\\10.15.11.230\' '' -D '\public2\AM_Share\vend_am00005\' -U vend_am00005 -c 'put /proj/vend_am00005/bin/dashboard.txt'
