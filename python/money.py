#!/usr/bin/env python

# -*- coding: utf-8 -*-

import sys

year = 365.0

def debtAcuire():
    print 'Calculate genarel interest rate for debt acquisition:'
    print '----------------------------------------------------'
    captital = float(raw_input('Your capital:'))
    rate = float(raw_input('Interest Rate in percentage:%'))
    rate /= 100.0
    interest = float(raw_input('Expected interest:'))
    bonus = float(raw_input('Bonus Interest:'))
    redpocket = float(raw_input('Platform red pocket:'))
    duration = int(raw_input('Remaining duration in days:'))
    total = bonus + redpocket + interest
    annualRate = total * year / (captital * duration)
    print 'Capital: \t\t\t{0}'.format(captital)
    print 'Interest Rate: \t\t\t{0:.3%}'.format(rate)
    print 'Interest: \t\t\t{0}'.format(interest)
    print 'Bonus: \t\t\t\t{0}'.format(bonus)
    print 'RedPocket: \t\t\t{0}'.format(redpocket)
    print 'Total: \t\t\t\t{0}'.format(total)
    print 'General Annual Interest Rate: \t{0:.3%}'.format(annualRate)


def directInvest():
    print 'Calculate general interest rate for direct investment project:'
    print '-------------------------------------------------------------'
    captital = float(raw_input('Your capital:'))
    rate = float(raw_input('Interest Rate in percentage:%'))
    rate /= 100.0
    redpocket = float(raw_input('Platform red pocket:'))
    duration = int(raw_input('Duration in days:'))
    interest = captital * rate * duration / year
    total = redpocket + interest
    annualRate = total * year / (captital * duration)
    print 'Capital: \t\t\t{0}'.format(captital)
    print 'Interest Rate: \t\t\t{0:.3%}'.format(rate)
    print 'Interest: \t\t\t{0}'.format(interest)
    print 'RedPocket: \t\t\t{0}'.format(redpocket)
    print 'Total: \t\t\t\t{0}'.format(total)
    print 'General Annual Interest Rate: \t{0:.3%}'.format(annualRate)

def main():
    if len(sys.argv) > 1:
        directInvest()
    else:
        debtAcuire()

if __name__ == '__main__':
    main()